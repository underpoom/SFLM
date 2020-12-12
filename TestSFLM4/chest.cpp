#include "chest.h"
using namespace sf;
chest::chest(Texture* texture, Vector2f size, Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);

}
chest::~chest()
{
}
void chest::Draw(RenderWindow& window)
{
	window.draw(body);
}

