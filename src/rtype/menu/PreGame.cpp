#include <stdexcept>
#include <functional>
#include "PreGame.hh"
#include "system/log/Log.hh"

PreGame::PreGame(const std::string &ip, const std::string &port)
 : _gameIsLaunched(false)
{
  using namespace std::placeholders;

	_cmdType["notif"] = std::bind(&PreGame::handleNotif, this, std::placeholders::_1);
	_cmdType["hi"] = std::bind(&PreGame::handleWelcome, this, std::placeholders::_1);
	_cmdType["err"] = std::bind(&PreGame::handleError, this, std::placeholders::_1);
	_cmdType["rep"] = std::bind(&PreGame::handleResponse, this, std::placeholders::_1);

  _roomlistMap["start"] = std::bind(&PreGame::roomlistStart, this);
  _roomlistMap["room"] = std::bind(&PreGame::roomlistAppend, this, _1);
  _roomlistMap["end"] = std::bind(&PreGame::roomlistEnd, this);

  	try {
  		_socket.reset(new TBSystem::network::sockets::Tcp);
  		TBSystem::network::Addr addr(ip, port, "TCP");
  		_socket->connect(addr);
  		_listener.addSocket(_socket,
  			std::bind(&PreGame::read, this, std::placeholders::_1),
  			std::bind(&PreGame::disconnected, this));
	} catch (std::runtime_error &e) {
		TBSystem::log::err << e.what() << TBSystem::log::endl;
		throw std::invalid_argument("Could not connect to server");
	}
}

PreGame::PreGame(const PreGame &other)
	: _listener(other._listener), _socket(other._socket), _gameIsLaunched(false),
	_cmdType(other._cmdType)
{}

PreGame::PreGame(PreGame&& other)
{
	swap(*this, other);
}

PreGame &PreGame::operator=(PreGame other)
{
	if (this != &other) {
		swap(*this, other);
	}
	return (*this);
}

void swap(PreGame &lhs, PreGame &rhs)
{
	lhs._socket = rhs._socket;
	lhs._gameIsLaunched = rhs._gameIsLaunched;
	lhs._listener = rhs._listener;
	lhs._cmdType = rhs._cmdType;
}

PreGame::~PreGame(void)
{}

void PreGame::run(void)
{
	while (1)
	{
		_listener.waitEvent(std::chrono::seconds(1));
		_listener.execute();
	}
}

void PreGame::disconnected(void)
{
	throw std::runtime_error("Error, disconnected from server");
}

bool PreGame::read(
		std::shared_ptr<TBSystem::network::sockets::ITcpSocket> &socket)
{
  char  buf[512];
  std::string::size_type pos;

  buf[socket->recv(buf, sizeof(buf))] = '\0';
  if (!buf[0]) return false;
  _commandLine += buf;

  while ((pos = _commandLine.find("\r\n")) != std::string::npos) {
    std::string line(_commandLine.substr(0, pos));
    std::string command;
    _commandLine = _commandLine.substr(pos + 2);

    handleMsg(line);
  }
	return (true);
}

void PreGame::handleMsg(const std::string &msg)
{
  std::istringstream iss(msg);
  std::string cmdType;
  iss >> cmdType;

  std::istreambuf_iterator<char> eos;
  std::string s(std::istreambuf_iterator<char>(iss), eos);
  auto it = _cmdType.find(cmdType);
  if (it != _cmdType.end()) {
  	it->second(s);
  }


TBSystem::log::info << " coucou " << msg << TBSystem::log::endl;
}

void PreGame::handleNotif(const std::string &notif)
{
	TBSystem::log::info << " NOTIFS !|" << notif << TBSystem::log::endl;
}

void PreGame::handleWelcome(const std::string &welcome)
{
  std::stringstream ss(welcome);
  std::string roomlist("roomlist\r\n");
	TBSystem::log::info << " WELCOME !|" << welcome << TBSystem::log::endl;
  ss >> _id;
  _socket->send(roomlist.c_str(), roomlist.size());
}

void PreGame::handleError(const std::string &error)
{
	TBSystem::log::info << " Error !|" << error << TBSystem::log::endl;
}

void PreGame::handleResponse(const std::string &response)
{
	TBSystem::log::info << " Rep !|" << response << TBSystem::log::endl;

  std::stringstream line(response);
  std::string cmd;

  line >> cmd;

}

void PreGame::roomlistDispatch(const std::string& command)
{
  std::stringstream ss(command);
  std::string type;

  ss >> type;
  auto it = _roomlistMap.find(type);
  if (it != _roomlistMap.end()) {
    it->second(type);
  }
}

void PreGame::roomlistStart()
{
  _rooms.clear();
}

void PreGame::roomlistAppend(const std::string& roomdetails)
{
  _rooms.emplace_back(roomdetails);
}

void PreGame::roomlistEnd()
{
  // TODO Notify the GUI of the update
}
