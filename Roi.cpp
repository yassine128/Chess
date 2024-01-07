/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/

#include "Roi.h"

Roi::Roi(std::string couleur, std::pair<int, int> position) :
    Piece(couleur, position, couleur == "black" ? "./Images/kingb.png" : "./Images/kingw.png")
{ 
    if (compteurInstance_ >= 2) {
        throw KingException("Vous ne pouvez pas creer plus de 2 rois.");
    }
    compteurInstance_++;
};

Roi::~Roi() {compteurInstance_--;};


std::vector<std::vector<std::pair<int, int>>> Roi::creationMoveList() {
    std::vector<std::vector<std::pair<int, int>>> moveOk;

    int xPos = position_.first;
    int yPos = position_.second;

    std::vector<std::pair<int, int>> temp; 
    movePossible(xPos + 1, yPos) ? temp.push_back(std::pair(xPos + 1, yPos)) : void();
    movePossible(xPos - 1, yPos) ? temp.push_back(std::pair(xPos - 1, yPos)) : void();
    movePossible(xPos, yPos + 1) ? temp.push_back(std::pair(xPos, yPos + 1)) : void();
    movePossible(xPos, yPos - 1) ? temp.push_back(std::pair(xPos, yPos - 1)) : void();
    movePossible(xPos + 1, yPos + 1) ? temp.push_back(std::pair(xPos + 1, yPos + 1)) : void();
    movePossible(xPos - 1, yPos - 1) ? temp.push_back(std::pair(xPos - 1, yPos - 1)) : void();
    movePossible(xPos + 1, yPos - 1) ? temp.push_back(std::pair(xPos + 1, yPos - 1)) : void();
    movePossible(xPos - 1, yPos + 1) ? temp.push_back(std::pair(xPos - 1, yPos + 1)) : void();
    moveOk.push_back(temp);

    return moveOk;
}