#include "background.h"
using namespace sf;
background::background(Vector2f size,String file,Vector2f pos)
{
	
	Texture texture;
	body.setSize(size);
	texture.loadFromFile("image/gbg.png");
	body.setTexture(&texture);
	body.setPosition(pos);

}
background::~background()
{
}

void background::ddraw(RenderWindow& window)
{
	

	window.draw(body);
}

