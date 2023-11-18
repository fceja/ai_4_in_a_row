#include <iostream>

#ifndef UNTITLED2_GAME_H
#define UNTITLED2_GAME_H

using namespace std;

class Game {

public:
    int gameTurn = 0;
    int piecesOnBoardCount = 0;
    string currPiecesOnBoard;
    string gameBoard[33][12];

    void addToMovesArray(string, int, int);
    void createInitialPiecesOnBoard();
    void createInitialGameBoard(string, string);
    void printCurrGameBoard();
    void updatePiecesOnBoard();
    void askAgentMove(int, int);
    void askOpponentMove(int, int);
    bool checkIfValidMove(string);
    int checkPieceID(string);
    bool goalCheck();
    void agentsMove(string, int, int);
};


#endif //UNTITLED2_GAME_H
