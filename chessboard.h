/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <memory>
#include "Piece.h"
#include <vector>

struct Square
{
public:
    Square();
    Square(std::pair<int, int>);
    void setPiece(std::shared_ptr<Piece> piece);
    bool getOccupe() const;
    std::pair<int, int> getPos() const;
    std::shared_ptr<Piece> getPiece();
private:
    std::pair<int, int> pos;
    bool occupe;
    std::shared_ptr<Piece> piece_;
};

namespace LogiqueGame {
    class Chessboard
    {
    public:
        Chessboard();
        ~Chessboard();
        std::vector<std::pair<int, int>> mouvementsPossibles(std::shared_ptr<Piece> piece);
        Square& getBoardSquare(int, int);
        void creationPieces(std::string nomFichier);
        void changePosition(std::shared_ptr<Piece> piece, std::pair<int, int> newPos, std::vector<std::pair<int, int>> mouvPoss);
        bool movePossible(int posX, int posY, std::shared_ptr<Piece> piece, std::vector<std::pair<int, int>>& moveOk);
        std::vector<std::pair<int, int>> prevChoix;
        std::string getTours() const;
        void changeTours();
        bool chercheCheck(std::string lastTour);
        void setBoard(std::string type, std::string color, std::pair<int, int> position);
        void clearBoard();
        std::vector<std::shared_ptr<Piece>> listePieces;

    private:
        std::string tour_;
        std::vector<std::pair<int, int>> allImpossibleMoves;
        Square board[8][8];
    };
}


#endif // CHESSBOARD_H
