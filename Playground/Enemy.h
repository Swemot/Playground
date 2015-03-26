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

	Enemy::Enemy(sf::Texture &texture, int incSpeed, std::vector<Tile> incpathList) 
		: endMovementCycle(incSpeed), currMovementCycle(0), destroyed(false), pathList(incpathList), position(0,0), health(3){
		sprite.setPosition(0,0);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(50 ,0, 25, 25));
		currentNode = pathList[pathList.size()-1];
		pathList.pop_back();
		currPath = currentNode.position - sprite.getPosition();
	}

	//void update(sf::Time dt)
	//{
	//	if(test == speed)
	//	{
	//		if(!pathList.empty())
	//		{
	//			currPath = currentNode.position - sprite.getPosition() ;
	//			currentNode = pathList[pathList.size()-1];
	//			pathList.pop_back();
	//			tempVec.x = currPath.x / speed;
	//			tempVec.y = currPath.y / speed;				
	//			test = 0;
	//		}
	//		else
	//		{
	//			currPath = currentNode.position - sprite.getPosition() ;
	//			tempVec.x = currPath.x / speed;
	//			tempVec.y = currPath.y / speed;
	//		}
	//	}
	//	if(test == speed * 2)
	//	{
	//		destroyed = true;
	//	}
	//	test++;
	//	sprite.move(tempVec);
	//}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		target.draw(sprite);
	}

	void setPath(std::vector<Tile> incpathList)
	{
		pathList = incpathList;
	}

private:

};
