#ifndef  __PRE_GAME__
# define __PRE_GAME__

# include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <system/network/Tcp.hh>
#include <system/network/Addr.hh>
#include <system/network/Listener.hh>
#include "View.hh"
#include "Room.hh"

class PreGame
{
public:
  enum state {
    eHALLWAY,
    eROOM
  };

	PreGame(const std::string &ip = "localhost", const std::string &port = "4242");
	~PreGame(void);

public:
	void run(void);

private:
	void disconnected(void);
	bool read(std::shared_ptr<TBSystem::network::sockets::ITcpSocket> &socket);

	void handleMsg(const std::string &msg);
	void handleNotif(const std::string &notif);
	void handleWelcome(const std::string &welcome);
	void handleError(const std::string &error);
	void handleResponse(const std::string &response);
  void handleGamestart(const std::string& id);

private:
  void updateHallway(void);
  void updateRoom(void);

private:
  void createRoom(void);
  void startGame(void);
  void leaveRoom(void);
  void requestRoomlist(void);
  void requestRoomdetails(int roomId);

private:
  void tryJoinRoom(int roomId);
  void joinRoom(const std::string& id);
  void roomlistDispatch(const std::string& command);
  void roomlistStart();
  void roomlistAppend(const std::string& roomdetails);
  void roomlistEnd();

private:
  void roomdetailsDispatch(const std::string& command);
  void roomdetailsStart(void);
  void roomdetailsAppend(const std::string& player);
  void roomdetailsEnd(void);

private:
	TBSystem::network::Listener _listener;
	std::shared_ptr<TBSystem::network::sockets::ITcpSocket> _socket;
  std::string _commandLine;
	bool _gameIsLaunched;
  int _id;
  int _currentRoom;
  state           _state;
  std::list<Room> _rooms;
  std::list<gooey::Player> _players;
  std::string _serverIp;

private:
	std::map<std::string, std::function<void (const std::string &)>> _cmdType;
	std::map<std::string, std::function<void (const std::string &)>> _responseMap;
	std::map<std::string, std::function<void (const std::string &)>> _roomlistMap;
	std::map<std::string, std::function<void (const std::string &)>> _roomdetailsMap;

private:
  sf::RenderWindow _window;
  View            _menu;
};

#endif /*!__PRE_GAME__ */
