
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "Animation.h"
#include "PLayer.h"
#include "Platform.h"
#include "background.h"
#include <vector>
static const float VIEW_HEIGHT = 512.0f;
using namespace sf;
using namespace std;
void ResizeView(const RenderWindow& window, View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(1400, 700), "SFML Tutorial", Style::Close | Style::Resize);
    View view(Vector2f(0.0f, 0.0f), Vector2f(1000.f * 1.4, 500.f * 1.4));

    Texture playerTexture;
    playerTexture.loadFromFile("image/tux_from_linux.png");
    Player player(&playerTexture, Vector2u(3, 9), 0.3f, 300.0f, 200.0f);

    RectangleShape box(Vector2f(50.0f, 50.0f));
    box.setPosition(200.0f, 200.00f);
    Texture boxtexture;
    boxtexture.loadFromFile("image/box1.png");
    box.setTexture(&boxtexture);

    vector<Platform> platforms;
    float _del = 10;
    platforms.push_back(Platform(&boxtexture, Vector2f(300.0f, 20.0f), Vector2f(0.0f, 775.0f - _del), Color::White));
    platforms.push_back(Platform(&boxtexture, Vector2f(200.0f, 20.0f), Vector2f(0.0f + 200, 775.0f - 150), Color::Green));
    platforms.push_back(Platform(&boxtexture, Vector2f(200.0f, 20.0f), Vector2f(0.0f - 200, 775.0f - 150 * 2), Color::Blue));
    platforms.push_back(Platform(&boxtexture, Vector2f(200.0f, 20.0f), Vector2f(0.0f + 200, 775.0f - 150 * 3), Color::White));
    platforms.push_back(Platform(&boxtexture, Vector2f(200.0f, 20.0f), Vector2f(0.0f + 500, 775.0f - 150 * 2 + 50), Color::Blue));
    platforms.push_back(Platform(&boxtexture, Vector2f(50.0f, 50.0f), Vector2f(200.0f + 25, 200.0f + 25), Color::Blue));

    RectangleShape enemy(Vector2f(312.0f / 2, 413.0f / 2));
    Texture enemyTexture;
    enemyTexture.loadFromFile("image/hugeyeti3.png");
    enemy.setTexture(&enemyTexture);

    RectangleShape bg(Vector2f(1000.0f * 2, 700.0f * 2));
    Texture bgTexture;
    bgTexture.loadFromFile("image/gbg.png");
    bg.setTexture(&bgTexture);
    bg.setPosition(-700.0f, -340.0f);

    vector<RectangleShape> backg;
    backg.push_back(enemy);

    RectangleShape bg2(Vector2f(1000.0f * 2, 700.0f * 2));
    Texture bg2Texture;
    bg2Texture.loadFromFile("image/gbgf.png");
    bg2.setTexture(&bg2Texture);
    bg2.setPosition(-2700.0f, -340.0f);

    vector<background> _bg;
    _bg.push_back(background(Vector2f(2000.0f, 1400.0f), String("image/gbg.png"), Vector2f(-700.0f, -500.0f)));

    float deltaTime = 1.0f;
    Clock clock;

    float enemyy = 400.0f, enemyx = -300.0f;
    enemy.setPosition(enemyx, enemyy);

    while (window.isOpen())
    {

        Vector2f pos = player.GetPosition();
        float speed_enemy = 0.2f;
        enemyy += (pos.y > (enemyy + 140)) * speed_enemy - (pos.y <= (enemyy + 140)) * speed_enemy;
        enemyx += (pos.x > (enemyx + 200)) * speed_enemy - (pos.x <= (enemyx + 200)) * speed_enemy;
        enemy.setPosition(enemyx, enemyy);

        deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 20.0f)
            deltaTime = 1.0f / 20.0f;
        player.Update(deltaTime);
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::Resized:
                ResizeView(window, view);
                break;
            }
        }

        printf("%.0f %.0f %.0f %.0f\n", pos.x, pos.y, enemyx, enemyy);
        view.setCenter(player.GetPosition());
        window.clear(Color(150, 150, 150));
        window.setView(view);

        cout << " " << player.GetPosition().x << " ";

        int v = 0;
        //if (player.GetPosition().x > 80)
        //   v = 0;
        // else v = 5;

        sf::Vector2f direction;
        for (int i = 0; i < platforms.size() - v; i++)
        {
            if (platforms[i].GetCollision().CheckCollision(player.GetCollision(), direction, 1.0f))
                player.OnCollistion(direction);
            platforms[i].GetCollision().CheckCollision(player.GetCollision(), direction, 1.0f);
        }

        window.draw(bg);
        window.draw(bg2);

        player.Draw(window);

        for (int i = 0; i < platforms.size() - v; i++)
        {
            platforms[i].Draw(window);
        }

        window.draw(box);
        window.draw(enemy);
        window.display();
    }
}
