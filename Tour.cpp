
/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/


#include "Tour.h"
#include <vector>

Tour::Tour(std::string couleur, std::pair<int, int> position) :
    Piece(couleur, position, couleur == "black" ? "./Images/tourb.png" : "./Images/tourw.png")
{

};

Tour::~Tour() {};

std::vector<std::vector<std::pair<int, int>>>  Tour::creationMoveList() {
    std::vector<std::vector<std::pair<int, int>>>  moveOk;

    int xPos = position_.first;
    int yPos = position_.second;

    std::vector<std::pair<int, int>> temp;
    for (int i = 1; movePossible(xPos + i, yPos); i++) { temp.push_back(std::pair(xPos + i, yPos)); } 
    moveOk.push_back(temp);

    temp.clear();
    for (int i = 1; movePossible(xPos - i, yPos); i++) { temp.push_back(std::pair(xPos - i, yPos)); }
    moveOk.push_back(temp);

    temp.clear(); 
    for (int i = 1; movePossible(xPos, yPos + i); i++) { temp.push_back(std::pair(xPos, yPos + i)); }
    moveOk.push_back(temp);

    temp.clear();
    for (int i = 1; movePossible(xPos, yPos - i); i++) { temp.push_back(std::pair(xPos, yPos - i)); }
    moveOk.push_back(temp);

    return moveOk; 
}
