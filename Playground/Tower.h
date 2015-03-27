#include <SFML\Graphics.hpp>
class Tower
{

public:
	sf::CircleShape circle;
	sf::Vector2f position;
	sf::Sprite sprite;
	bool haveEnemy, shoot, tower;
	Enemy *enemy;
	float velocity;
	sf::Vector2f shootVec;
	sf::Texture texture;
	sf::Time elapsedTime;
	int x, y;
	sf::Time shootTimer;
	
	Tower::Tower(){
	}

	Tower::Tower(float incTowerRadius, sf::Vector2f incPosition, float incVelocity, float incShootDelay, sf::Vector2f incMousePos, sf::Texture &incTexture, int incTowerNumber, int incTowerTextureSizeX, int incTowerTextureSizeY)
		: haveEnemy(false), velocity(incVelocity), shootVec(0,0), position(incPosition),
		shoot(false), x((int)incMousePos.x), y((int)incMousePos.y), texture(incTexture){
		enemy = nullptr;
		circle.setRadius(incTowerRadius);
		circle.setOrigin(incTowerRadius / 2, incTowerRadius / 2);
		circle.setPosition(incPosition - sf::Vector2f((incTowerRadius / 2) - (incTowerTextureSizeX / 2), (incTowerRadius / 2) - (incTowerTextureSizeY / 2)));
		circle.setFillColor(sf::Color(255, 0, 0, 64));
		shootTimer = sf::seconds(incShootDelay);
		sprite.setTexture(incTexture);
		sprite.setTextureRect(sf::IntRect(25 * incTowerNumber, 0, incTowerTextureSizeX, incTowerTextureSizeY));
		sprite.setPosition(incPosition);
		//shape.setBl
	}

	bool getExist(){
		if(tower)
			return true;
	}

private:

};
