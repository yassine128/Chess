/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/
#include "Fou.h"

Fou::Fou(std::string couleur, std::pair<int, int> position) :
    Piece(couleur, position, couleur == "black" ? "./Images/foub.png" : "./Images/fouw.png")
{

};

Fou::~Fou() {};

std::vector<std::vector<std::pair<int, int>>> Fou::creationMoveList() {
    std::vector<std::vector<std::pair<int, int>>> moveOk;

    int xPos = position_.first;
    int yPos = position_.second;

    std::vector<std::pair<int, int>> temp; 
    for (int i = 1; movePossible(xPos + i, yPos + i); ++i) { temp.push_back(std::pair(xPos + i, yPos + i)); }
    moveOk.push_back(temp); 

    temp.clear();
    for (int i = 1; movePossible(xPos - i, yPos + i); ++i) { temp.push_back(std::pair(xPos - i, yPos + i)); }
    moveOk.push_back(temp);

    temp.clear();
    for (int i = 1; movePossible(xPos + i, yPos - i); ++i) { temp.push_back(std::pair(xPos + i, yPos - i)); }
    moveOk.push_back(temp);

    temp.clear(); 
    for (int i = 1; movePossible(xPos - i, yPos - i); ++i) { temp.push_back(std::pair(xPos - i, yPos - i)); }
    moveOk.push_back(temp);

    return moveOk;
}
