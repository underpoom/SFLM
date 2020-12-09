#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "Animation.h"
#include "PLayer.h"
#include "Platform.h"
#include "background.h"
#include <vector>
using namespace sf;
using namespace std;
void ResizeView(const RenderWindow& window, View& view)
{
    static const float VIEW_HEIGHT = 512.0f;
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}
int main()
{
    RenderWindow window(sf::VideoMode(1400, 700), "SFML Tutorial", Style::Close | Style::Resize);
    View view(Vector2f(0.0f, 0.0f), Vector2f(1000.f * 1.4, 500.f * 1.4));
    Texture playerTexture;
    playerTexture.loadFromFile("image/tux_from_linux.png");
    Player player(&playerTexture, Vector2u(3, 9), 0.3f, 250.0f, 180.0f);
    Event event;

    Clock clock;
    float deltaTime = 1.0;

    RectangleShape background[10], enemy[10];
    Texture backgroundTexture[10], enemyTexture[10], platformsTexture[10];
    vector<Platform> platforms;

    int numbackground = 2;
    float enemyy = 400.0, enemyx = -300.0;
    // background
    {
        backgroundTexture[0].loadFromFile("image/gbg.png");
        backgroundTexture[1].loadFromFile("image/gbgf.png");
        for (int i = 0; i < numbackground; i++)
        {
            background[i].setSize(Vector2f(900.0f*2 , 500.0f*2 ));
            background[i].setTexture(&backgroundTexture[i % 2]);
            background[i].setPosition(-700.0f + i * 2000.0, 0.0f);
        }
    }
    // platformsTexture file
    {
        platformsTexture[0].loadFromFile("image/1_1.psd"); 
        platformsTexture[1].loadFromFile("image/1_2.psd"); 
        platformsTexture[2].loadFromFile("image/1_3.psd"); 
        platformsTexture[3].loadFromFile("image/1_4.psd"); 
        platformsTexture[4].loadFromFile("image/2_1.psd"); 
        platformsTexture[5].loadFromFile("image/2_2.psd"); 
        platformsTexture[6].loadFromFile("image/2_3.psd"); 
        platformsTexture[7].loadFromFile("image/3_1.psd"); 
        platformsTexture[8].loadFromFile("image/4_1.psd"); 


        platformsTexture[30].loadFromFile("image/obj/pipe22.PNG");
        platformsTexture[31].loadFromFile("image/obj/pipe32.PNG");
        platformsTexture[32].loadFromFile("image/obj/pipe42.PNG");

        platformsTexture[33].loadFromFile("image/obj/qs.PNG");
        platformsTexture[34].loadFromFile("image/obj/hb11.PNG");
        platformsTexture[35].loadFromFile("image/obj/hb81.PNG");
        platformsTexture[36].loadFromFile("image/obj/hb31.PNG");
        platformsTexture[37].loadFromFile("image/obj/hbcoin.PNG");
        platformsTexture[38].loadFromFile("image/obj/hbstar.PNG");
        platformsTexture[39].loadFromFile("image/obj/hb21.PNG");
        platformsTexture[40].loadFromFile("image/obj/hbstair11.PNG");
        platformsTexture[41].loadFromFile("image/obj/hbstair12.PNG");
        platformsTexture[42].loadFromFile("image/obj/hbstair13.PNG");
        platformsTexture[43].loadFromFile("image/obj/hbstair14.PNG");
        platformsTexture[44].loadFromFile("image/obj/hbstair15.PNG");
        platformsTexture[45].loadFromFile("image/obj/hbstair16.PNG");
        platformsTexture[46].loadFromFile("image/obj/hbstair17.PNG");
        platformsTexture[47].loadFromFile("image/obj/hbstair18.PNG");






        platformsTexture[160].loadFromFile("image/obj/floor1.PNG");
        platformsTexture[161].loadFromFile("image/obj/floor2.PNG");
        platformsTexture[162].loadFromFile("image/obj/floor3.PNG");
        platformsTexture[163].loadFromFile("image/obj/floor4.PNG");







    }
    
    // all platforms 
    {
        float bx = 35.0;
        float h = 775.0;                            //lenght-height 
        platforms.push_back(Platform(&platformsTexture[160], Vector2f(bx * 69 , bx * 2), Vector2f(0.0f + ((69/2)*35), h)));
        platforms.push_back(Platform(&platformsTexture[30], Vector2f(bx * 2 ,  bx * 2), Vector2f(bx*29, h-bx*2))); //pipe
        platforms.push_back(Platform(&platformsTexture[31], Vector2f(bx * 2 ,  bx * 3), Vector2f(bx*39, h-bx*2.5)));  //pipe
        platforms.push_back(Platform(&platformsTexture[32], Vector2f(bx * 2 ,  bx * 4), Vector2f(bx * 47, h - bx*3)));  //pipe
        platforms.push_back(Platform(&platformsTexture[32], Vector2f(bx * 2 ,  bx * 4), Vector2f(bx * 58, h - bx * 3))); //pipe


        platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 21  , h - bx*5))); //ladd
        platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 22  , h - bx * 5))); //qs
        platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 23, h - bx * 5))); //ladd
        platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 24, h - bx * 5))); //qs
        platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 25, h - bx * 5))); //ladd
        





        platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 17, h - bx * 5))); //qs1
        platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 23, h - bx * 10))); //qs2

        platforms.push_back(Platform(&platformsTexture[161], Vector2f(bx * 15, bx * 2), Vector2f(bx*80, h)));
        platforms.push_back(Platform(&platformsTexture[162], Vector2f(bx * 67, bx * 2), Vector2f(bx * 93+68/2*bx , h)));

        platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 83, h - bx * 5))); //ladd
        platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 84, h - bx * 5))); //ladd
        platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 85, h - bx * 5))); //ladd




        platforms.push_back(Platform(&platformsTexture[35], Vector2f(bx * 8, bx * 1), Vector2f(bx * 89, h - bx * 10))); //ladd

        platforms.push_back(Platform(&platformsTexture[36], Vector2f(bx * 3, bx * 1), Vector2f(bx * 100, h - bx * 10))); //ladd
        platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 102, h - bx * 10))); //qs1

        platforms.push_back(Platform(&platformsTexture[37], Vector2f(bx * 1, bx * 1), Vector2f(bx * 102, h - bx * 5))); //qs1

        platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 108, h - bx * 5))); //hb
        platforms.push_back(Platform(&platformsTexture[38], Vector2f(bx * 1, bx * 1), Vector2f(bx * 109, h - bx * 5))); //hbstar
       


        platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 114, h - bx * 5))); //qs1
        platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 117, h - bx * 5))); //qs1
        platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 117, h - bx * 10))); //qs1
        platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 120, h - bx * 5))); //qs1
        
        platforms.push_back(Platform(&platformsTexture[36], Vector2f(bx * 3, bx * 1), Vector2f(bx * 129, h - bx * 10))); //hb
        platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 126, h - bx * 5))); //hb

        platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 136, h - bx * 10))); //hb
        platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 137, h - bx * 10))); //qs
        platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 138, h - bx * 10))); //qs
        platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 139, h - bx * 10))); //hb

        platforms.push_back(Platform(&platformsTexture[39], Vector2f(bx * 2, bx * 1), Vector2f(bx * 137, h - bx * 5))); //hb

        platforms.push_back(Platform(&platformsTexture[40], Vector2f(bx * 1, bx * 1), Vector2f(bx * 142, h-bx*1.5))); //hb
        platforms.push_back(Platform(&platformsTexture[41], Vector2f(bx * 1, bx * 2), Vector2f(bx * 143, h-bx*2))); //hb
        platforms.push_back(Platform(&platformsTexture[42], Vector2f(bx * 1, bx * 3), Vector2f(bx * 144, h - bx * 2.5))); //hb
        platforms.push_back(Platform(&platformsTexture[43], Vector2f(bx * 1, bx * 4), Vector2f(bx * 145, h - bx * 3))); //hb

        platforms.push_back(Platform(&platformsTexture[43], Vector2f(bx * 1, bx * 4), Vector2f(bx * 148, h - bx * 3))); //hb
        platforms.push_back(Platform(&platformsTexture[42], Vector2f(bx * 1, bx * 3), Vector2f(bx * 149, h - bx * 2.5))); //hb
        platforms.push_back(Platform(&platformsTexture[41], Vector2f(bx * 1, bx * 2), Vector2f(bx * 150, h - bx * 2))); //hb
        platforms.push_back(Platform(&platformsTexture[40], Vector2f(bx * 1, bx * 1), Vector2f(bx * 151, h - bx * 1.5))); //hb

        platforms.push_back(Platform(&platformsTexture[40], Vector2f(bx * 1, bx * 1), Vector2f(bx * 156, h - bx * 1.5))); //hb
        platforms.push_back(Platform(&platformsTexture[41], Vector2f(bx * 1, bx * 2), Vector2f(bx * 157, h - bx * 2))); //hb
        platforms.push_back(Platform(&platformsTexture[42], Vector2f(bx * 1, bx * 3), Vector2f(bx * 158, h - bx * 2.5))); //hb
        platforms.push_back(Platform(&platformsTexture[43], Vector2f(bx * 1, bx * 4), Vector2f(bx * 159, h - bx * 3))); //hb
        platforms.push_back(Platform(&platformsTexture[43], Vector2f(bx * 1, bx * 4), Vector2f(bx * 160, h - bx * 3))); //hb

        platforms.push_back(Platform(&platformsTexture[163], Vector2f(bx * 67, bx * 2), Vector2f(bx * 164 + 67 / 2 * bx, h)));

        platforms.push_back(Platform(&platformsTexture[43], Vector2f(bx * 1, bx * 4), Vector2f(bx * 164, h - bx * 3))); //hb
        platforms.push_back(Platform(&platformsTexture[42], Vector2f(bx * 1, bx * 3), Vector2f(bx * 165, h - bx * 2.5))); //hb
        platforms.push_back(Platform(&platformsTexture[41], Vector2f(bx * 1, bx * 2), Vector2f(bx * 166, h - bx * 2))); //hb
        platforms.push_back(Platform(&platformsTexture[40], Vector2f(bx * 1, bx * 1), Vector2f(bx * 167, h - bx * 1.5))); //hb

        platforms.push_back(Platform(&platformsTexture[30], Vector2f(bx * 2, bx * 2), Vector2f(bx * 172, h - bx * 2))); //pipe

        platforms.push_back(Platform(&platformsTexture[39], Vector2f(bx * 2, bx * 1), Vector2f(bx * 177+bx*0.5, h - bx * 5))); //hb
        platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 179, h - bx * 5))); //qs
        platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 180, h - bx * 5))); //hb

        platforms.push_back(Platform(&platformsTexture[30], Vector2f(bx * 2, bx * 2), Vector2f(bx * 188, h - bx * 2))); //pipe

        platforms.push_back(Platform(&platformsTexture[40], Vector2f(bx * 1, bx * 1), Vector2f(bx * 190, h - bx * 1.5))); //hb
        platforms.push_back(Platform(&platformsTexture[41], Vector2f(bx * 1, bx * 2), Vector2f(bx * 191, h - bx * 2))); //hb
        platforms.push_back(Platform(&platformsTexture[42], Vector2f(bx * 1, bx * 3), Vector2f(bx * 192, h - bx * 2.5))); //hb
        platforms.push_back(Platform(&platformsTexture[43], Vector2f(bx * 1, bx * 4), Vector2f(bx * 193, h - bx * 3))); //hb
        platforms.push_back(Platform(&platformsTexture[44], Vector2f(bx * 1, bx * 5), Vector2f(bx * 194, h - bx * 3.5))); //hb
        platforms.push_back(Platform(&platformsTexture[45], Vector2f(bx * 1, bx * 6), Vector2f(bx * 195, h - bx * 4))); //hb
        platforms.push_back(Platform(&platformsTexture[46], Vector2f(bx * 1, bx * 7), Vector2f(bx * 196, h - bx * 4.5))); //hb
        platforms.push_back(Platform(&platformsTexture[47], Vector2f(bx * 1, bx * 8), Vector2f(bx * 197, h - bx * 5))); //hb
        platforms.push_back(Platform(&platformsTexture[47], Vector2f(bx * 1, bx * 8), Vector2f(bx * 198, h - bx * 5))); //hb

        platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 207, h - bx * 1.5))); //hb final
       






















       
       
    }
    // enemy
    {
       // enemy[0].setSize(Vector2f(312.0f / 2, 413.0f / 2));
       // enemyTexture[0].loadFromFile("image/hugeyeti3.png");
       // enemy[0].setTexture(&enemyTexture[0]);
    }
    // menu
    

    Texture btnplayTexture,backTexture;
    RectangleShape btnplay(Vector2f(1300.0f/3, 300.0f/3));
    RectangleShape sbtnplay(Vector2f(1300.0f / 3*1.2, 300.0f / 3*1.2));

    RectangleShape back(Vector2f(1400.0f , 700.0f ));

    btnplayTexture.loadFromFile("image/menu/btnstart.PNG");

    backTexture.loadFromFile("image/menu/back.jpg");

    btnplay.setTexture(&btnplayTexture);
    sbtnplay.setTexture(&btnplayTexture);
    back.setTexture(&backTexture);

    

    int state = 0;
    while (window.isOpen())
    {
        

        if (state == 0)
        {
            printf("player = %.0f %.0f %.0f %.0f %.0f ", player.GetPosition().x, player.GetPosition().y, enemyx, enemyy);
            btnplay.setPosition(player.GetPosition().x, player.GetPosition().y-300);
            sbtnplay.setPosition(player.GetPosition().x-10, player.GetPosition().y - 310);

            Vector2i mouse = Mouse::getPosition(window);
            printf("mousepos x= %.0f y= %.0f\n", (float)mouse.x, (float)mouse.y);




            back.setPosition(player.GetPosition().x - 700, player.GetPosition().y - 350);
           
            window.clear(Color(150, 150, 150));
            view.setCenter(player.GetPosition());
            window.setView(view);

            window.draw(back);
            if (mouse.x > 738 and mouse.x < 1080 and mouse.y>64 and mouse.y < 130)
                window.draw(sbtnplay);
            else 
            window.draw(btnplay);
         
            window.display();
            
           
           
            

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

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            {
                if(mouse.x>738 and mouse.x<1080 and mouse.y>64 and mouse.y<130)
                
                state = 1;
            }




        }

        else if (state == 1)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {

                state = 0;
            }

            // enemy setting
            {
                Vector2f pos = player.GetPosition();
                float speed_enemy = 0.1f;
                enemyy += (pos.y > (enemyy + 140)) * speed_enemy - (pos.y <= (enemyy + 140)) * speed_enemy;
                enemyx += (pos.x > (enemyx + 200)) * speed_enemy - (pos.x <= (enemyx + 200)) * speed_enemy;
                enemy[0].setPosition(enemyx, enemyy);
                printf("player = %.0f %.0f %.0f %.0f %.0f\n", player.GetPosition().x, pos.y, enemyx, enemyy);
            }
            // deltaTime
            {
                deltaTime = clock.restart().asSeconds();
                if (deltaTime > 1.0f / 20.0f)
                    deltaTime = 1.0f / 20.0f;
                player.Update(deltaTime);
            }
            // closed
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
            //Center&View
            {
                view.setCenter(player.GetPosition());
                window.clear(Color(150, 150, 150));
                window.setView(view);
            }
            for (int i = 0; i < numbackground; i++)
            {
                window.draw(background[i]);
            }
            for (int i = 0; i < platforms.size(); i++)
            {
                Vector2f direction;
                if (platforms[i].GetCollision().CheckCollision(player.GetCollision(), direction, 1.0))
                    player.OnCollistion(direction);
                platforms[i].GetCollision().CheckCollision(player.GetCollision(), direction, 1.0);
                platforms[i].Draw(window);
            }
            //window.draw(enemy[0]);
            player.Draw(window);
            window.display();
        }
    }
    

}
