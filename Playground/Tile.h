#include <SFML\Graphics.hpp>

class Tile : public sf::Drawable, public sf::Transformable
{
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	bool shortest, wall, tower, haveEnemy;
	int value, x, y, weight, heuristic, parentX, parentY;
	float distance;
	Tile *parent;

	Tile::Tile() 
		: shortest(false), value(0), x(0), y(0), weight(0), 
		heuristic(0), wall(false), parentX(0), parentY(0), 
		tower(false), haveEnemy(false), parent(nullptr)
	{
	}


	//void getEnemyList(std::vector<Enemy> incEnemies)
	//{
	//	enemies = incEnemies;
	//}
/*
	bool setRad(sf::Vector2f incVec)
	{
		float dist = std::distance(incVec, circle.getOrigin);
		if ( dist < circle.radius )
	}
*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		target.draw(sprite);
	}

	friend bool operator == (const Tile& n1, const Tile& n2) 
	{
        return (n1.x == n2.x && n1.y == n2.y);
	}

	bool operator < (const Tile& lhs) 
	{ 
		return (value < lhs.value); 
	}

private:
};
