#include <SFML\Graphics.hpp>

class Shoot
{

public:

	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f spritePos;
	sf::Vector2f enemyPosition;
	sf::Vector2f shootVec;
	sf::Texture texture;
	float velocity;
	Enemy *enemy;
	bool destroyed, enemyLiving;
	int damage;

	int hitRange;

	Shoot::Shoot(){
	}

	Shoot::Shoot(Enemy &incEnemy, sf::Vector2f incPosition, 
		sf::Texture &incTexture, float incVelocity) 
		: shootVec(0,0), velocity(incVelocity), destroyed(false), 
		enemy(&incEnemy), position(incPosition), damage(1), hitRange(15), enemyLiving(true)
	{
		sprite.setTexture(incTexture);
		sprite.setTextureRect(sf::IntRect(25, 0 , 25, 25));
		sprite.setPosition(incPosition);
	}

	void update(sf::Time dt)
	{
		if(enemyLiving){
			ShootEvent(enemy->position);
		} else {
			ShootEvent(enemyPosition);
		}
		if(&enemy->destroyed)
		{
			enemyPosition = enemy->position;
			enemyLiving = false;
		}
		spritePos = sprite.getPosition();
	}

	void ShootEvent(sf::Vector2f incVector){
		float distance = std::sqrt(
			(incVector.x-position.x)*
			(incVector.x-position.x)+ 
			(incVector.y-position.y)*
			(incVector.y-position.y));
		shootVec = velocity * (enemy->position - sprite.getPosition()) / distance;
		sprite.move(shootVec);

		float shootdistance = std::sqrt(
			(incVector.x-sprite.getPosition().x)*
			(incVector.x-sprite.getPosition().x)+ 
			(incVector.y-sprite.getPosition().y)*
			(incVector.y-sprite.getPosition().y));
		if(shootdistance < hitRange || enemy->health <= 0){
			destroyed = true;
			enemy->health--;
		}
	}

	/*
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		target.draw(sprite);
	}*/
private:

};
