#include <SFML\Graphics.hpp>
#include <deque>
#include "Camera.h"
#include "Tile.h"
#include "Enemy.h"
#include "TowerManager.h"
#include "EnemyManager.h"
#include "InputManager.h"


class Game
{
public:
	Camera camera;
	InputManager inputManager;
	EnemyManager enemyManager;
	TowerManager towerManager;

	sf::Texture groundTexture;
	sf::Texture towerTexture;
	sf::Texture enemyTexture;
	sf::Texture testingTex;

	sf::Sprite testingSprite;
	sf::Text text;
	sf::Font font;
	sf::CircleShape circle;

	int tileSizex, tileSizey, xPos, yPos, textureSizex, textureSizey;
	bool wasButtonPressed;
	bool wasTButtonPressed;
	bool MouseButtonPressed;

	int markedX, markedY;
	sf::Vector2f mousePos;
	sf::Vector2f worldPos;

	std::vector<std::vector<Tile>> tile;

	std::deque<Enemy> getEnemies;

	sf::Sprite sprite;

	Game()
	{
		groundTexture.loadFromFile("Texture/GroundTex.png");
		font.loadFromFile("arial.ttf");
		//font.loadFromFile("arial.ttf");
		testingTex.loadFromFile("Texture/testingTexture.png");
		towerTexture.loadFromFile("Texture/TowerTexture.png");
		enemyTexture.loadFromFile("Texture/EnemyTexture.png");

		tileSizex = 40, tileSizey = 40, textureSizex = 25, textureSizey = 25;

		tileCreate();

		enemyManager = EnemyManager(getEnemies, enemyTexture, tileSizex, tileSizey);
		towerManager = TowerManager(getEnemies, tile, towerTexture, groundTexture, textureSizex, textureSizey);
		inputManager = InputManager(towerManager, enemyManager, tile, text,  tileSizex, tileSizey, textureSizex, textureSizey, testingTex, font);
		enemyManager.rerunAlgorithm(tile, 0, 0, 19, 19);
		tile[19][19].sprite.setColor(sf::Color::Red);
	}

	void update(sf::Time &dt, sf::RenderWindow &window, sf::Event event)
	{
		camera.update(dt, event);
		enemyManager.update(dt);
		towerManager.update(dt);
		inputManager.update(dt, window, event);
	}

	virtual void draw(sf::RenderWindow &window)
	{		
		for(int x = 0; x < tileSizex; x++)
			for(int y = 0; y < tileSizey; y++)
			{
				window.draw(tile[x][y]);
			}		
		window.draw(camera);		
		window.draw(towerManager);
		window.draw(enemyManager);
		window.draw(inputManager);
		window.draw(text);
		window.draw(circle);
		window.draw(sprite);
	}

	void tileCreate()
	{
		tile = std::vector<std::vector<Tile>> (tileSizex, std::vector<Tile>(tileSizey));
		for(int x = 0; x < tileSizex; x++)
			for(int y = 0; y < tileSizey; y++)
			{
				tile[x][y].sprite.setTexture(groundTexture);
				tile[x][y].sprite.setTextureRect(sf::IntRect(0,0,textureSizex,textureSizey));
				tile[x][y].sprite.setPosition((x * textureSizex),(y * textureSizey));
				tile[x][y].x = x;
				tile[x][y].y = y;
				tile[x][y].position = sf::Vector2f(x * textureSizex, y * textureSizey);
			}
	}

private:
};
 