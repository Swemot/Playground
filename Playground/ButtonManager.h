#include <SFML\Graphics.hpp>
#include "Button.h"

class ButtonManager : public sf::Drawable, public sf::Transformable
{
private:
	
	sf::Text text;
	sf::Vector2f worldPos;

	sf::Sprite sprite;

public:
	std::vector<Button> buttons;
	ButtonManager(){
	}

	ButtonManager(sf::Texture &incTexture, sf::Font &incFont){
		std::string stringArr[] = {"Tower1", "Tower2", "Tower3"};
		
		buttons = std::vector<Button>((sizeof(stringArr)/sizeof(*stringArr)));

		for(int i = 0; i < (sizeof(stringArr)/sizeof(*stringArr)); i++){
			buttons[i].text.setString(stringArr[i]);
			buttons[i].text.setFont(incFont);
			buttons[i].text.setCharacterSize(20);
			buttons[i].text.setStyle(sf::Text::Bold);
			buttons[i].text.setColor(sf::Color::Green);
			buttons[i].text.setPosition((150 * i + 18.0f), (750 + 35.0f));

			buttons[i].sprite.setTexture(incTexture);
			buttons[i].sprite.setPosition(sf::Vector2f(150 * i , 750));
			buttons[i].buttonNumber = i;  
		}
	}

	void update(sf::Clock dt){		
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{		
		for(Button btn : buttons){
			btn.draw(target, states);
		}
	}
};