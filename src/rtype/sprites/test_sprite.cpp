
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Board.hh"


int main(void)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	Sprite::Board sprite("teambicycle.png", "config.cfg");

	Sprite::AnimationInfos *animInfos = sprite.generateAnimInfo();
	animInfos->setAnimationName("destroy");
	animInfos->startAnimation();
	Sprite::AnimationInfos *moveanim = sprite.generateAnimInfo();
	if (!moveanim->setAnimationName("move"))
		return 0;
	moveanim->startAnimation();

	// sf::Texture _texture;
	//  _texture.loadFromFile("teambicycle.png");
	// sf::Sprite _board;
	// _board.setTexture(_texture);

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
 	     //	window.draw(animInfos.getRect());
	// sprite.getSprite();
		window.draw(animInfos->getSprite());
	    window.draw(moveanim->getSprite());

	    window.display();
	}
	return (0);
}