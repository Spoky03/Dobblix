#include "display.h"
#include "code.h"

    
void Display::drawBoard(sf::RenderWindow& window)
    {
        sf::Texture texture;
        sf::Texture textureBackground;
        texture.loadFromFile("planks.jpg");
        textureBackground.loadFromFile("background.png");
        sf::RectangleShape rectangle(sf::Vector2f(sizeWindow*scaleWindow, sizeWindow*scaleWindow));
        rectangle.setTexture(&texture);
        sf::CircleShape circle(sizeWindow*scaleWindow/(scaleWindow+1));
        circle.setTexture(&textureBackground);
        //circle.setFillColor(sf::Color(100,100,100,255));
        rectangle.setTexture(&texture);
        window.draw(rectangle);
        rectangle.setPosition(sizeWindow, 0);
        window.draw(rectangle);
        window.draw(circle);
        circle.setPosition(sizeWindow, 0);
        window.draw(circle);

}
void Display::drawText(sf::RenderWindow& window, std::string string, std::string color){
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text(string, font);
    text.setPosition(sizeWindow/4, sizeWindow/4);
    text.setCharacterSize(200);
    if (color == "red"){text.setFillColor(sf::Color::Red);}
    else if (color == "green"){text.setFillColor(sf::Color::Green);}
    else {text.setFillColor(sf::Color::White);}
    window.clear();
    window.draw(text);
    window.display();
}
void Display::drawScore(sf::RenderWindow& window, int score){
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text(std::to_string(score), font);
    text.setPosition(0, sizeWindow);
    text.setCharacterSize(44);
    if (score<=0) {text.setFillColor(sf::Color::Red);}
    else {text.setFillColor(sf::Color::Green);}
    window.draw(text);
}
void Display::drawTimer(sf::RenderWindow& window){
    sf::Clock clock;
    clock.restart();
    sf::Time time1 = clock.getElapsedTime();
    int seconds = int(time1.asSeconds()) % 60;
    std::ostringstream str;
    str << seconds;
    std :: string secondsString = str.str();
    std::cout << "time: " << secondsString << std::endl;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text(secondsString, font);
    text.setPosition(800, sizeWindow);
    text.setCharacterSize(44);
    text.setFillColor(sf::Color::White);
    //window.draw(text);
}

void Display::drawPicture(sf::RenderWindow& window, Picture& picture){
    sf::Texture texture;
    texture.loadFromFile(picture.getPath());
    sf::Sprite sprite;
    sprite.setOrigin (texture.getSize().x/2, texture.getSize().y/2);
    sprite.setTexture(texture);
    sprite.setPosition(std::get<0>(picture.position), std::get<1>(picture.position));
    sprite.setRotation(picture.rotation);
    sprite.setScale(picture.size, picture.size);
    window.draw(sprite);

}
void Display::drawPictureLoop(sf::RenderWindow& window, std::vector<Picture> chosenPictures){
    for (int i = 0; i < chosenPictures.size(); i++){
        drawPicture(window, chosenPictures[i]);
    }
}

std::tuple <int,int> Display::getPositionClicked(sf::RenderWindow& window){
    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {break;}
        }
        else if (event.type == sf::Event::Closed){window.close();break;}
        else if (sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Escape){window.close();break;}
        }
    }
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    //std :: cout << "clicked pos:"<<localPosition.x << " " << localPosition.y << std::endl;
    return std::make_tuple(localPosition.x, localPosition.y);
}
void Display::waitForInput(sf::RenderWindow& window, std::vector<Picture> BoardState, std::vector<std::unique_ptr<sf::Sound>>& soundList, int &score) {
    sf::Event event;
    while (window.waitEvent(event)) {   
        while(true){
            
            std::tuple <int,int> positionClicked = getPositionClicked(window);
            int flag = (isPictureClickedTheDupe(BoardState, positionClicked));
            if (flag==0) {
                soundList[2]->play();  
                continue;
            }
            else if (flag == 1){
                soundList[0]->play();
                drawText(window, "Dobry obrazek", "green");
                score++;
                break;
            }
            else if(flag==-1){
                soundList[1]->play(); 
                score--;       
                drawText(window, "Zly obrazek", "red");

                break;
            }
        } 
        if(autoSkip==true){sf::sleep(sf::milliseconds(300));break;}
        while (window.waitEvent(event) and autoSkip==false) {
            if (event.type == sf::Event::MouseButtonPressed){if (event.mouseButton.button == sf::Mouse::Left) {break;}}
        }
    }
}


void Display::loopWindow()
{
    sf::RenderWindow window(sf::VideoMode(sizeWindow*2*scaleWindow, sizeWindow*scaleWindow+80), "Dobblix");
    window.setFramerateLimit(5);
    while (window.isOpen())
    {   
        sf::Event event;
        //sf::Thread thread(&drawTimer, &window);
        
        std::unique_ptr<int> score = std::make_unique<int>();

        //sound https://en.sfml-dev.org/forums/index.php?topic=28780.0
        std::map<std::string, std::unique_ptr<sf::SoundBuffer>> map;
        std::vector<std::unique_ptr<sf::Sound>> soundList;

        std::unique_ptr<sf::SoundBuffer> buffer = std::make_unique<sf::SoundBuffer>();
        buffer->loadFromFile("good.wav");
        map["good.wav"] = std::move(buffer);
        soundList.push_back(std::make_unique<sf::Sound>(*map["good.wav"]));

        std::unique_ptr<sf::SoundBuffer> buffer2 = std::make_unique<sf::SoundBuffer>();
        buffer2->loadFromFile("error.wav");
        map["error.wav"] = std::move(buffer2);
        soundList.push_back(std::make_unique<sf::Sound>(*map["error.wav"]));

        std::unique_ptr<sf::SoundBuffer> buffer3 = std::make_unique<sf::SoundBuffer>();
        buffer3->loadFromFile("miss.wav");
        map["miss.wav"] = std::move(buffer3);
        soundList.push_back(std::make_unique<sf::Sound>(*map["miss.wav"]));

        while(window.pollEvent(event)){  
            //thread.launch();
            window.clear();
            drawScore(window, *score);
            this->drawBoard(window);
            std::unique_ptr<std::vector<Picture> > currentBoardState = std::make_unique<std::vector<Picture> >();
            *currentBoardState = makePictureLoop();
            *currentBoardState = chooseNPictures(*currentBoardState);
            *currentBoardState = chooseNPicturesWithDupe(*currentBoardState);
            *currentBoardState = makePositionCircle(*currentBoardState);
            this->drawPictureLoop(window, *currentBoardState);
            window.display();
            waitForInput(window, *currentBoardState, soundList, *score);               
        }
    }
}



