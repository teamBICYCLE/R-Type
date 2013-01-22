#ifndef  __PRE_GAME__
# define __PRE_GAME__

# include <string>
#include <map>
#include <system/network/Tcp.hh>
#include <system/network/Addr.hh>
#include <system/network/Listener.hh>
#include "Room.hh"

class PreGame
{
public:
	PreGame(const std::string &ip = "localhost", const std::string &port = "4242");
	PreGame(const PreGame &other);
	PreGame(PreGame &&other);
	PreGame &operator=(PreGame other);
	friend void  swap(PreGame &lhs, PreGame &rhs);
	virtual ~PreGame(void);

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

private:
  void roomlistDispatch(const std::string& command);
  void roomlistStart();
  void roomlistAppend(const std::string& roomdetails);
  void roomlistEnd();

private:
	TBSystem::network::Listener _listener;
	std::shared_ptr<TBSystem::network::sockets::ITcpSocket> _socket;
  std::string _commandLine;
	bool _gameIsLaunched;
  int _id;
  std::list<Room> _rooms;

private:
	std::map<std::string, std::function<void (const std::string &)>> _cmdType;
	std::map<std::string, std::function<void (const std::string &)>> _responseMap;
	std::map<std::string, std::function<void (const std::string &)>> _roomlistMap;
};

#endif /*!__PRE_GAME__ */
