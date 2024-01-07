/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/
#include "chessBoard.h"
class RAII 
{
public: 
	RAII(LogiqueGame::Chessboard* board, const std::shared_ptr<Piece>& piece, std::pair<int, int> pos);
	~RAII(); 
private: 
	LogiqueGame::Chessboard* board_;
	std::pair<int, int> pos_;
	std::shared_ptr<Piece> previousPiece_;
	std::pair<int, int> originalPos_; 
	std::pair<int, int> originalAnciennePosition_; 
	std::shared_ptr<Piece> pieceKilled_;
};