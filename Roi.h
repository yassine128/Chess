/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/
#ifndef ROI_H
#define ROI_H

#include "Piece.h"
#include "kingError.h"

class Roi : public Piece {
public:
    Roi(std::string couleur, std::pair<int, int> position);
    ~Roi();
    virtual std::vector<std::vector<std::pair<int, int>>> creationMoveList() override;
    // Il va falloir rajouter le compteur d'instances pour le TP6
private: 
    inline static int compteurInstance_ = 1; 
};


#endif // ROI_H
