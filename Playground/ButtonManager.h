#include <SFML\Graphics.hpp>
#include "Button.h"

class ButtonManager : public sf::Drawable, public sf::Transformable
{
private:
	
	sf::Text text;
	sf::Vector2f worldPos;

	sf::Sprite sprite;

public:
	std::vector<Button> towerButtons;
	std::vector<Button> enemyButtons;
	ButtonManager(){
	}

	ButtonManager(sf::Texture &incTexture, sf::Font &incFont){		
		
		std::string towerNames[] = {"Tower1", "Tower2", "Tower3"};
		towerButtons = std::vector<Button>((sizeof(towerNames)/sizeof(*towerNames)));

		std::string enemyNames[] = {"Enemy1", "Enemy2", "Enemy3"};
		enemyButtons = std::vector<Button>((sizeof(enemyNames)/sizeof(*enemyNames)));


		for(int i = 0; i < (sizeof(towerNames)/sizeof(*towerNames)); i++){
			towerButtons[i].text.setString(towerNames[i]);
			towerButtons[i].text.setFont(incFont);
			towerButtons[i].text.setCharacterSize(20);
			towerButtons[i].text.setStyle(sf::Text::Bold);
			towerButtons[i].text.setColor(sf::Color::Black);
			towerButtons[i].text.setPosition((150 * i + 18.0f), (750 + 35.0f));
			towerButtons[i].sprite.setTexture(incTexture);
			towerButtons[i].sprite.setPosition(sf::Vector2f(150 * i , 750));
			towerButtons[i].buttonNumber = i;  

			enemyButtons[i].text.setString(enemyNames[i]);
			enemyButtons[i].text.setFont(incFont);
			enemyButtons[i].text.setCharacterSize(20);
			enemyButtons[i].text.setStyle(sf::Text::Bold);
			enemyButtons[i].text.setColor(sf::Color::Black);
			enemyButtons[i].text.setPosition((590 + (150 * i) + 18.0f), (750 + 35.0f));
			enemyButtons[i].sprite.setTexture(incTexture);
			enemyButtons[i].sprite.setPosition(sf::Vector2f(600 + (150 * i) , 750));
			enemyButtons[i].buttonNumber = i;
		}
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{		
		for(Button btn : towerButtons){
			btn.draw(target, states);
		}
		for(Button btn : enemyButtons){
			btn.draw(target, states);
		}
	}
};