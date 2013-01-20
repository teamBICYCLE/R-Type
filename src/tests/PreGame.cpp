#include <stdexcept>
#include <functional>
#include "PreGame.hh"
#include "system/log/Log.hh"

PreGame::PreGame(const std::string &ip, const std::string &port)
 : _gameIsLaunched(false)
{
	_cmdType["notif"] = std::bind(&PreGame::handleNotif, this, std::placeholders::_1);
	_cmdType["hi"] = std::bind(&PreGame::handleWelcome, this, std::placeholders::_1);
	_cmdType["err"] = std::bind(&PreGame::handleError, this, std::placeholders::_1);
	_cmdType["rep"] = std::bind(&PreGame::handleResponse, this, std::placeholders::_1);

	_notifType["gamestart"] = std::bind(&PreGame::handleGameStart, this, std::placeholders::_1);
	_notifType["gameend"] = std::bind(&PreGame::handleGameEnd, this, std::placeholders::_1);
	_notifType["player"] = std::bind(&PreGame::handlePlayer, this, std::placeholders::_1);
	
	_playerAction["join"] = std::bind(&PreGame::handlePlayerJoin, this, std::placeholders::_1);
	_playerAction["leave"] = std::bind(&PreGame::handlePlayerLeave, this, std::placeholders::_1);
	_playerAction["ready"] = std::bind(&PreGame::handlePlayerReady, this, std::placeholders::_1);
	_playerAction["not_ready"] = std::bind(&PreGame::handlePlayerNotReady, this, std::placeholders::_1);

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
	_cmdType(other._cmdType), _notifType(other._notifType)
{}

PreGame::PreGame(PreGame&& other)
{
	swap(*this, other);	
}

PreGame &PreGame::operator=(PreGame other)
{
	swap(*this, other);
	return (*this);
}

void swap(PreGame &lhs, PreGame &rhs)
{
	lhs._socket = rhs._socket;
	lhs._gameIsLaunched = rhs._gameIsLaunched;
	lhs._listener = rhs._listener;
	lhs._cmdType = rhs._cmdType;
	lhs._notifType = rhs._notifType;
}

PreGame::~PreGame(void)
{}

void PreGame::run(void)
{
	while (1)
	{
		_listener.waitEvent(std::chrono::milliseconds(10000));
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
	char msg[155];
	int ret;

	try {
		ret = socket->recv(msg, 154);
	} catch (std::runtime_error &e) {
		TBSystem::log::err << e.what() << TBSystem::log::endl;
		return (false);
	}
	if (!ret) {
		return (false);
	}
	handleMsg(std::string(msg));
	return (true);
}

void PreGame::handleMsg(const std::string &msg)
{
  std::istringstream iss(msg);
  std::string cmdType;
  iss >> cmdType;

  std::istreambuf_iterator<char> eos;
  std::string s(std::istreambuf_iterator<char>(iss), eos);
  if (_cmdType.find(cmdType) != _cmdType.end()) {
  	_cmdType.find(cmdType)->second(s);
  }


TBSystem::log::info << " coucou " << msg << TBSystem::log::endl;
}

void PreGame::handleNotif(const std::string &notif)
{
	std::istringstream iss(notif);
	std::string notifType;

	iss >> notifType;
  	std::istreambuf_iterator<char> eos;
  	std::string s(std::istreambuf_iterator<char>(iss), eos);
  	if (_notifType.find(notifType) != _notifType.end()) {
  	_notifType.find(notifType)->second(s);
	}
	TBSystem::log::info << " NOTIFS !|" << notif << TBSystem::log::endl;
}

void PreGame::handleWelcome(const std::string &welcome)
{
	std::istringstream iss(welcome);
	unsigned int i;

	iss >> i;
	TBSystem::log::info << i << " WELCOME !|" << welcome << TBSystem::log::endl;
}

void PreGame::handleError(const std::string &error)
{
	TBSystem::log::info << " Error !|" << error << TBSystem::log::endl;	
}

void PreGame::handleResponse(const std::string &response)
{
	TBSystem::log::info << " Error !|" << response << TBSystem::log::endl;		
}

void PreGame::handleGameStart(const std::string &roomId)
{
	std::istringstream iss(roomId);
	unsigned int id;

	iss >> id;
	TBSystem::log::info << id << " GAMESTART !|" << roomId << TBSystem::log::endl;
}

void PreGame::handleGameEnd(const std::string &roomId)
{
	std::istringstream iss(roomId);
	unsigned int id;

	iss >> id;
	TBSystem::log::info << id << " GAMEEND !|" << roomId << TBSystem::log::endl;
}

void PreGame::handlePlayer(const std::string &player)
{
	std::istringstream iss(player);
	std::string playerAction;

	iss >> playerAction;
  	std::istreambuf_iterator<char> eos;
  	std::string s(std::istreambuf_iterator<char>(iss), eos);
  	if (_notifType.find(playerAction) != _notifType.end()) {
  	_notifType.find(playerAction)->second(s);
	}
	TBSystem::log::info  << " PLAYER !|" << player << TBSystem::log::endl;	
}

void PreGame::handlePlayerJoin(const std::string &player)
{
	std::istringstream iss(player);
	unsigned int id;

	iss >> id;	
	TBSystem::log::info << id << " PLAYERJOIN !|" << player << TBSystem::log::endl;	
}

void PreGame::handlePlayerLeave(const std::string &player)
{
	std::istringstream iss(player);
	unsigned int id;

	iss >> id;	
	TBSystem::log::info << id << " PLAYERLEAVE !|" << player << TBSystem::log::endl;	
}

void PreGame::handlePlayerReady(const std::string &player)
{
	std::istringstream iss(player);
	unsigned int id;

	iss >> id;	
	TBSystem::log::info << id << " PLAYERReady !|" << player << TBSystem::log::endl;
}

void PreGame::handlePlayerNotReady(const std::string &player)
{
	std::istringstream iss(player);
	unsigned int id;

	iss >> id;
	TBSystem::log::info << id << " PLAYERNOTREADY !|" << player << TBSystem::log::endl;
}