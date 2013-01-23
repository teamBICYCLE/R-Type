#include "Button.hh"
#include "ListView.hh"
#include "ListItem.hh"
#include "View.hh"
#include <functional>
#include <SFML/Graphics.hpp>
#include <system/log/Log.hh>
#include <system/network/Listener.hh>
#include <system/network/Tcp.hh>
#include <system/network/Addr.hh>
#include <iostream>
#include "PreGame.hh"
#ifdef _WIN32
# include <tchar.h>
#endif

std::string resourcesPath;

#ifdef _WIN32LOL
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	TCHAR cmdline[4096] ;
    TCHAR* argv[4096] ;
    int argc = 0 ;
    _tcscpy( cmdline, GetCommandLine() ) ;
    argv[argc] = _tcstok( cmdline, TEXT(" \t") ) ;
    while( argv[argc] != 0 )
    {
        argc++ ;
        argv[argc] = _tcstok( 0, TEXT(" \t") ) ;
    }
#endif
//#elif defined __gnu_linux__
int main(int argc, char* argv[])
{
//#endif
  if (argc < 4) {
    TBSystem::log::err << "Usage: ./client <ip> <port> <resources_path>" << TBSystem::log::endl;
    return EXIT_FAILURE;
  }
  TBSystem::log::err << argv[1] << " " << argv[2] << " " << argv[3] << TBSystem::log::endl;
  resourcesPath = argv[3];
  try {
    PreGame  pregame(argv[1], argv[2]);

    pregame.run();
  }
  catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return EXIT_SUCCESS;
}
