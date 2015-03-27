#include <SFML\Graphics.hpp>
#include <thread>

class EnemyManager : public sf::Drawable, public sf::Transformable
{
public:

	std::deque<Enemy> *enemies;
	std::vector<std::vector<Tile>> tile;
	std::vector<Tile> pathList;
	std::vector<Tile> openList;
	std::vector<Tile> closedList;	
	sf::Texture enemyTexture;
	int stopX, stopY, tileSizex, tileSizey;

	bool algoSearch;
	bool pathFound;
	bool pathExist;
	Tile currentNode;

	EnemyManager::EnemyManager() : algoSearch(false), pathFound(false)
	{
	}

	EnemyManager::EnemyManager(std::deque<Enemy> &incEnemyList, sf::Texture incTexture, int tileSizex, int tileSizey)
		: enemyTexture(incTexture), tileSizex(tileSizex), tileSizey(tileSizey), algoSearch(false), pathFound(false), enemies(&incEnemyList), pathExist(false) {
	}

	void update(sf::Time &dt){
		for(std::deque<Enemy>::iterator it=enemies->begin(); it!=enemies->end();){
			//IF currMovementCycle  == endMovementCycle
			if(NewCycle(it)){
				//IF pathlist is empty
				if(PathListIsEmpty(it)){
					EnemyGetNewPath(it);
				} else {
					EnemyMovePath(it);					
				}
			}
			if(FinishedCycle(it) || EnemyHealthGone(it)){
				it->destroyed =  true;
			} else {	
				EnemyMoveSprite(it);
			}
			it++;
		}
		
		for(std::deque<Enemy>::iterator it=enemies->begin(); it!=enemies->end();){
			if(it->destroyed)
				it = enemies->erase(it);
			else
				it++;
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		for(auto &e : *enemies)
		{
			target.draw(e.sprite);
		}
	}

	void SpawnEnemy(int incEnemyNumber)
	{
		if(pathExist)
			switch(incEnemyNumber){
				case Enemy0:{
					enemies->push_back(Enemy(enemyTexture, 100, pathList, 3, incEnemyNumber));
					break;
				}
				case Enemy1:{
					enemies->push_back(Enemy(enemyTexture, 50, pathList, 6, incEnemyNumber));
					break;
				}
			}
			
	}

	void EnemyGetNewPath(std::deque<Enemy>::iterator incIterator){
		incIterator->currPath = incIterator->currentNode.position - incIterator->sprite.getPosition();
		incIterator->currentNode = incIterator->pathList[incIterator->pathList.size()-1];
		incIterator->pathList.pop_back();

		incIterator->tempVec = sf::Vector2f(incIterator->currPath.x / incIterator->endMovementCycle, incIterator->currPath.y / incIterator->endMovementCycle);

		incIterator->currMovementCycle = 0;
	}
	void EnemyMovePath(std::deque<Enemy>::iterator incIterator){
		incIterator->currPath = incIterator->currentNode.position - incIterator->sprite.getPosition();
		incIterator->tempVec = sf::Vector2f(incIterator->currPath.x / incIterator->endMovementCycle, incIterator->currPath.y / incIterator->endMovementCycle);
	}
	bool NewCycle(std::deque<Enemy>::iterator incIterator){
		if(incIterator->currMovementCycle == incIterator->endMovementCycle)
			return true;
		return false;
	}
	bool PathListIsEmpty(std::deque<Enemy>::iterator incIterator){
		if(incIterator->pathList.empty())
			return false;
		return true;		
	}
	bool FinishedCycle(std::deque<Enemy>::iterator incIterator){
		if(incIterator->currMovementCycle == incIterator->endMovementCycle * 2)
			return true;
		return false;
	}
	bool EnemyHealthGone(std::deque<Enemy>::iterator incIterator){
		if(incIterator->health <= 0)
			return true;
		return false;
	}
	void EnemyMoveSprite(std::deque<Enemy>::iterator incIterator){
		incIterator->currMovementCycle++;
		incIterator->position += incIterator->tempVec;
		incIterator->sprite.move(incIterator->tempVec);
	}
	void aStar()
	{
		while(true)
		{
			openList.erase(std::remove(openList.begin(), openList.end(), currentNode), openList.end());
			closedList.push_back(currentNode);

			std::vector<Tile> neighbor = SearchNeighbor(currentNode);

			for(auto &n : neighbor)
			{
				if (!n.wall && (std::find(closedList.begin(), closedList.end(), n)==closedList.end()))
				{
					if ((std::find(openList.begin(), openList.end(), n)==openList.end()))
					{
						tile[n.x][n.y].parentX = currentNode.x;
						tile[n.x][n.y].parentY = currentNode.y;

						n.parentX = currentNode.x; 
						n.parentY = currentNode.y;

						n.weight = n.weight + currentNode.weight;
						n.heuristic = 1 * (std::abs(n.x - stopX) + std::abs(n.y - stopY));
						n.value = n.weight + n.heuristic;
						openList.push_back(n);
					}
				}
			}

			if(!openList.empty())
			{
				std::vector<Tile> sortedList;
				sortedList = openList;
				std::sort(sortedList.begin(), sortedList.end());
				sortedList[0].shortest = true;
				currentNode = sortedList[0];
			}

			if(currentNode.x == stopX && currentNode.y == stopY)
			{
				DrawPath();
				break;
			}
		}
	}

	void DrawPath()
	{
		pathList.clear();
		while(true)
		{
			if(currentNode.x == 0 && currentNode.y == 0)
			{
				pathFound = false;
				break;
			}
			else
			{
				pathList.push_back(currentNode);			
			}
			currentNode = tile[currentNode.parentX][currentNode.parentY];
		}
		//senemies->push_back(Enemy(texture, 15, pathList));
	}

	void rerunAlgorithm(std::vector<std::vector<Tile>> &swelist, int startX, int startY, int stopX, int stopY)
	{
		closedList.clear();
		openList.clear();
		tile = swelist;
		for(int x = 0; x < tileSizex; x++)
		{
			for(int y = 0; y < tileSizey; y++)
			{
				if(!tile[x][y].wall)
				{
					tile[x][y].weight = 0;
					tile[x][y].heuristic = 0;
					tile[x][y].value = 0;
					tile[x][y].parentX = 0;
					tile[x][y].parentY = 0;
				}
			}
		}
		currentNode = tile[startX][startY];
		openList.push_back(currentNode);
		this->stopX = stopX;
		this->stopY = stopY;

		std::thread Thread(&EnemyManager::aStar, this);

		Thread.join();
		Thread.~thread();
		pathExist = true;
	}

	std::vector<Tile> SearchNeighbor(Tile currentNode)
	{
		//Nondiagonal

		std::vector<Tile> neighbor;
		if (currentNode.x - 1 >= 0)
		{
			if ((std::find(openList.begin(), openList.end(), tile[currentNode.x - 1][currentNode.y])==openList.end()))
			{				

				tile[currentNode.x - 1][currentNode.y].weight = 10;
			}
			neighbor.push_back(tile[currentNode.x - 1][currentNode.y]);
		}
		if (currentNode.x + 1 < tileSizex)
		{
			if ((std::find(openList.begin(), openList.end(), tile[currentNode.x + 1][currentNode.y]) == openList.end()))
			{
				tile[currentNode.x + 1][currentNode.y].weight = 10;
			}
			neighbor.push_back(tile[currentNode.x + 1][currentNode.y]);
		}
		if (currentNode.y - 1 >= 0)
		{
			if ((std::find(openList.begin(), openList.end(), tile[currentNode.x][currentNode.y - 1]) == openList.end()))
			{
				tile[currentNode.x][currentNode.y - 1].weight = 10;
			}
			neighbor.push_back(tile[currentNode.x][currentNode.y - 1]);
		}
		if (currentNode.y + 1 < tileSizey)
		{
			if ((std::find(openList.begin(), openList.end(), tile[currentNode.x][currentNode.y + 1]) == openList.end()))
			{
				tile[currentNode.x][currentNode.y + 1].weight = 10;
			}
			neighbor.push_back(tile[currentNode.x][currentNode.y + 1]);
		}

		//Diagonal
		/*
		if (currentNode.x - 1 >= 0 && currentNode.y + 1 < tileSizex)
		{
			if ((std::find(openList.begin(), openList.end(), tile[currentNode.x - 1][currentNode.y + 1]) == openList.end()))
			{
				tile[currentNode.x - 1][currentNode.y + 1].weight = 14;
			}
			neighbor.push_back(tile[currentNode.x - 1][currentNode.y + 1]);
		}
		if (currentNode.x + 1 < tileSizex && currentNode.y + 1 < tileSizex)
		{
			if ((std::find(openList.begin(), openList.end(), tile[currentNode.x + 1][currentNode.y + 1]) == openList.end()))
			{
				tile[currentNode.x + 1][currentNode.y + 1].weight = 14;
		}
			neighbor.push_back(tile[currentNode.x + 1][currentNode.y + 1]);
		}
		if (currentNode.x - 1 >= 0 && currentNode.y - 1 >= 0)
		{
			if ((std::find(openList.begin(), openList.end(), tile[currentNode.x - 1][currentNode.y - 1]) == openList.end()))
			{
				tile[currentNode.x - 1][currentNode.y - 1].weight = 14;
			}
			neighbor.push_back(tile[currentNode.x - 1][currentNode.y - 1]);
		}
		if (currentNode.x + 1 < tileSizey && currentNode.y - 1 >= 0)
		{
			if ((std::find(openList.begin(), openList.end(), tile[currentNode.x + 1][currentNode.y - 1]) == openList.end()))
			{
				tile[currentNode.x + 1][currentNode.y - 1].weight = 14;
			}
			neighbor.push_back(tile[currentNode.x + 1][currentNode.y - 1]);
		}*/
		return neighbor;
	}

private:

	enum EnemyNumber { Enemy0, Enemy1, Enemy2};

};
