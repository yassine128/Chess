/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/
#include "chessboard.h"
#include "Roi.h"
#include "Fou.h"
#include "Tour.h"
#include <algorithm>
#include "RAII.h"
#include <fstream>
#include <iomanip>
#include <sstream>

Square::Square() {}
Square::Square(std::pair<int, int> p) : pos(p), occupe(0), piece_(nullptr) {}
void Square::setPiece(std::shared_ptr<Piece> piece) {piece_ = piece;};
bool Square::getOccupe() const {return occupe;}
std::shared_ptr<Piece> Square::getPiece() {return piece_;}


std::pair<int, int> Square::getPos() const {
    return pos;
}

LogiqueGame::Chessboard::Chessboard() {
    tour_= "white";
    // Initialisation
    // création du tableau de Square
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++){
            std::pair<int, int> p = std::make_pair(i, j);
            board[i][j] = Square(p);
        }
    }
};

LogiqueGame::Chessboard::~Chessboard() {};

std::string LogiqueGame::Chessboard::getTours() const {
    return tour_;
};

void LogiqueGame::Chessboard::changeTours() {

    if(tour_ == "white")
        tour_ = "black";
    else
        tour_= "white";
}

Square& LogiqueGame::Chessboard::getBoardSquare(int x, int y) {
    return board[x][y];
}


void LogiqueGame::Chessboard::setBoard(std::string type, std::string color, std::pair<int, int> position) {

    try {
        std::shared_ptr<Piece> piece; 
        if (type == "roi") {
            piece = std::make_shared<Roi>(color, position);
            board[piece.get()->getPosition().first][piece.get()->getPosition().second].setPiece(piece);
        }
        else if (type == "tour") {
            piece = std::make_shared<Tour>(color, position);
            board[piece.get()->getPosition().first][piece.get()->getPosition().second].setPiece(piece);
        }
        else if (type == "fou") {
            piece = std::make_shared<Fou>(color, position);
            board[piece.get()->getPosition().first][piece.get()->getPosition().second].setPiece(piece);
        }
        listePieces.push_back(piece);
    }
    catch (KingException& e) {
        std::cout << e.what() << std::endl; 
    }
}

void LogiqueGame::Chessboard::creationPieces(std::string nomFichier) {
    std::string dossier = "./ListOfEndGames/" + nomFichier + ".txt";
    std::ifstream fichier(dossier);
    std::string line;
    do {
        std::string type, couleur;
        int posX, posY;

        fichier >> std::quoted(type) >> std::quoted(couleur) >> posX >> posY;
        setBoard(type, couleur, std::make_pair(posX, posY));
    } while (getline(fichier, line));
}


void LogiqueGame::Chessboard::changePosition(std::shared_ptr<Piece> piece, std::pair<int, int> newPos, std::vector<std::pair<int, int>> mouvPos) {
    // On change la piece de position (Plus tard, il faudra vérifier si le mouvement est valide, si la piece sur l'autre case est ennemi ou alié)
    if (piece != nullptr && std::count(mouvPos.begin(), mouvPos.end(), newPos) && tour_ == piece->getCouleur()) {
        std::shared_ptr<Piece> tempPiece = board[newPos.first][newPos.second].getPiece();
        if (tempPiece) {
            auto it = std::find(listePieces.begin(), listePieces.end(), tempPiece);
            listePieces.erase(it);
        }
        bool therewascheck = false; 
        {
            RAII raii(this, piece, newPos);
            std::string lastTour = tour_;
            changeTours();
            if (chercheCheck(lastTour)) {
                therewascheck = true; 
                if (tempPiece) {
                    listePieces.push_back(tempPiece);
                }
                changeTours();
            }
        }
        if (!therewascheck) {
           piece->setAnciennePosition(piece->getPosition());
           piece->setCurrentPosition(newPos);
           board[piece->getAnciennePosition().first][piece->getAnciennePosition().second].setPiece(nullptr);
           board[newPos.first][newPos.second].setPiece(piece);
        }
    }
}

// Permet de filtrer les mouvements possibles 
std::vector<std::pair<int, int>> LogiqueGame::Chessboard::mouvementsPossibles(std::shared_ptr<Piece> piece) {
    std::vector<std::pair<int,int>> moveOk;
    if (piece == nullptr)
        return moveOk;

    if (auto roi = dynamic_cast<Roi*>(piece.get())) {
        std::vector<std::vector<std::pair<int, int>>> tempMove = roi->creationMoveList();
        //for (std::vector<std::pair<int, int>> v : tempMove) {
            for (std::pair<int, int> p : tempMove[0])
                if (movePossible(p.first, p.second, piece, moveOk)) {
                    moveOk.push_back(p);
                }
        //}
    }

    else if (auto fou = dynamic_cast<Fou*>(piece.get())) {
        std::vector<std::vector<std::pair<int, int>>> tempMove = fou->creationMoveList();
        for (std::vector<std::pair<int, int>> v : tempMove) {
            for (std::pair<int, int> p : v)
                if (movePossible(p.first, p.second, piece, moveOk))
                    moveOk.push_back(p);
                else
                    break; 
        }
    }
    else if (auto tour = dynamic_cast<Tour*>(piece.get())) {
        std::vector<std::vector<std::pair<int, int>>> tempMove = tour->creationMoveList();
 
        for (std::vector<std::pair<int, int>> v : tempMove) {
            for (std::pair<int, int> p : v)
                if (movePossible(p.first, p.second, piece, moveOk))
                    moveOk.push_back(p);
                else
                    break; 
        }
    }

    return moveOk; // Vecteur des mouvements possibles
}

bool LogiqueGame::Chessboard::movePossible(int posX, int posY, std::shared_ptr<Piece> piece, std::vector<std::pair<int,int>>& moveOk) {
    //allImpossibleMoves.clear();  

    if (posX > 7 || posX < 0 || posY > 7 || posY < 0)
        return false;
    if (board[posX][posY].getPiece() == nullptr)
        return true;
    else if (board[posX][posY].getPiece() != nullptr && board[posX][posY].getPiece()->getCouleur() == piece->getCouleur())
        return false;
    else if (board[posX][posY].getPiece() != nullptr && board[posX][posY].getPiece()->getCouleur() != piece->getCouleur()) {
        moveOk.push_back(std::pair<int, int>(posX, posY));
        return false;
    }

    return false;
};

bool LogiqueGame::Chessboard::chercheCheck(std::string lastTour) {
    // On veut passer à travers toutes les pieces de couleur opposé et voir si dans les movePossibles, le roi de notre couleur en fait partie.
    std::vector<std::pair<int, int>> tempListe;
    for (std::shared_ptr<Piece> p : listePieces) {
            // On regarde seulement les pieces enemies
            if (p->getCouleur() != lastTour) {
                tempListe = mouvementsPossibles(p);
                for (int i = 0; i < tempListe.size(); i++) {
                    if (auto roi = dynamic_cast<Roi*>(getBoardSquare(tempListe[i].first, tempListe[i].second).getPiece().get()))
                            return true;
                }
            }
    }
    return false;
}

void LogiqueGame::Chessboard::clearBoard() {
    tour_ = "white";
    listePieces.clear();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j].setPiece(nullptr);
        }
    }
}