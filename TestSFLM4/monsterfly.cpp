#include "monsterfly.h"


using namespace sf;
monsterfly::monsterfly(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, Vector2f pos) :
	animation(texture, imageCount, switchTime)
{
	this->speedm1 = speed;
	rowm1 = 0;
	faceRightm1 = true;


	bodym1.setSize(sf::Vector2f(214.0f / 5, 225.0f / 5));
	bodym1.setPosition(pos.x, pos.y);

	bodym1.setTexture(texture);
}

monsterfly::~monsterfly() {}
void monsterfly::Updatem1(float deltatimem1, float posx, float posy) {
	float x = bodym1.getPosition().x;
	float y = bodym1.getPosition().y;
	sf::Vector2f movement(0.0f, 0.0f);
	if (chk == 0) {
		movement.y -= speedm1 * deltatimem1;
		if (y <= posx) {
			chk = 1;
		}
	}
	if (chk == 1) {
		movement.y += speedm1 * deltatimem1;
		if (y >= posy) {
			chk = 0;
		}
	}
	if (chk == 2) {
		bodym1.setPosition(sf::Vector2f(0.0f, 1000.0f));
	}

	rowm1 = 0;
	if (chk == 0) {
		faceRightm1 = true;
	}
	else {
		faceRightm1 = false;
	}

	animation.Update(rowm1, deltatimem1, faceRightm1);
	bodym1.setTextureRect(animation.uvRect);
	bodym1.move(movement);
}

void monsterfly::Draw(sf::RenderWindow& window)
{
	window.draw(bodym1);
}