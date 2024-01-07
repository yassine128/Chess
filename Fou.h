/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/
#ifndef FOU_H
#define FOU_H

#include "Piece.h"

class Fou : public Piece
{
public:
    Fou(std::string couleur, std::pair<int, int> position);
    ~Fou();
    std::vector<std::vector<std::pair<int, int>>> creationMoveList() override;
};

#endif // FOU_H
