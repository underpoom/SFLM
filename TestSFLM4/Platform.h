#pragma once
#include <SFML\Graphics.hpp>
#include "Collision.h"
using namespace sf;
class Platform
{
public:
	Platform(Texture* texture, Vector2f size, Vector2f position);
	~Platform();
	void Draw(RenderWindow& window);
	Collision GetCollision() { return Collision(body); }
private :
	RectangleShape body;
};
/*
        platformsTexture[30].loadFromFile("image/obj/pipe22.PNG");
        platformsTexture[31].loadFromFile("image/obj/pipe32.PNG");
        platformsTexture[32].loadFromFile("image/obj/pipe42.PNG");

        platformsTexture[33].loadFromFile("image/obj/qs.PNG");
        platformsTexture[34].loadFromFile("image/obj/hb11.PNG");
        platformsTexture[35].loadFromFile("image/obj/hb81.PNG");
        platformsTexture[36].loadFromFile("image/obj/hb31.PNG");
        platformsTexture[37].loadFromFile("image/obj/hbcoin.PNG");
        platformsTexture[40].loadFromFile("image/obj/hbstair11.PNG");
        platformsTexture[41].loadFromFile("image/obj/hbstair12.PNG");
        platformsTexture[42].loadFromFile("image/obj/hbstair13.PNG");
        platformsTexture[43].loadFromFile("image/obj/hbstair14.PNG");

        platformsTexture[160].loadFromFile("image/obj/floor1.PNG");
        platformsTexture[161].loadFromFile("image/obj/floor2.PNG");
        platformsTexture[162].loadFromFile("image/obj/floor3.PNG");



*/

