#include <SFML\Graphics.hpp>
#include "ButtonManager.h"

class InputManager : public sf::Drawable, public sf::Transformable
{

private:

	int tileSizex, tileSizey, xPos, yPos, textureSizex, textureSizey;

	ButtonManager buttonManager;

	sf::Vector2f mousePos;
	sf::Vector2f targetTowerPos;

	bool wasButtonPressed;
	bool wasTButtonPressed;
	bool MouseLeftButtonPressed;
	bool MouseRightButtonPressed;

public:

	sf::Vector2f worldPos;

	TowerManager *towerManager;
	EnemyManager *enemyManager;
	std::vector<std::vector<Tile>> *tile;

	std::vector<Button> buttons;

	sf::Texture testingTex;
	
	sf::Text text;

	sf::Sprite sprite;
	sf::Font font;

	InputManager(){
	}

	InputManager(TowerManager &incTowerManager, EnemyManager &incEnemyManager, std::vector<std::vector<Tile>> &incTile, sf::Text &incText, int incTileSizex, int incTileSizey, int incTextureSizex, int incTextureSizey, sf::Texture &incTexture, sf::Font &incFont)
		:tileSizex(incTileSizex), tileSizey(incTileSizey), textureSizex(incTextureSizex), textureSizey(incTextureSizey), enemyManager(&incEnemyManager), towerManager(&incTowerManager), tile(&incTile), text(incText){
		buttonManager = ButtonManager(incTexture, incFont);
	}

	bool IsValid(int xPos, int yPos){
		if(xPos > -1 && xPos < tileSizex && yPos > -1 && yPos < tileSizey)
			return true;
		return false;
	}

	void update(sf::Time &dt, sf::RenderWindow &window, sf::Event event)
	{
		worldPos = getWorldPos(window);
		mousePos = getMousePos(window);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !MouseLeftButtonPressed)
		{
			if(windowBounds(worldPos))			
			{
				bool insideButton = false;
				for(Button btn : buttonManager.towerButtons){
					if(btn.sprite.getGlobalBounds().contains(worldPos)){
						towerManager->AddTower(btn.buttonNumber, targetTowerPos);
						(*tile)[xPos][yPos].sprite.setColor(sf::Color::Black);
						insideButton = true;
					}
				}
				for(Button btn : buttonManager.enemyButtons){
					if(btn.sprite.getGlobalBounds().contains(worldPos)){						
						enemyManager->SpawnEnemy(btn.buttonNumber);
					}
				}
				if(!insideButton){
					if(IsValid(xPos, yPos))
						(*tile)[xPos][yPos].sprite.setColor(sf::Color::White);
					xPos = int(mousePos.x);
					yPos = int(mousePos.y);
					targetTowerPos = mousePos;
					(*tile)[xPos][yPos].sprite.setColor(sf::Color::Green);
				}
				MouseLeftButtonPressed = true;
			}
		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && MouseLeftButtonPressed)
			MouseLeftButtonPressed = false;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			towerManager->ClearTowers();
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		buttonManager.draw(target, states);
	}
	sf::Vector2i getPixelPos(sf::RenderWindow &window){
		return sf::Mouse::getPosition(window);
	}

	sf::Vector2f getWorldPos(sf::RenderWindow &window){
		return window.mapPixelToCoords(getPixelPos(window));
	}

	sf::Vector2f getMousePos(sf::RenderWindow &window){
		return sf::Vector2f(getWorldPos(window).x / ((textureSizex * (tileSizex * 10)) / (tileSizex * 10)),
			getWorldPos(window).y / ((textureSizex * (tileSizex * 10)) / (tileSizex * 10)));
	}

	bool windowBounds(sf::Vector2f worldPos){
		 if(worldPos.x < (textureSizex * tileSizex) &&
				worldPos.x > 0 &&
				worldPos.y < (textureSizey * tileSizey) &&
				worldPos.y > 0)
				return true;
		 return false;
	}
};