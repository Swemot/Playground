#include <SFML\Graphics.hpp>

class Enemy
{

public:
	int currMovementCycle, endMovementCycle;
	sf::Sprite sprite;
	Tile currentNode;
	std::vector<Tile> pathList;
	bool hello, destroyed;;
	sf::Vector2f currPath, tempVec;
	sf::Vector2f position;
	int health;
	Enemy::Enemy()
	{
	}

	Enemy::Enemy(sf::Texture &texture, int incSpeed, std::vector<Tile> incpathList, int incHealth, int incEnemyNumber) 
		: endMovementCycle(incSpeed), currMovementCycle(0), destroyed(false), pathList(incpathList), position(-25,0), health(incHealth){
		sprite.setPosition(-25,0);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(incEnemyNumber * 25 ,0, 25, 25));
		currentNode = pathList[pathList.size()-1];
		pathList.pop_back();
		currPath = currentNode.position - sprite.getPosition();
	}
	void setPath(std::vector<Tile> incpathList)
	{
		pathList = incpathList;
	}

private:

};
