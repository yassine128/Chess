// Les test pour le Modèle pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca

#include "chessboard.h"
#include "Piece.h"
#include "Tour.h"
#include "Roi.h"
#include "Fou.h"

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

TEST(Chessboard, tour_mouvement) {
	LogiqueGame::Chessboard chess;
	std::shared_ptr<Piece> p = std::make_shared<Tour>(Tour("black", std::make_pair(0, 0)));
	chess.getBoardSquare(0, 0).setPiece(p);

	std::vector<std::pair<int, int>> testPossible = chess.mouvementsPossibles(p);
	std::vector<std::pair<int, int>> testReponse = {
		{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, 
		{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}
	};

	ASSERT_EQ(testPossible, testReponse);	
}

TEST(Chessboard, roi_mouvement) {
	LogiqueGame::Chessboard chess;
	std::shared_ptr<Piece> p = std::make_shared<Roi>(Roi("black", std::make_pair(0, 0)));
	chess.getBoardSquare(0, 0).setPiece(p);

	std::vector<std::pair<int, int>> testPossible = chess.mouvementsPossibles(p);
	std::vector<std::pair<int, int>> testReponse = {
		{1, 0}, {0, 1}, {1, 1}
	};

	ASSERT_EQ(testPossible, testReponse);
}

TEST(Chessboard, fou_mouvement) {
	LogiqueGame::Chessboard chess;
	std::shared_ptr<Piece> p = std::make_shared<Fou>(Fou("black", std::make_pair(0, 0)));
	chess.getBoardSquare(0, 0).setPiece(p);

	std::vector<std::pair<int, int>> testPossible = chess.mouvementsPossibles(p);
	std::vector<std::pair<int, int>> testReponse = {
		{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7},
	};

	ASSERT_EQ(testPossible, testReponse);
}

TEST(Chessboard, set_board) {
    LogiqueGame::Chessboard chess;
    chess.setBoard("roi", "white", std::make_pair(4, 0));

    auto piece = chess.getBoardSquare(4, 0).getPiece();
    ASSERT_TRUE(piece != nullptr);
    ASSERT_EQ(piece->getCouleur(), "white");
    ASSERT_EQ(piece->getPosition(), std::make_pair(4, 0));
}

TEST(Chessboard, changer_position) {
    LogiqueGame::Chessboard chess;
    chess.setBoard("roi", "white", std::make_pair(4, 0));

    auto piece = chess.getBoardSquare(4, 0).getPiece();
    chess.changePosition(piece, std::make_pair(4, 1), { {4, 1} });

    auto newPiece = chess.getBoardSquare(4, 1).getPiece();
    ASSERT_TRUE(newPiece != nullptr);
    ASSERT_EQ(newPiece->getCouleur(), "white");
    ASSERT_EQ(newPiece->getPosition(), std::make_pair(4, 1));
}

TEST(Chessboard, chercher_check) {
    LogiqueGame::Chessboard chess;
    chess.setBoard("roi", "white", std::make_pair(4, 0));
    chess.setBoard("tour", "black", std::make_pair(0, 0));

    auto check = chess.chercheCheck("white");
    ASSERT_TRUE(check);
}

TEST(Chessboard, clear_board) {
    LogiqueGame::Chessboard chess;
    chess.setBoard("roi", "white", std::make_pair(4, 0));
    chess.setBoard("tour", "black", std::make_pair(0, 0));

    chess.clearBoard();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ASSERT_TRUE(chess.getBoardSquare(i, j).getPiece() == nullptr);
        }
    }
}

TEST(Chessboard, change_tour) {
    LogiqueGame::Chessboard chess;
    chess.changeTours(); 

    ASSERT_TRUE(chess.getTours() == "black");
}

#endif
