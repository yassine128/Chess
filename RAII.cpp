/*
* Auteur: Yassine Seddaoui, Matei Zama
* Matricules: 2204548, 2207283
*/

#include "RAII.h"
RAII::RAII(LogiqueGame::Chessboard* board, const std::shared_ptr<Piece>& piece, std::pair<int, int> pos) :
	board_(board), previousPiece_(piece), pos_(pos), originalPos_(piece->getPosition()), originalAnciennePosition_(piece->getAnciennePosition()),
	pieceKilled_(board->getBoardSquare(pos.first, pos.second).getPiece())
{
	// On change la position de la piece dans le board 
	previousPiece_->setAnciennePosition(piece->getPosition());
	previousPiece_->setCurrentPosition(pos_);


	board_->getBoardSquare(originalPos_.first, originalPos_.second).setPiece(nullptr);
	board_->getBoardSquare(pos_.first, pos_.second).setPiece(previousPiece_);
}

RAII::~RAII() {
	// On doit remettre le board dans son état original 
	board_->getBoardSquare(pos_.first, pos_.second).setPiece(pieceKilled_);
	board_->getBoardSquare(originalPos_.first, originalPos_.second).setPiece(previousPiece_);

	// Restore the original anciennePosition of the piece.
	previousPiece_->setCurrentPosition(originalPos_);
	previousPiece_->setAnciennePosition(originalAnciennePosition_);
}