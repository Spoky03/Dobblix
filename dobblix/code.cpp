#include "code.h"
std::mt19937 rng(){
    std::random_device rd;
    std::mt19937 rng(rd());
    return rng;
}
void Picture::makeName(std::string path){
    std::string name;
    for (int i = path.length()-1; i >= 0; i--){
        if (path[i] == '/'){
            break;
        }
        else {
            name = path[i] + name;
        }
    }
    //remove .png from name
    name.erase(name.end()-4, name.end());
    this->name = name;
}
void Picture::makePicture(int id, std::string path){
    this->id = id;
    this->path = path;
    makeName(path);
    this->rotation = 0;
    this->size = 9;
    this->position = std::make_tuple(69, 69);
    this->isDupe = false;
    
}
std::vector<Picture> chooseNPictures(std::vector<Picture> &pictureList){
    //choose random n*2-1 pictures
    std::unique_ptr <std::vector <Picture>> chosenPictures = std::make_unique <std::vector <Picture>>();
    std::sample(pictureList.begin() , pictureList.end() , std::back_inserter(*chosenPictures), n*2-1 , rng() );
    return *chosenPictures;
    
}

std::vector<Picture> chooseNPicturesWithDupe(std::vector<Picture> &pictureList){
    std::vector <Picture>* chosenPictures = new std::vector <Picture>;
    std::shuffle(pictureList.begin(), pictureList.end(), rng());
    std::vector <Picture> firstPart;
    std::vector <Picture> secondPart;
    for (int i = 0; i < pictureList.size(); i++){
        if (i < pictureList.size()/2 + 1){
            pictureList[i].setIsLeft(true);
            firstPart.push_back(pictureList[i]);
        }
        else {
            pictureList[i].setIsLeft(false);
            secondPart.push_back(pictureList[i]);
        }
    }
    int tempRand = rng()() % firstPart.size();
    firstPart[tempRand].setIsLeft(true);firstPart[tempRand].setIsDupe(true);
    Picture dupe = firstPart[tempRand];
    dupe.setIsLeft(false);
    dupe.setIsDupe(true);
    secondPart.push_back(dupe);
    std::shuffle(firstPart.begin(), firstPart.end(), rng());
    std::shuffle(secondPart.begin(), secondPart.end(), rng());
    for (int i = 0; i < firstPart.size(); i++){
        chosenPictures->push_back(firstPart[i]);
    }
    for (int i = 0; i < secondPart.size(); i++){
        chosenPictures->push_back(secondPart[i]);
    }
    for (int i = 0; i < chosenPictures->size(); i++){
        if(chosenPictures->at(i).getIsDupe() == true){
        std::cout << chosenPictures->at(i).getName() << " " << chosenPictures->at(i).getIsDupe() << " " << chosenPictures->at(i).getIsLeft() << std::endl;
    }}
    return *chosenPictures;
}
std::vector<Picture> makePositionCircle(std::vector<Picture> &pictureList){
    std::unique_ptr <std::vector <Picture>> chosenPictures = std::make_unique <std::vector <Picture>>();
    for (int i = 0; i < pictureList.size(); i++){
        chosenPictures->push_back(pictureList[i]);
    }
    std::tuple <int, int> position;
    std::vector <int> lg; //vector of 1
    int ang = 360/n;
    std::vector <int> angList;
    for (int i = 0; i < n; i++){
        angList.push_back(ang*i);
    }
    //make circle
    for (int i = 0; i <n; i++){
        int x = sizeWindow/2 + (sizeWindow/2 - 100)*cos(angList[i]*3.141/180);
        int y = sizeWindow/2 + (sizeWindow/2 - 100)*sin(angList[i]*3.141/180);
        position = std::make_tuple(x, y);
        chosenPictures->at(i).setPosition(position);
        chosenPictures->at(i).setRandomRotation();
    }
    //make second circle
    for (int i = 0; i < n; i++){
        int x = sizeWindow/2 + (sizeWindow/2 - 100)*cos(angList[i]*3.141/180)+800;
        int y = sizeWindow/2 + (sizeWindow/2 - 100)*sin(angList[i]*3.141/180);
        position = std::make_tuple(x, y);
        chosenPictures->at(i+n).setPosition(position);
        chosenPictures->at(i+n).setRandomRotation();
    }

    return *chosenPictures;
}
void Picture::setRandomRotation(){
    int tempRand = rng()() % 6;
    this->rotation = tempRand*60;

}

PositionOfSamePictures getSamePictures(std::vector<Picture> &pictureList){   
    PositionOfSamePictures positionOfDupes;
    for (int i = 0; i < pictureList.size(); i++){
        if (pictureList[i].getIsDupe() == true){
            if (pictureList[i].getIsLeft() == true){positionOfDupes.first = pictureList[i].getPosition();}
            else{positionOfDupes.second = pictureList[i].getPosition();}
        }
    }
    return positionOfDupes;
}
bool isInBetweenTwoCoordinates(std::tuple <int,int> originPoint, std::tuple <int,int> input){
    int picSize = 128/2;
    std::tuple <int,int> LT = std::make_tuple(std::get<0>(originPoint)-picSize, std::get<1>(originPoint)-picSize);
    std::tuple <int,int> RB = std::make_tuple(std::get<0>(originPoint)+picSize, std::get<1>(originPoint)+picSize);
    if (std::get<0>(input) > std::get<0>(LT) and std::get<0>(input) < std::get<0>(RB) and std::get<1>(input) > std::get<1>(LT) and std::get<1>(input) < std::get<1>(RB)){
        return true;
    }
    else {return false;}
}
int isPictureClickedTheDupe(std::vector<Picture> pictureList, std::tuple <int,int> input){
    PositionOfSamePictures positionOfDupes = getSamePictures(pictureList);
    if (isInBetweenTwoCoordinates(positionOfDupes.first, input) or isInBetweenTwoCoordinates(positionOfDupes.second, input)){
        return 1;}
    else {
        for (int i = 0; i < pictureList.size(); i++){
            if (isInBetweenTwoCoordinates(pictureList[i].getPosition(), input)){return -1;}
        }}
    return 0; 
}
std::vector<Picture> makePictureLoop(){
    std::unique_ptr <std::vector <Picture>> pictureList = std::make_unique <std::vector <Picture>>();
    std::ifstream namesFile("names.txt");
    std::string Text;
    int i = 0;
    while (std::getline (namesFile, Text)){
       if (pictureList->size()<symbolAmount) {
            Picture picture;
            Text = "pictures/" + Text;
            picture.makePicture(i, Text);
            pictureList->push_back(picture);
            i++;
        }
        else {break;}
    }
    namesFile.close();
    return *pictureList;
}




