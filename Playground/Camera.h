#include <SFML\Graphics.hpp>

class Camera : public sf::Drawable, public sf::Transformable
{
public:
	float speed;	
	sf::View view;
	float zoom;

	Camera()
	{
		speed = 300.0f;
		view.setCenter(sf::Vector2f(500,500));
		view.setSize(sf::Vector2f(1000, 1000));
	}

	void update(sf::Time dt, sf::Event event)
	{
		sf::Vector2f movement(0.f, 0.f);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			movement.x += speed;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			movement.x -= speed;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			movement.y += speed;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			movement.y -= speed;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
			view.zoom(0.99f);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
			view.zoom(1.01f);

		//if (event.type == sf::Event::MouseWheelMoved)
		//{

		//	zoom = event.mouseWheel.delta;

		//	if(zoom < event.mouseWheel.delta)
		//		view.zoom(0.99f);

		//	if(zoom > event.mouseWheel.delta)
		//		view.zoom(1.01f);

		//}

		view.move(movement * dt.asSeconds());
	}


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		target.setView(view);
	}

	private:

};
