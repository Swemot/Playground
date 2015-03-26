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
	//float shootTimer;
	sf::Time elapsedTime;
	int x, y;
	sf::Time shootTimer;
	Tower::Tower(){
	}

	Tower::Tower(float incTowerRadius, sf::Vector2f incPosition, float incVelocity, float incShootDelay, sf::Vector2f incMousePos)
		: haveEnemy(false), velocity(incVelocity), shootVec(0,0), position(incPosition),
		shoot(false), x((int)incMousePos.x), y((int)incMousePos.y){
		enemy = nullptr;
		circle.setRadius(incTowerRadius);
		circle.setOrigin(incTowerRadius / 2, incTowerRadius / 2);
		circle.setPosition(incPosition);
		shootTimer = sf::seconds(incShootDelay);
	}

	bool getExist(){
		if(tower)
			return true;
	}

private:

};
