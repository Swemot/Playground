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
				for(Button btn : buttonManager.buttons){
					if(btn.sprite.getGlobalBounds().contains(worldPos)){
						towerManager->AddTower(btn.buttonNumber, targetTowerPos);
						(*tile)[xPos][yPos].sprite.setColor(sf::Color::Black);
						insideButton = true;
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
				//PlaceTile();
				MouseLeftButtonPressed = true;
			}
			/*for(Button btn : buttons){
				if(btn.sprite.getGlobalBounds().contains(worldPos)){
					btn.text.setString(std::to_string(worldPos.x) + " " + std::to_string(worldPos.y));
				}
			}*/
		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && MouseLeftButtonPressed)
			MouseLeftButtonPressed = false;
		/*
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !MouseRightButtonPressed)
		{
			if(windowBounds(worldPos))
			{
				enemyManager->rerunAlgorithm(*tile, 0, 0, (int)mousePos.x, (int)mousePos.y);
			}
			MouseRightButtonPressed = true;
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && MouseRightButtonPressed)
			MouseRightButtonPressed = false;
		*/
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !wasButtonPressed)
		{
			enemyManager->spawnEnemy();
			wasButtonPressed = true;
		}
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F) && wasButtonPressed)
			wasButtonPressed = false;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			//ResetTiles();
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		buttonManager.draw(target, states);
	}

	/*
	void ResetTiles(){
		for(Tower t : towerManager->towers){
			(*tile)[t.x][t.y].tower = false;				
		}

		towerManager->towers.clear();
	}
	
	void PlaceTile(){
		(*tile)[(int)mousePos.x][(int)mousePos.y].sprite.setColor(sf::Color::Green);
		(*tile)[(int)mousePos.x][(int)mousePos.y].wall = true;
		towerManager->towers[(int)mousePos.x][(int)mousePos.y].tower = true;

		for(int i = 0; i < enemyManager->pathList.size(); i++){
			if(enemyManager->pathList[i].x == (int)mousePos.x && enemyManager->pathList[i].y == (int)mousePos.y){
				enemyManager->rerunAlgorithm(*tile, 0, 0, 19, 19);
			}
		}
	}*/

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