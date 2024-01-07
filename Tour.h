/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/
#ifndef TOUR_H
#define TOUR_H

#include "Piece.h"

class Tour : public Piece {
public:
    Tour(std::string couleur, std::pair<int, int> position);
    ~Tour();
    virtual std::vector<std::vector<std::pair<int, int>>> creationMoveList() override;
};


#endif // TOUR_H
