
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "Animation.h"
#include "PLayer.h"
#include "Platform.h"
static const float VIEW_HEIGHT = 512.0f;
using namespace sf;

void ResizeView(const RenderWindow& window, View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
        
}
int main()
{
 
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Tutorial" , Style::Close | Style::Resize);
    View view(Vector2f(0.0f, 0.0f), Vector2f(512.f, 512.f));
    Texture playerTexture;
    playerTexture.loadFromFile("image/tux_from_linux.png");
    Player player(&playerTexture, Vector2u(3, 9), 0.3f,100.0f);

    Platform platform1(nullptr, Vector2f(400.0f, 200.0f), Vector2f(500.0f, 200.0f));
    Platform platform2(nullptr, Vector2f(400.0f, 200.0f), Vector2f(500.0f, 0.0f));

    float deltaTime = 0.0f;
    Clock clock;
        
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

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

        player.Update(deltaTime);

        platform1.GetCollision().CheckCollision(player.GetCollision(), 0.0f);
        platform2.GetCollision().CheckCollision(player.GetCollision(), 1.0f);
        view.setCenter(player.GetPosition());
            
        window.clear(Color(150,150,150));
        window.setView(view);
        player.Draw(window);
        platform1.Draw(window);
        platform2.Draw(window);
        window.display();
              
    }
          
}