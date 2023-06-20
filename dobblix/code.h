#ifndef CODE_H
#define CODE_H
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <random>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <memory>
#include <functional>
#include <thread>
#include <SFML/System.hpp>

//changeable variables
const int n = 8; //game size
const float scaleWindow = 1; //window scale
const bool autoSkip = true; //auto skip to next picture
//fixed varxiables
const int symbolAmount = (n*n)-n+1; // fixed amount of pictues and cards in game 
const int sizeWindow = 800; //window size

class Picture
{
    private:
        int id;
        std::string name;
        std::string path;
        int rotation;
        int size;
        bool isDupe;
        bool isLeft;
        std::tuple <int, int> position;
    public: 
        int getId() {return id;}
        std::string getName() {return name;} 
        std::string getPath() {return path;}
        int getRotation() {return rotation;}
        int getSize() {return size;}
        std::tuple <int, int> getPosition() {return position;}
        bool getIsDupe() {return isDupe;}
        bool getIsLeft() {return isLeft;}
        void setPosition(std::tuple <int, int> pos) {position = pos;}
        void makePicture(int id, std::string name);
        void makeName(std::string path);
        void setRotation(int rotation) {this->rotation = rotation;}
        void setSize(int size) {this->size = size;}
        void setIsDupe(bool isDupe) {this->isDupe = isDupe;}
        void setIsLeft(bool isLeft) {this->isLeft = isLeft;}
        void setRandomRotation();
        
    friend class Display;
};

std::vector<Picture> makePictureLoop();
std::vector<Picture> chooseNPictures(std::vector<Picture>&);
std::vector<Picture> chooseNPicturesWithDupe(std::vector<Picture>&);
std::vector<Picture> makePositionCircle(std::vector<Picture>&);
std::tuple <int,int> getRightBottomCorner(std::tuple <int,int>);
bool isInBetweenTwoCoordinates(std::tuple <int,int>, std::tuple <int,int>);
int isPictureClickedTheDupe(std::vector<Picture>, std::tuple <int,int>);
struct PositionOfSamePictures{std::tuple <int,int> first;std::tuple <int,int> second;};
PositionOfSamePictures getSamePictures(std::vector<Picture>&);
std::mt19937 rng();

#endif