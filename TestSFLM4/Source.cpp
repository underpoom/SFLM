#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <windows.h>
#include "Animation.h"
#include "Textbox.h"
#include "PLayer.h"
#include "Platform.h"
#include "background.h"
#include "monster1.h";
#include "monstertop.h";
#include "monsterfly.h";
#include "chest.h";
#include <vector>
#include<stdio.h>
#include<utility>
#include<algorithm>
#include<string>
using namespace sf;
using namespace std;
void ResizeView(const RenderWindow& window, View& view)
{
    static const float VIEW_HEIGHT = 512.0f;
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}
void showHighScore(int x, int y, string word, sf::RenderWindow& window, sf::Font* font)
{
   
    
        sf::Text text;
        text.setFont(*font);
        text.setPosition(x, y);
        text.setString(word);
        if (word == "HIGHSCORE")
            text.setCharacterSize(80);
        else
        text.setCharacterSize(50);
        window.draw(text);
    
}
int mins=0, secs=0;
void showTime(int x, int y, float mills, sf::RenderWindow& window, sf::Font* font)
{
        mills = int(mills);
        secs = (int(mills) / 100) % 60;
        mins = (int(mills) /100)/60%60;
    mills = int(mills) % 100;
    int mills2 = int(mills);
    String _secs, _mins;
    if (secs < 10)_secs = "0";
        else _secs = "";
    if (mins < 10)_mins = "0";
    else _mins = ""; 
    String word = _mins + to_string(mins) + ":" + _secs + to_string(secs) + ":" + to_string(mills2);
   
    sf::Text text;
    text.setFont(*font);
    text.setPosition(x, y);
    text.setString(word);
    text.setCharacterSize(75);
    
    
    window.draw(text);
}
void showcount(int x, int y, int count, sf::RenderWindow& window, sf::Font* font)
{
   
    sf::Text text;
    text.setFont(*font);
    text.setPosition(x, y);
    text.setString(to_string(count));
    text.setCharacterSize(60);
    text.setFillColor(Color::Black);
    window.draw(text);
}

int main()
{

    

    Font font;
    char temp[255] = {};
    int score[6] = {};
    string name[6] = {};
    vector <pair<int, string>> userScore;
    FILE* fp;
    // high score
    {
    font.loadFromFile("Blockbusted.ttf");
    fp = fopen("./Score.txt", "r");
    for (int i = 0; i < 5; i++)
    {
        fscanf(fp, "%s", &temp);
        name[i] = temp;
        fscanf(fp, "%d", &score[i]);
        userScore.push_back(make_pair(score[i], name[i]));
        //cout << temp << " " << score;
    }
    ///////////////////----------------------------
    name[5] = "kkkokkkkk";
    score[5] = 12356;
    ///////////////////----------------------------
    userScore.push_back(make_pair(score[5], name[5]));
    sort(userScore.begin(), userScore.end());
    fclose(fp);
    }

    int state = 0;
    // start game
    start:;

    RenderWindow window(sf::VideoMode(1400, 700), "Escapue!", Style::Close | Style::Resize);
    View view(Vector2f(0.0f, 0.0f), Vector2f(1000.f * 1.4, 500.f * 1.4));
    Texture playerTexture;
    playerTexture.loadFromFile("image/tux_from_linux.png");
    Player player(&playerTexture, Vector2u(3, 9), 0.3f, 200.0f, 180.0f);

    //sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,Vector2f pos
    Texture monsterTexture, monsterTexture2 , monsterTexture3, monsterTexture4 , monsterTexture5, monsterTexture6;
    Texture monsterTexture7, monsterTexture8;
    monsterTexture.loadFromFile("image/monster/ms01.PNG");
    monsterTexture2.loadFromFile("image/monster/ghost.PNG");
    monsterTexture3.loadFromFile("image/monster/ms03.PNG");
    monsterTexture4.loadFromFile("image/monster/ms04.PNG");
    monsterTexture5.loadFromFile("image/monster/ms05.PNG");
    monsterTexture6.loadFromFile("image/monster/ms06.PNG");
    monsterTexture7.loadFromFile("image/monster/ms07.PNG");
    monsterTexture8.loadFromFile("image/monster/ms08.PNG");

    monster1 monster(&monsterTexture, Vector2u(1, 1), 0.3f, 250.0f , Vector2f(500.0f , 699.0f -20));
    monsterfly monster2(&monsterTexture2, Vector2u(1, 1), 0.3f, 250.0f, Vector2f(1740.0f, 699.0f - 20));
    monster1 monster3(&monsterTexture3, Vector2u(1, 1), 0.3f, 250.0f, Vector2f(1078, 699.0f - 20));
    monstertop monster4(&monsterTexture4, Vector2u(1, 1), 0.3f, 250.0f, Vector2f(3000, 360.0f -10 ));
    monster1 monster5(&monsterTexture5, Vector2u(1, 1), 0.3f, 150.0f, Vector2f(2760.0f, 699.0f - 20));
    monster1 monster6(&monsterTexture6, Vector2u(1, 1), 0.3f, 700.0f, Vector2f(3500.0f, 699.0f - 20));
    monster1 monster7(&monsterTexture7, Vector2u(1, 1), 0.3f, 400.0f, Vector2f(4600.0f, 699.0f - 20));
    monster1 monster8(&monsterTexture8, Vector2u(1, 1), 0.3f, 300.0f, Vector2f(6200.0f, 699.0f - 20));
    monsterfly monster9(&monsterTexture2, Vector2u(1, 1), 0.3f, 450.0f, Vector2f(1880.0f, 699.0f - 20));

    
    Event event;
    Clock clock;
    float deltaTime = 1.0;
    RectangleShape background[10], enemy[10];
    Texture backgroundTexture[10], enemyTexture[10], platformsTexture[200];
    vector<Platform> platforms;
    RectangleShape obj[10];
    Texture objTexture[10];

    int numbackground = 10;
    
    sf::SoundBuffer buffer;
   
    if (!buffer.loadFromFile("soundeffect/ES_Game Show - Liru.ogg"))
    {
        cout << "Error";
    }
    Sound sound;
    sound.setBuffer(buffer);
    



    // background 
    {
        backgroundTexture[0].loadFromFile("image/background/ice2.jpg");
        backgroundTexture[1].loadFromFile("image/background/ice2.jpg");
        for (int i = 0; i < numbackground; i++)
        {
            background[i].setSize(Vector2f(2880.0f /1.3 , 2065.0f/1.3 ));
            background[i].setTexture(&backgroundTexture[i % 2]);
            background[i].setPosition(-1200.0f + i * 2210.0, -500.0f +200);
        }
    }
    //other obj
    {
        // flag
        objTexture[0].loadFromFile("image/obj/flag.PNG");
        obj[0].setSize(Vector2f(35.0*1.5  , 350.0 ));
        obj[0].setTexture(&objTexture[0]);
        obj[0].setPosition(7250 - 35 * 1.35, 775 - 35 * 12);
        // castle
        objTexture[1].loadFromFile("image/obj/castle.PNG");
        obj[1].setSize(Vector2f(35.0 * 5, 35.0 * 5));
        obj[1].setTexture(&objTexture[1]);
        obj[1].setPosition(35*219.2, 775 - 35 * 6);



    }
    // platformsTexture file
    {
        
      


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
        float h = 775.0;     
        // platform main room
        {
            //lenght-height 
            platforms.push_back(Platform(&platformsTexture[160], Vector2f(bx * 69, bx * 2), Vector2f(0.0f + ((69 / 2) * 35), h)));
            platforms.push_back(Platform(&platformsTexture[30], Vector2f(bx * 2, bx * 2), Vector2f(bx * 29, h - bx * 2))); //pipe
            platforms.push_back(Platform(&platformsTexture[31], Vector2f(bx * 2, bx * 3), Vector2f(bx * 39, h - bx * 2.5)));  //pipe
            platforms.push_back(Platform(&platformsTexture[32], Vector2f(bx * 2, bx * 4), Vector2f(bx * 47, h - bx * 3)));  //pipe
            platforms.push_back(Platform(&platformsTexture[32], Vector2f(bx * 2, bx * 4), Vector2f(bx * 58, h - bx * 3))); //pipe
            platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 21, h - bx * 5))); //ladd
            platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 23, h - bx * 5))); //ladd
            platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 25, h - bx * 5))); //ladd
            platforms.push_back(Platform(&platformsTexture[161], Vector2f(bx * 15, bx * 2), Vector2f(bx * 80, h)));
            platforms.push_back(Platform(&platformsTexture[162], Vector2f(bx * 67, bx * 2), Vector2f(bx * 93 + 68 / 2 * bx, h)));
            platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 83, h - bx * 5))); //ladd
            platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 85, h - bx * 5))); //ladd
            platforms.push_back(Platform(&platformsTexture[35], Vector2f(bx * 8, bx * 1), Vector2f(bx * 89, h - bx * 10))); //ladd
            platforms.push_back(Platform(&platformsTexture[36], Vector2f(bx * 3, bx * 1), Vector2f(bx * 100, h - bx * 10))); //ladd
            platforms.push_back(Platform(&platformsTexture[37], Vector2f(bx * 1, bx * 1), Vector2f(bx * 102, h - bx * 5))); //qs1
            platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 108, h - bx * 5))); //hb
            platforms.push_back(Platform(&platformsTexture[38], Vector2f(bx * 1, bx * 1), Vector2f(bx * 109, h - bx * 5))); //hbstar
            platforms.push_back(Platform(&platformsTexture[36], Vector2f(bx * 3, bx * 1), Vector2f(bx * 129, h - bx * 10))); //hb
            platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 126, h - bx * 5))); //hb
            platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 136, h - bx * 10))); //hb
            platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 139, h - bx * 10))); //hb
            platforms.push_back(Platform(&platformsTexture[39], Vector2f(bx * 2, bx * 1), Vector2f(bx * 137, h - bx * 5))); //hb
            platforms.push_back(Platform(&platformsTexture[40], Vector2f(bx * 1, bx * 1), Vector2f(bx * 142, h - bx * 1.5))); //hb
            platforms.push_back(Platform(&platformsTexture[41], Vector2f(bx * 1, bx * 2), Vector2f(bx * 143, h - bx * 2))); //hb
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
            
            platforms.push_back(Platform(&platformsTexture[39], Vector2f(bx * 2, bx * 1), Vector2f(bx * 177 + bx * 0.5, h - bx * 5))); //hb
            platforms.push_back(Platform(&platformsTexture[34], Vector2f(bx * 1, bx * 1), Vector2f(bx * 180, h - bx * 5))); //hb
            
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

            platforms.push_back(Platform(&platformsTexture[30], Vector2f(bx * 2, bx * 2), Vector2f(bx * 172, h - bx * 2))); //pipe
            platforms.push_back(Platform(&platformsTexture[30], Vector2f(bx * 2, bx * 2), Vector2f(bx * 186, h - bx * 2))); //pipe

            platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 17, h - bx * 5))); //qs1    -1
            platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 22, h - bx * 5))); //qs     -2
            platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 23, h - bx * 10))); //qs2   -3
            platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 24, h - bx * 5))); //qs     -4
            platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 84, h - bx * 5))); //ladd   -5
            platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 102, h - bx * 10))); //qs1  -6
            platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 114, h - bx * 5))); //qs1    -7
            platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 117, h - bx * 5))); //qs1    -8
            platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 117, h - bx * 10))); //qs1   -9
            platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 120, h - bx * 5))); //qs1    -10
            platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 137, h - bx * 10))); //qs    -11
            platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 138, h - bx * 10))); //qs    -12
            platforms.push_back(Platform(&platformsTexture[33], Vector2f(bx * 1, bx * 1), Vector2f(bx * 179, h - bx * 5))); //qs     -13



        }
        
 
    }

    
    
    // menu icon
    Texture btnplayTexture,backTexture;
    Texture hsTexture,settingTexture,exitTexture,commingTexture,returnTexture,gameoverTexture,playagainTexture;
    RectangleShape back(Vector2f(1400.0f , 700.0f ));
    RectangleShape btnplay(Vector2f(1300.0f/3, 300.0f/3)) , sbtnplay(Vector2f(1300.0f / 3*1.2, 300.0f / 3*1.2));
    RectangleShape btnhs(Vector2f(369.0f , 97.0f )), sbtnhs(Vector2f(369.0f  * 1.2, 97.0f  * 1.2));
    RectangleShape btnsetting(Vector2f(540.0f /1.8, 322.0f/1.8 )), sbtnsetting(Vector2f(540.0f/1.8  * 1.2, 322.0f /1.8* 1.2));
    RectangleShape btnexit(Vector2f(540.0f / 2.5, 240.0f / 2.5)), sbtnexit(Vector2f(540.0f / 2.5 * 1.2, 240.0f / 2.5 * 1.2));
    RectangleShape comming(Vector2f(1200.0f /1.5 , 450.0f /1.5));
    RectangleShape btnreturn(Vector2f(280.0/3.5 , 280.0/3.5 )),sbtnreturn(Vector2f(280.0 / 3.5 *1.2, 280.0 / 3.5 * 1.2));
    RectangleShape btngameover(Vector2f(804.0 /1, 422.0 / 1));
    RectangleShape btnplayagain(Vector2f(738.0 / 2.5, 419.0 / 2.5)), sbtnplayagain(Vector2f(738.0 / 2.5 * 1.2, 419.0 / 2.5 * 1.2));
    // menu buttonTexture
    {
        backTexture.loadFromFile("image/menu/back.jpg");
        back.setTexture(&backTexture);

        btnplayTexture.loadFromFile("image/menu/btnstart.PNG");
        btnplay.setTexture(&btnplayTexture);
        sbtnplay.setTexture(&btnplayTexture);

        hsTexture.loadFromFile("image/menu/highscore.PNG");
        btnhs.setTexture(&hsTexture);
        sbtnhs.setTexture(&hsTexture);

        settingTexture.loadFromFile("image/menu/setting.PNG");
        btnsetting.setTexture(&settingTexture);
        sbtnsetting.setTexture(&settingTexture);

        exitTexture.loadFromFile("image/menu/exit.PNG");
        btnexit.setTexture(&exitTexture);
        sbtnexit.setTexture(&exitTexture);

        commingTexture.loadFromFile("image/menu/commingsoon.PNG");
        comming.setTexture(&commingTexture);

        returnTexture.loadFromFile("image/menu/return.PNG");
        btnreturn.setTexture(&returnTexture);
        sbtnreturn.setTexture(&returnTexture);

        gameoverTexture.loadFromFile("image/menu/btngameover.PNG");
        btngameover.setTexture(&gameoverTexture);

        playagainTexture.loadFromFile("image/menu/btnplayagain.PNG");
        btnplayagain.setTexture(&playagainTexture);
        sbtnplayagain.setTexture(&playagainTexture);

       
        




       
    }
    player.fallen = 0;
    bool on = 0;

    int vjump = 0;
    int vjumpstate = 0;
    int mins = 0, secons = 0, mills = 0;
    Clock Cclock;

    int ichest[20] = {};
    int ichestcol[20] = {};
    srand(time(NULL));
    Texture ChestTexture[10];
    {
        ChestTexture[0].loadFromFile("image/chest&key/chest0.PNG");
        ChestTexture[1].loadFromFile("image/chest&key/chest1.PNG");
        ChestTexture[2].loadFromFile("image/chest&key/chest2.PNG");
        ChestTexture[3].loadFromFile("image/chest&key/chest3.PNG");
        ChestTexture[4].loadFromFile("image/chest&key/key0.PNG");
        ChestTexture[5].loadFromFile("image/chest&key/key1.PNG");
        ChestTexture[6].loadFromFile("image/chest&key/key2.PNG");
        ChestTexture[7].loadFromFile("image/chest&key/key3.PNG");

        ChestTexture[8].loadFromFile("image/chest&key/x.PNG");

    }
    RectangleShape icon;
    icon.setSize(Vector2f(380.0/3, 436.0/3));
    icon.setTexture(&ChestTexture[8]);
    
        
    Textbox playernametextbox(70, sf::Color::White, true);
    playernametextbox.setFont(font);
    playernametextbox.setPosition({ player.GetPosition().x - 500,player.GetPosition().y +100});
    playernametextbox.setlimit(true, 10);


    vector<chest> Chest;
int _rand[20] = {};
    // chest put
    {
        float bx = 35.0f;
        float h = 775.0f;

        
        for (int i = 0; i < 14; i++)
        {
            _rand[i] = rand() % 8;
        }

        Chest.push_back(chest(&ChestTexture[_rand[0]], Vector2f(bx , bx ), Vector2f(bx * 17 , h - bx * 5 - bx + rand()%2*70 )));
        Chest.push_back(chest(&ChestTexture[_rand[1]], Vector2f(bx, bx  ), Vector2f(bx * 22 , h - bx * 5 - bx + rand() % 2 * 70)));
        Chest.push_back(chest(&ChestTexture[_rand[2]], Vector2f(bx, bx  ), Vector2f(bx * 23 , h - bx * 10 - bx + rand() % 2 * 70)));
        Chest.push_back(chest(&ChestTexture[_rand[3]], Vector2f(bx, bx), Vector2f(bx * 24, h - bx * 5 - bx + rand() % 2 * 70)));
        Chest.push_back(chest(&ChestTexture[_rand[4]], Vector2f(bx, bx), Vector2f(bx * 84, h - bx * 5 - bx + rand() % 2 * 70)));
        Chest.push_back(chest(&ChestTexture[_rand[5]], Vector2f(bx, bx), Vector2f(bx * 102, h - bx * 10 - bx + rand() % 2 * 70)));
        Chest.push_back(chest(&ChestTexture[_rand[6]], Vector2f(bx, bx), Vector2f(bx * 114, h - bx * 5 - bx + rand() % 2 * 70)));
        Chest.push_back(chest(&ChestTexture[_rand[7]], Vector2f(bx, bx), Vector2f(bx * 117, h - bx * 5 - bx + rand() % 2 * 70)));
        Chest.push_back(chest(&ChestTexture[_rand[8]], Vector2f(bx, bx), Vector2f(bx * 117, h - bx * 10 - bx + rand() % 2 * 70)));
        Chest.push_back(chest(&ChestTexture[_rand[9]], Vector2f(bx, bx), Vector2f(bx * 120, h - bx * 5 - bx + rand() % 2 * 70)));
        Chest.push_back(chest(&ChestTexture[_rand[10]], Vector2f(bx, bx), Vector2f(bx * 137, h - bx * 10 - bx + rand() % 2 * 70)));
        Chest.push_back(chest(&ChestTexture[_rand[11]], Vector2f(bx, bx), Vector2f(bx * 138, h - bx * 10 - bx + rand() % 2 * 70)));
        Chest.push_back(chest(&ChestTexture[_rand[12]], Vector2f(bx, bx), Vector2f(bx * 179, h - bx * 10 - bx + rand() % 2 * 70)));



    }

    Vector2f warp[10];
    {
        warp[0] = Vector2f(1016.0f, 450.0);
        warp[1] = Vector2f(1360.0f, 417.0);
        warp[2] = Vector2f(1650.0f, 382.0);
        warp[3] = Vector2f(2032.0f, 386.0);
    }

    int countchest = 0 , countkey = 0;
    int soundstate1 = 0;
    int finalstate = 0;

    while (window.isOpen())
    {  
        // highscore
        if(state == -1)
        {

            btnreturn.setPosition(player.GetPosition().x + 320 - 720, player.GetPosition().y - 230);
            sbtnreturn.setPosition(player.GetPosition().x + 315 - 720, player.GetPosition().y - 240);

            Vector2i mouse = Mouse::getPosition(window);
            printf("mousepos x= %.0f y= %.0f\n", (float)mouse.x, (float)mouse.y);

            back.setPosition(player.GetPosition().x - 700, player.GetPosition().y - 350);


            fopen("./Score.txt", "w");
            for (int i = 5; i >= 0; i--)
            {
                strcpy(temp, userScore[i].second.c_str());
                fprintf(fp, "%s %d\n", temp, userScore[i].first);
            }
            fclose(fp);
            
            

            window.clear();
            window.draw(back);


            showHighScore(-200 + 20, 150 -20, "HIGHSCORE", window, &font);

            for (int i = 4; i >= 0; i--)
            {

                showHighScore(-220,190 + (5 - i) * 60, userScore[i].second, window, &font);
                showHighScore(+60+40,190 + (5 - i) * 60, to_string(userScore[i].first), window, &font);
            }

            if (mouse.x > 990 - 720 and mouse.x < 1100 - 720 and mouse.y>92 and mouse.y < 200)
                window.draw(sbtnreturn);
            else
                window.draw(btnreturn);


            window.display();

            if (mouse.x > 990 - 720 and mouse.x < 1100 - 720 and mouse.y>92 and mouse.y < 200)
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    state = 0;

             
        

        }
        // menu
        if (state == 0)
        {
            
           
            // all button-------------------------------------------------------------------
            btnplay.setPosition(player.GetPosition().x, player.GetPosition().y-300);
            sbtnplay.setPosition(player.GetPosition().x-20, player.GetPosition().y - 310);

            btnhs.setPosition(player.GetPosition().x +25, player.GetPosition().y - 165);
            sbtnhs.setPosition(player.GetPosition().x , player.GetPosition().y - 175);


            btnsetting.setPosition(player.GetPosition().x + 55, player.GetPosition().y -30);
            sbtnsetting.setPosition(player.GetPosition().x +30, player.GetPosition().y -50);

            btnexit.setPosition(player.GetPosition().x + 105, player.GetPosition().y +170);
            sbtnexit.setPosition(player.GetPosition().x + 95, player.GetPosition().y +160);

            comming.setPosition(player.GetPosition().x  -400, player.GetPosition().y -150);

            


            //-------------------------------------------------------------------------------
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
            
            if (mouse.x > 720 and mouse.x < 1080 and mouse.y>187 and mouse.y < 281)
                window.draw(sbtnhs);
            else
                window.draw(btnhs);

            if (mouse.x > 770 and mouse.x < 1040 and mouse.y>330 and mouse.y < 470)
                window.draw(sbtnsetting);
            else             
                window.draw(btnsetting);


            if (mouse.x > 808 and mouse.x < 1017 and mouse.y>520 and mouse.y < 610)
                window.draw(sbtnexit);
            else              
                window.draw(btnexit);

            if (mouse.x > 813 and mouse.x < 1010 and mouse.y>525 and mouse.y < 606)
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    window.close();

            
            if (mouse.x > 770 and mouse.x < 1040 and mouse.y>330 and mouse.y < 470)
                if (Mouse::isButtonPressed(sf::Mouse::Left) )            
                  state = 2;

            if (mouse.x > 726 and mouse.x < 1079 and mouse.y>190 and mouse.y < 270)
                if (Mouse::isButtonPressed(sf::Mouse::Left))
                    state = -1;

            
            
            playernametextbox.drawTo(window);
            

          
           
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
                case sf::Event::TextEntered:
                    playernametextbox.typeOn(event);
                
                
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) )
            {
                if (mouse.x > 738 and mouse.x < 1080 and mouse.y>64 and mouse.y < 130)
                {
                    state = 1;
                    Cclock.restart();
                    
                }
                
                    
            }

           


        }
         
        // game play
        else if (state == 1)
        {  
        

        

        
            // sound play
            {
                if (soundstate1 == 0)
                    sound.play();

                if (soundstate1 == 0)
                    soundstate1 = 1;
                
            }
            
            printf("player x=%.0f y=%.0f cchest=%d ckey=%d ", player.GetPosition().x, player.GetPosition().y,countchest,countkey);
            // Exit
            if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
            {     
                state = 0;
                goto start;
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
            // Center&View
            {
                view.setCenter(player.GetPosition());
                window.clear(Color(150, 150, 150));
                window.setView(view);
            }
            // background
            for (int i = 0; i < numbackground; i++)
            {
                window.draw(background[i]);
            }
            // obj
            {
                for (int i = 0; i < 10; i++)
                {
                    window.draw(obj[i]);
                        
                }
            }
            
            
                player.Draw(window);
            
            // Warp
            {
                if (Keyboard::isKeyPressed(Keyboard::Key::V) and vjumpstate == 0)
                {
                    vjump++;
                    player.SetPosition(1000.0f + vjump * 300, 500.0f);
                    vjumpstate = 1;
                }
                if (!Keyboard::isKeyPressed(Keyboard::Key::V))
                {
                    vjumpstate = 0;
                }
            }
            Vector2f direction;     
            // update monster
            {
                monster.Updatem1(deltaTime * 0.8, 360.0, 930.0);
                monster.Draw(window);

                monster2.Updatem1(deltaTime * 0.8, 380, 700);
                monster2.Draw(window);

                monster3.Updatem1(deltaTime * 0.8, 1078 - 20, 1303 - 20);
                monster3.Draw(window);

                monster4.Updatem1(deltaTime * 0.8, 3000 - 20, 3230 - 20);
                monster4.Draw(window);

                monster5.Updatem1(deltaTime * 0.8, 2560 - 20, 3030 - 20);
                monster5.Draw(window);

                monster6.Updatem1(deltaTime * 0.8, 3300 - 20, 4400 - 20);
                monster6.Draw(window);

                monster7.Updatem1(deltaTime * 0.8, 4460 - 50, 4925 - 40);
                monster7.Draw(window);

                monster8.Updatem1(deltaTime * 0.8, 6083 - 30, 6518 - 95);
                monster8.Draw(window);

                monster9.Updatem1(deltaTime * 0.8, 180, 700);
                monster9.Draw(window);
            }    
            
            // platforms & chest/key        
            for (int i = 0; i < platforms.size(); i++)
            {

                
                    if (platforms[i].GetCollision().CheckCollision(player.GetCollision(), direction, 1.0))
                        player.OnCollistion(direction);
                    platforms[i].GetCollision().CheckCollision(player.GetCollision(), direction, 1.0);


                    
                    
                        for(int j=54;j<54+13;j++)
                        if (ichest[j-54]==0 and (platforms[j].GetCollision().CheckCollision(player.GetCollision(), direction, 1.0f)))
                        {
                            ichest[j-54] = 1;
                        }

                        if (platforms[53].GetCollision().CheckCollision(player.GetCollision(), direction, 1.0f))
                        {
                            int r = rand() % 4;
                            player.SetPosition(warp[r].x,warp[r].y);
                        }
                        if (platforms[52].GetCollision().CheckCollision(player.GetCollision(), direction, 1.0f))
                        {
                            int r = rand() % 4;
                            player.SetPosition(warp[r].x, warp[r].y);
                        }

                        
                        for (int k = 0; k < Chest.size(); k++)
                        {

                            if (ichest[k] != 0)
                            {
                                

                                Chest[k].Draw(window);
                            }
                            if (ichest[k] == 1 and ichestcol[k] == 0 and (Chest[k].GetCollision().CheckCollision(player.GetCollision(), direction, 1.0f)))
                                {
                                    ichestcol[k] = 1;
                                }



                        }
                        countchest = 0, countkey = 0;

                        for (int l = 0; l < Chest.size(); l++)
                        {
                            if (ichestcol[l] == 1 and _rand[l] < 4)
                                countchest++;
                            if (ichestcol[l] == 1 and _rand[l] > 3)
                                countkey++;

                        }


                   

                    

                    platforms[i].Draw(window);
                
            }


            for (int i = 0; i < 15; i++)
            {
               
                cout << ichest[i];
            }
            cout << " : ";
            for (int i = 0; i < 15; i++)
            {

                cout << ichestcol[i];
            }

            cout << endl;
            
           
            // fall down
            {
                btngameover.setPosition(player.GetPosition().x + 320 - 720, player.GetPosition().y - 230-100+10);
                btnplayagain.setPosition(player.GetPosition().x +180  -85, player.GetPosition().y +150 -20);
                sbtnplayagain.setPosition(player.GetPosition().x + 180 - 85-25, player.GetPosition().y + 150 - 20-15);

                Vector2i mouse = Mouse::getPosition(window);
                printf(" mousepos x= %.0f y= %.0f ", (float)mouse.x, (float)mouse.y);

                // fall down
                if (player.GetPosition().y>890)
                {
                    
                    {
                        if (mouse.x > 803 and mouse.x < 1081 and mouse.y>490 and mouse.y < 635)
                            window.draw(sbtnplayagain);
                        else
                            window.draw(btnplayagain);

                        if (mouse.x > 803 and mouse.x < 1081 and mouse.y>490 and mouse.y < 635)
                            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                            {
                                goto start;
                                state = 1;
                            }

                            player.fallen = 1;
                        window.draw(btngameover);
                       
                    }

                }
            }
            // show time
            {
                Time elapsed = Cclock.getElapsedTime();    
                
                mills = int(elapsed.asSeconds() * 100);
                showTime(player.GetPosition().x + 360, player.GetPosition().y - 300, mills, window, &font);
            }
            // show icon
            {
                icon.setPosition(player.GetPosition().x -650, player.GetPosition().y - 300);
                window.draw(icon);

                showcount(player.GetPosition().x -500 -10-3, player.GetPosition().y - 300-8 +5, countchest, window, &font);
                showcount(player.GetPosition().x - 500 - 10-3, player.GetPosition().y - 300 - 8 +80 +5, countkey, window, &font);
            }

            // monster collision
            {
                if (monster.GetCollider().CheckCollisionm1(player.GetCollision(), direction))
                    on = 1;
                if (monster2.GetCollider().CheckCollisionm2(player.GetCollision(), direction))
                    on = 1;
                if (monster3.GetCollider().CheckCollisionm1(player.GetCollision(), direction))
                    on = 1;
                if (monster4.GetCollider().CheckCollisionm1(player.GetCollision(), direction))
                    on = 1;
                if (monster5.GetCollider().CheckCollisionm1(player.GetCollision(), direction))
                    on = 1;
                if (monster6.GetCollider().CheckCollisionm1(player.GetCollision(), direction))
                    on = 1;
                if (monster7.GetCollider().CheckCollisionm1(player.GetCollision(), direction))
                    on = 1;
                if (monster8.GetCollider().CheckCollisionm1(player.GetCollision(), direction))
                    on = 1;
                if (monster9.GetCollider().CheckCollisionm1(player.GetCollision(), direction))
                    on = 1;
            }

                if(on == 1)
                {
                    btngameover.setPosition(player.GetPosition().x + 320 - 720, player.GetPosition().y - 230 - 100 + 10);
                    btnplayagain.setPosition(player.GetPosition().x + 180 - 85, player.GetPosition().y + 150 - 20);
                    sbtnplayagain.setPosition(player.GetPosition().x + 180 - 85 - 25, player.GetPosition().y + 150 - 20 - 15);

                    Vector2i mouse = Mouse::getPosition(window);
                    printf(" mousepos x= %.0f y= %.0f ", (float)mouse.x, (float)mouse.y);

                    {
                        if (mouse.x > 803 and mouse.x < 1081 and mouse.y>490 and mouse.y < 635)
                            window.draw(sbtnplayagain);
                        else
                            window.draw(btnplayagain);

                        if (mouse.x > 803 and mouse.x < 1081 and mouse.y>490 and mouse.y < 635)
                            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                            {
                                goto start;
                                state = 1;
                            }

                        player.fallen = 1;
                        window.draw(btngameover);

                    }

                }
            
            window.display();
        }
        // setting popup
        else if (state == 2)
        { 

                     Vector2i mouse = Mouse::getPosition(window);
                     printf("mousepos x= %.0f y= %.0f\n", (float)mouse.x, (float)mouse.y);

                     back.setPosition(player.GetPosition().x - 700, player.GetPosition().y - 350);

                     btnreturn.setPosition(player.GetPosition().x +320 -720, player.GetPosition().y -230);
                     sbtnreturn.setPosition(player.GetPosition().x + 315 -720, player.GetPosition().y - 240);

                     comming.setPosition(player.GetPosition().x - 400, player.GetPosition().y - 150);

                     
                     window.clear(Color(150, 150, 150));
                     view.setCenter(player.GetPosition());
                     window.setView(view);

                     window.draw(back);
                    
                     window.draw(comming);


                     if (mouse.x > 990 - 720 and mouse.x < 1100 - 720 and mouse.y>92 and mouse.y < 200)
                         window.draw(sbtnreturn);
                     else
                        window.draw(btnreturn);
                    

                     

                     if (mouse.x > 990 - 720 and mouse.x < 1100 - 720 and mouse.y>92 and mouse.y < 200)
                         if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                             state = 0;
                        
                window.display();
            
        }
       

       
    }
}
