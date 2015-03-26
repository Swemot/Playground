#include <SFML\Graphics.hpp>
#include "TransformableAndDrawable.h"
#include "Tile.h"
#include <math.h>

class Block : public sf::Drawable, public sf::Transformable
{
public:
	sf::VertexArray m_vertices;
	sf::Texture m_texture;
	sf::Sprite sprite;

	std::vector<std::vector<Tile>> tile;

	Block()
	{
	}

	//Block::Block(std::vector<std::vector<Tile>> tile)
	//{		
	//	this->tile = tile;
	//}

	void update(sf::Time dt)
	{
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
	}

private:
};
