#include <stdexcept>
#include <functional>
#include "PreGame.hh"
#include "gamestate/GameState.hh"
#include "system/log/Log.hh"
#include "client.h"

PreGame::PreGame(const std::string &ip, const std::string &port)
 : _gameIsLaunched(false)
 , _currentRoom(-1)
 , _state(eHALLWAY)
 , _serverIp(ip)
 , _window(sf::VideoMode(GameState::WINDOW_WIDTH, GameState::WINDOW_HEIGHT),
           "SFML RType")
 , _menu("./resources/menu_background.jpg", _window.getSize(),
       sf::Vector2f(500.0,50.0))
{
  using namespace std::placeholders;


  _cmdType["notif"] = std::bind(&PreGame::handleNotif, this, _1);
  _cmdType["hi"] = std::bind(&PreGame::handleWelcome, this, _1);
  _cmdType["err"] = std::bind(&PreGame::handleError, this, _1);
  _cmdType["rep"] = std::bind(&PreGame::handleResponse, this, _1);
  _cmdType["gamestart"] = std::bind(&PreGame::handleGamestart, this, _1);

  _responseMap["roomlist"] = std::bind(&PreGame::roomlistDispatch, this, _1);
  _responseMap["room_details"] = std::bind(&PreGame::roomdetailsDispatch, this, _1);
  _responseMap["join"] = std::bind(&PreGame::joinRoom, this, _1);
  _responseMap["leave"] = std::bind(&PreGame::requestRoomlist, this);

  _roomlistMap["start"] = std::bind(&PreGame::roomlistStart, this);
  _roomlistMap["room"] = std::bind(&PreGame::roomlistAppend, this, _1);
  _roomlistMap["end"] = std::bind(&PreGame::roomlistEnd, this);

  _roomdetailsMap["start"] = std::bind(&PreGame::roomdetailsStart, this);
  _roomdetailsMap["player"] = std::bind(&PreGame::roomdetailsAppend, this, _1);
  _roomdetailsMap["end"] = std::bind(&PreGame::roomdetailsEnd, this);

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
  _musicPlayer.play("menu");
}

PreGame::~PreGame(void)
{}

void PreGame::run(void)
{
	while (_window.isOpen())
	{
    sf::Event event;

    while (_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        _window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        _menu.clickEvent(sf::Mouse::getPosition(_window));
      }
    }
		_listener.waitEvent(std::chrono::milliseconds(10));
		_listener.execute();
    _window.clear();
    _menu.draw(_window);
    _window.display();
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

	TBSystem::log::info << " WELCOME !|" << welcome << TBSystem::log::endl;
  ss >> _id;
  requestRoomlist();
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
  auto it = _responseMap.find(cmd);
  if (it != _responseMap.end()) {
    std::istreambuf_iterator<char> eos;
    std::string s(std::istreambuf_iterator<char>(line), eos);

    it->second(s);
  }
}

void PreGame::handleGamestart(const std::string& id)
{
  std::stringstream ss(id);
  int         intid;
  int         port;

  ss >> intid;
  ss >> port;
  TBSystem::log::info << "the port value is " << port << TBSystem::log::endl;
  _musicPlayer.play("game");
  _state = eHALLWAY;
  client(_serverIp, std::to_string(port), intid, _window);
  updateHallway();
}

void PreGame::joinRoom(const std::string& id)
{
  std::string details("room_details " + id + "\r\n");

  TBSystem::log::info << "will join " << id << TBSystem::log::endl;
  _socket->send(details.c_str(), details.size());
  _currentRoom = std::stoi(id);
  _state = eROOM;
  updateRoom();
}

void PreGame::roomlistDispatch(const std::string& command)
{
  std::stringstream ss(command);
  std::string type;

  TBSystem::log::info << "In dispatch with `" << command << "`" << TBSystem::log::endl;
  ss >> type;
  auto it = _roomlistMap.find(type);
  if (it != _roomlistMap.end()) {
    std::istreambuf_iterator<char> eos;
    std::string s(std::istreambuf_iterator<char>(ss), eos);

    it->second(s);
  }
}

void PreGame::roomlistStart()
{
  TBSystem::log::info << "In roomlist start" << TBSystem::log::endl;
  _rooms.clear();
}

void PreGame::roomlistAppend(const std::string& roomdetails)
{
  TBSystem::log::info << "In roomlist append" << TBSystem::log::endl;
  _rooms.emplace_back(roomdetails);
}

void PreGame::roomlistEnd()
{
  TBSystem::log::info << "In roomlist end" << TBSystem::log::endl;
  updateHallway();
}

void PreGame::roomdetailsDispatch(const std::string& command)
{
  std::stringstream ss(command);
  std::string type;
  int roomId;

  TBSystem::log::info << "In dispatch with `" << command << "`" << TBSystem::log::endl;
  ss >> roomId;
  ss >> type;
  if (roomId != _currentRoom) return;
  auto it = _roomdetailsMap.find(type);
  if (it != _roomdetailsMap.end()) {
    std::istreambuf_iterator<char> eos;
    std::string s(std::istreambuf_iterator<char>(ss), eos);

    it->second(s);
  }
}

void PreGame::roomdetailsStart(void)
{
  TBSystem::log::debug << "in start roomdetails ======" << TBSystem::log::endl;
  _players.clear();
}

void PreGame::roomdetailsAppend(const std::string& player)
{
  _players.emplace_back(player);
}

void PreGame::roomdetailsEnd(void)
{
  updateRoom();
}

void PreGame::createRoom(void)
{
  std::string cmd("create\r\n");

  _socket->send(cmd.c_str(), cmd.size());
}

void PreGame::startGame(void)
{
  std::string cmd("start " + std::to_string(_currentRoom) + "\r\n");

  _socket->send(cmd.c_str(), cmd.size());
}

void PreGame::tryJoinRoom(int roomId)
{
  std::string cmd("join " + std::to_string(roomId) + "\r\n");

  _socket->send(cmd.c_str(), cmd.size());
}

void PreGame::leaveRoom(void)
{
  std::string cmd("leave " + std::to_string(_currentRoom) + "\r\n");

  _socket->send(cmd.c_str(), cmd.size());
  _state = eHALLWAY;
  updateHallway();
}

void PreGame::requestRoomlist(void)
{
  std::string roomlist("roomlist\r\n");

  _socket->send(roomlist.c_str(), roomlist.size());
}

void PreGame::requestRoomdetails(int roomId)
{
  std::string cmd("room_details " + std::to_string(roomId) + "\r\n");

  _socket->send(cmd.c_str(), cmd.size());
}

void PreGame::updateHallway(void)
{
  using namespace std::placeholders;

  if (_state == eHALLWAY) {
    _menu.setButtonOne(sf::Vector2f(100.0f, 50.0f),
                       std::bind(&PreGame::createRoom, this),
                       "./resources/create_button.png");
    _menu.unsetButtonTwo();
    _menu.update(_rooms);
    _menu.setGlobalCallback(std::bind(&PreGame::tryJoinRoom, this, _1));
  }
}

void PreGame::updateRoom(void)
{
  if (_state == eROOM) {
    _menu.setButtonOne(sf::Vector2f(100.0f, 50.0f),
                       std::bind(&PreGame::startGame, this),
                       "./resources/play_button.png");
    _menu.setButtonTwo(sf::Vector2f(100.0f, 50.0f),
                       std::bind(&PreGame::leaveRoom, this),
                       "./resources/leave_button.png");
    _menu.update(_players);
  }
}
