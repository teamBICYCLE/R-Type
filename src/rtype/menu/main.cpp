#include "Button.hh"
#include "ListView.hh"
#include "ListItem.hh"
#include "View.hh"
#include <functional>
#include <SFML/Graphics.hpp>

#include <iostream>

void	playCallback()
{
  std::cout << "==PLAY==" << std::endl;
}

void	quitCallback()
{
  std::cout << "==QUIT==" << std::endl;
}

void	listCallback()
{
  std::cout << "==LISTITEM CLICKED==" << std::endl;
}

int	main()
{
  sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML RType");
  View		view("../resources/menu_background.jpg", window.getSize(), sf::Vector2f(500.0,50.0));

  std::vector<void*>	test;

  test.push_back(new std::string("toto"));
  test.push_back(new std::string("toto"));
  test.push_back(new std::string("toto"));
  test.push_back(new std::string("toto"));

  view.setButtonOne(sf::Vector2f(100,100), std::bind(playCallback), "");
  view.setButtonTwo(sf::Vector2f(100,100), std::bind(quitCallback), "");
  view.setGlobalCallback(std::bind(listCallback));
  view.update(test);
  while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	  if (event.type == sf::Event::MouseButtonPressed)
	    view.clickEvent(sf::Mouse::getPosition(window));
	}
      window.clear();
      view.draw(window);
      window.display();
    }
 
  return EXIT_SUCCESS;
}
