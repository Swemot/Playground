#include <SFML\Graphics.hpp>
#include <list>
#include "Tower.h"
#include "Shoot.h"

class TowerManager : public sf::Drawable, public sf::Transformable
{

public:

	int textureSizex, textureSizey;
	float tempDistance, shootdistance;
	//std::vector<std::vector<Tower>> towers;
	std::vector<Tower> towers;
	std::deque<Enemy> *getEnemies;
	sf::Texture towerTexture, shootTexture;
	std::list<Shoot> shoots;
	Enemy *temp;
	TowerManager()
	{
	}

	TowerManager(std::deque<Enemy> &incEnemyList, std::vector<std::vector<Tile>>& incTile, sf::Texture &incTowerTexture, sf::Texture &incShootTexture, int textureSizex, int textureSizey) 
		: towerTexture(incTowerTexture), textureSizex(textureSizex), 
		textureSizey(textureSizey), getEnemies(&incEnemyList), shootTexture(incShootTexture)
	{
	}

	float CalculateDistance(sf::Vector2f incVec1, sf::Vector2f incVec2){
		return std::sqrt(
			(incVec1.x-incVec2.x) * 
			(incVec1.x-incVec2.x) +
			(incVec1.y-incVec2.y) *
			(incVec1.y-incVec2.y));
	}

	void update(sf::Time &dt)
	{
		for(Tower &tower : towers){
			if(tower.enemy != nullptr)
				if(tower.enemy->health <= 0){
					tower.enemy = nullptr;
					tower.haveEnemy = false;						
				}
			if(tower.tower && !tower.haveEnemy){
				if(!getEnemies->empty()){
					for(auto &e : *getEnemies){
						float distance = CalculateDistance(e.position, tower.position);
						if(distance < tower.circle.getRadius()){
							tower.enemy = &e;
							tower.haveEnemy = true;
						}
					}
				}
			}
			if(tower.tower && tower.haveEnemy){
				if(getEnemies->size() > 0){
					temp = tower.enemy;					
					float distance = CalculateDistance(temp->position, tower.position);
					if(distance > tower.circle.getRadius() || temp->destroyed){
						tower.enemy = nullptr;
						tower.haveEnemy = false;
					} else {						
						if(tower.elapsedTime >= tower.shootTimer){
							shoots.push_back(
								Shoot(*temp, 
								tower.position, 
								shootTexture, 
								tower.velocity));
							tower.elapsedTime = sf::seconds(0);
						}
					}
				}else{
					tower.enemy = nullptr;
					tower.haveEnemy = false;
				}				
			}
			tower.elapsedTime += dt;
		}
		
		for(std::list<Shoot>::iterator it=shoots.begin(); it!=shoots.end();){
			if(getEnemies->size() > 0)
				it->update(dt);
			else
				it->destroyed = true;
			if(it->destroyed)
				it = shoots.erase(it);
			else
				it++;
		}
	}
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{		
		for(auto &t : towers)
		{
			target.draw(t.circle);
			target.draw(t.sprite);			
		}
		for(auto &s : shoots)
		{
			target.draw(s.sprite);
		}
	}

	void ClearTowers(){
		towers.clear();
	}

	void AddTower(int incTowerNumber, sf::Vector2f incMousePos){
		switch(incTowerNumber){
			case Tower0:{
				float towerRadius = 100;
				sf::Vector2f position = sf::Vector2f((int)incMousePos.x * textureSizex, (int)incMousePos.y * textureSizex );
				float velocity = 5.0f;
				float shootTimer = 0.1f;
				towers.push_back(Tower(
					towerRadius, 
					position, 
					velocity, 
					shootTimer, 
					incMousePos, 
					towerTexture, 
					incTowerNumber,
					textureSizex, 
					textureSizey));
				break;
			}
			case Tower1:{
				float towerRadius = 300;
				sf::Vector2f position = sf::Vector2f((int)incMousePos.x * textureSizex, (int)incMousePos.y * textureSizex );
				float velocity = 10.0f;
				float shootTimer = 0.75f;
				towers.push_back(Tower(
					towerRadius,
					position, 
					velocity, 
					shootTimer, 
					incMousePos, 
					towerTexture, 
					incTowerNumber,
					textureSizex, 
					textureSizey));
				break;
			}case Tower2:{

				break;
			}
		}
	}

private:

	enum TowerNumber { Tower0, Tower1, Tower2};

private:

};