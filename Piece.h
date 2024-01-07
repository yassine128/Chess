/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/
#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>

class Piece
{
public:
    Piece() = default;
    Piece(std::string couleur, std::pair<int, int> position_, std::string urlImage);
    virtual ~Piece() = default;

   // virtual mouvPossible(); 

    // Setter
    void setCurrentPosition(std::pair<int, int> currPos);
    void setAnciennePosition(std::pair<int, int> anciennePos);

    // Getter
    std::string getCouleur() const;
    std::pair<int, int> getPosition() const;
    std::pair<int, int> getAnciennePosition() const;
    std::string getUrlImage() const;

    virtual std::vector<std::vector<std::pair<int, int>>> creationMoveList() = 0;

    bool movePossible(int posX, int posY);

protected:
    std::string couleur_;
    std::pair <int, int> position_;
    std::pair <int, int> anciennePosition_;
    std::string urlImage_ = "";
};



#endif // PIECE_H
