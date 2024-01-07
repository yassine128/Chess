/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/
#include "Piece.h"

Piece::Piece(std::string couleur, std::pair<int, int> position, std::string urlImage) {
    couleur_ = couleur;
    position_ = position;
    urlImage_ = urlImage;
};

// Getter
std::string Piece::getCouleur() const {return couleur_;};
std::pair<int, int> Piece::getPosition() const {return position_;};
std::pair<int, int> Piece::getAnciennePosition() const {return anciennePosition_;};
std::string Piece::getUrlImage() const {return urlImage_;};

void Piece::setCurrentPosition(std::pair<int, int> currPos) {
    position_ = currPos;
}
void Piece::setAnciennePosition(std::pair<int, int> anciennePos) {
    anciennePosition_ = anciennePos;
}

bool Piece::movePossible(int posX, int posY) {
    if (posX > 7 || posX < 0 || posY > 7 || posY < 0)
        return false;
    return true; 
}