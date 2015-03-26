#include <SFML\Graphics.hpp>


class Button{ 

public:
	sf::Vector2f worldPos;
	sf::Vector2f position;
	std::string buttonText;
	sf::Sprite sprite;
	sf::Text text;
	sf::Font font;
	sf::Texture texture;
	int buttonNumber;
	Button(){
	}

	Button(std::string buttonText, sf::Font &font, sf::Vector2f position, sf::Texture &texture)
	:font(font), texture(texture){
		text.setString(buttonText);
		text.setFont(font);
		text.setCharacterSize(20);
		text.setStyle(sf::Text::Bold);
		text.setColor(sf::Color::Green);
		text.setPosition((position.x + 18.0f), (position.y + 35.0f));

		sprite.setTexture(texture);
		sprite.setPosition(position);
		buttonNumber = 1;
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite);
		target.draw(text);
	}
private:
};