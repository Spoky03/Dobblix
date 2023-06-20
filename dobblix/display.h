#ifndef DISPLAY_H
#define DISPLAY_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

class Picture;

class Display
{       
        void drawBoard(sf::RenderWindow&);
        void drawText(sf::RenderWindow&, std::string, std::string);
        void drawScore(sf::RenderWindow&, int);
        void drawTimer(sf::RenderWindow&);
        void drawPicture(sf::RenderWindow&, Picture&);
        void drawPictureLoop(sf::RenderWindow&, std::vector<Picture>);
        std::tuple <int,int> getPositionClicked(sf::RenderWindow&);
        void waitForInput(sf::RenderWindow&, std::vector<Picture>, std::vector<std::unique_ptr<sf::Sound>>&, int&);

public:
        void loopWindow();

};

#endif