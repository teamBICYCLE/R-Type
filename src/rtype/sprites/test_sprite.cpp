
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Board.hh"
#include "AnimationManager.hh"


#include <iostream>
int main(void)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	Sprite::AnimationManager toto;

	toto.addSourceFolder("testloading");
	Sprite::AnimationInfos	*anim1 = toto["testloading/r-typesheet22.png"]->generateAnimInfo();
	Sprite::AnimationInfos	*anim2 = toto["testloading/r-typesheet22.png"]->generateAnimInfo();


	if (anim1->setAnimationName("destroy") && anim2->setAnimationName("move"))
	{
		anim1->startAnimation();
		anim2->startAnimation();

	while (window.isOpen())
	{
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
		    	window.close();
		          // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		          // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		          //   sprite.move(1,0);
		          // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		          //   sprite.move(0,-1);
		          // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		          //   sprite.move(0,1);
		}
	    window.clear(sf::Color::White);
	    window.draw(anim1->getSprite());
	    // window.draw(anim2->getSprite());
		// window.draw(toto["testloading/teambicycle.png"].getAnimInfo()->getSprite());
		// window.draw(toto["testloading/Screenshot.png"].getAnimInfo()->getSprite());
	    window.display();
	}
}else
 std::cout << "fail" << std::endl;
	return (0);
}