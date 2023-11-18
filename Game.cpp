#include "Game.h"
#include <string>

bool Game::goalCheck(){

    piecesOnBoardCount++;

    if(piecesOnBoardCount == 64){
        cout << "\n\t  Draw." << endl;
        exit(EXIT_SUCCESS);
    }

    int start = 0;
    int end = 4;
    int lastCol = 8;

    // checks for horizontal 4 in a row
    for(int row = 0; row < 8; row++) {
        for (int i = start; i < end; i++) {
            if ((currPiecesOnBoard.at(i) == 'X' && currPiecesOnBoard.at(i + 1) == 'X' &&
                 currPiecesOnBoard.at(i + 2) == 'X' && currPiecesOnBoard.at(i + 3) == 'X') ||
                (currPiecesOnBoard.at(i) == 'O' && currPiecesOnBoard.at(i + 1) == 'O' &&
                 currPiecesOnBoard.at(i + 2) == 'O' && currPiecesOnBoard.at(i + 3) == 'O')) {
               // cout << "Game over." << endl;
                gameBoard[gameTurn+1][11] += " win";
                printCurrGameBoard();
                return true;
            }
            if (end == lastCol) {
                break;
            } else {
                end++;
            }
        }
        start += 8;
        end += 4;
        lastCol +=8;
    }


    // resets for vertical check
    start = 0;
    end = 25;
    int lastRow = 57;

    // check for vertical 4 in a row
    for(int col = 0; col < 8; col++) {
        for (int i = start; i < end; i+=8) {
            if ((currPiecesOnBoard.at(i) == 'X' && currPiecesOnBoard.at(i + 8) == 'X' &&
                 currPiecesOnBoard.at(i + 16) == 'X' && currPiecesOnBoard.at(i + 24) == 'X') ||
                (currPiecesOnBoard.at(i) == 'O' && currPiecesOnBoard.at(i + 8) == 'O' &&
                 currPiecesOnBoard.at(i + 16) == 'O' && currPiecesOnBoard.at(i + 24) == 'O')) {
               // cout << "Game over." << endl;
                gameBoard[gameTurn+1][11] += " win";
                printCurrGameBoard();

                return true;
            }
            if (end >= lastRow) {
                break;
            } else {
                end += 8;
            }
        }
        start++;
        end = 26+col;
        lastRow++;
    }
    return false;
}

void Game::createInitialPiecesOnBoard() { // creates initial board pieces.
    for (int i = 0; i < 64; i++) {
        currPiecesOnBoard += "-";
    }
    updatePiecesOnBoard();
}

void Game::updatePiecesOnBoard() {// add values from string to board
    int boardIndex = 0;

    for (int row = 1; row < 9; row++) {
        for (int col = 1; col < 9; col++) {
            gameBoard[row][col] = currPiecesOnBoard.at(boardIndex);
            boardIndex++;
        }
    }
}

void Game::createInitialGameBoard(string goesFirst, string goesSecond) { // adds labels to displayed board
    // labels horizontal axis
    gameBoard[0][0] = " ";
    gameBoard[0][1] = "1";
    gameBoard[0][2] = "2";
    gameBoard[0][3] = "3";
    gameBoard[0][4] = "4";
    gameBoard[0][5] = "5";
    gameBoard[0][6] = "6";
    gameBoard[0][7] = "7";
    gameBoard[0][8] = "8";

    // labels vertical axis
    gameBoard[0][0] = " ";
    gameBoard[1][0] = "A";
    gameBoard[2][0] = "B";
    gameBoard[3][0] = "C";
    gameBoard[4][0] = "D";
    gameBoard[5][0] = "E";
    gameBoard[6][0] = "F";
    gameBoard[7][0] = "G";
    gameBoard[8][0] = "H";

    // adds  'vs' title in proper order
    goesFirst = "\t\t" + goesFirst;
    gameBoard[0][9] = goesFirst;
    gameBoard[0][10] = "vs.";
    gameBoard[0][11] = goesSecond;

}

void Game::printCurrGameBoard() { // prints board with current pieces
    cout << endl << endl;
    for (int row = 0; row < 9; row++) { // prints up to H
        for (int col = 0; col < 12; col++) {
            cout << gameBoard[row][col] << " ";
        }
        cout << endl;
    }

    if(gameTurn >= 8){
        for (int row = 9; row < gameTurn+2; row++) {
            for (int col = 9; col < 12; col++) {
                if(col == 9){
                    cout << "\t\t" + gameBoard[row][col] << " ";
                }
                else {
                    cout << gameBoard[row][col] << " ";
                }
            }
            cout << endl;
        }
    }

}

void Game::askAgentMove(int iGoFirst, int iAmAgent) { //ask's for agent move
    string moveMade;
    bool inValidInput = true;
    bool moveIsIllegal;

    // validates input
    // checks if piece already on board, and bounds check
    while (inValidInput) {
        cout << "\nChoose Agents's move: " << endl;
        cin >> moveMade;

        moveIsIllegal = checkIfValidMove(moveMade);

        if (moveIsIllegal) {
            cout << "\n** Illegal move **" << endl;
        } else {
            inValidInput = false;
        }
    }

    // determines if playing as 'X' or 'O'
    if(iGoFirst == 0){
        //agent goes first
        currPiecesOnBoard.at(checkPieceID(moveMade)) = 'X';
    }else{
        // agent goes second
        currPiecesOnBoard.at(checkPieceID(moveMade)) = 'O';
    }

    addToMovesArray(moveMade, iGoFirst, iAmAgent);
    updatePiecesOnBoard();
    printCurrGameBoard();
}

void Game::askOpponentMove(int iGoFirst, int iAmOpponent) {
    string moveMade;
    bool inValidInput = true;
    bool moveIsIllegal;

    // validates input
    // checks if piece already on board, and bounds check
    while (inValidInput) {
        cout << "\nChoose Opponent's move: " << endl;
        cin >> moveMade;

        moveIsIllegal = checkIfValidMove(moveMade);

        if (moveIsIllegal) {
            INVALID:
            cout << "\n** Illegal move **" << endl;
        } else {
            inValidInput = false;
        }
    }

    // determines if playing as 'X' or 'O'
    if(iGoFirst == 1){
        // opponent goes first
        currPiecesOnBoard.at(checkPieceID(moveMade)) = 'X';
    }else{
        // opponent goes second
        currPiecesOnBoard.at(checkPieceID(moveMade)) = 'O';

    }
    addToMovesArray(moveMade, iGoFirst, iAmOpponent);
    updatePiecesOnBoard();
    printCurrGameBoard();
}

void Game::agentsMove(string moveMade, int iGoFirst, int iAmAgent){

    // determines if playing as 'X' or 'O'
    if(iGoFirst == 0){
        // opponent goes first
        currPiecesOnBoard.at(checkPieceID(moveMade)) = 'X';
    }else{
        // opponent goes second
        currPiecesOnBoard.at(checkPieceID(moveMade)) = 'O';
    }
    addToMovesArray(moveMade, iGoFirst, iAmAgent);
    updatePiecesOnBoard();
    printCurrGameBoard();

}

void Game::addToMovesArray(string moveMade, int iGoFirst, int whoAmI){
    if(whoAmI == 0){
        // i am agent, do i go first?
        if(iGoFirst == 0){
            // agent goes first
            // input move 1st col movesMade array
            string temp;// add '1.' ... to board

            // print 1. ... 32. ; has different formats
            if(gameTurn < 8) {
                temp = "\t  " + to_string(gameTurn + 1) + '.';
                gameBoard[gameTurn + 1][9] = temp;
                gameBoard[gameTurn + 1][10] = "  " + moveMade;
            }
            else if(gameTurn == 8) {
                // print 9. on board
                temp = "\t\t\t  " + to_string(gameTurn + 1) + '.';
                gameBoard[gameTurn + 1][9] = temp;
                gameBoard[gameTurn + 1][10] = "  " + moveMade;
            }else if(gameTurn > 8){
                // print 10. ... 11. on board
                temp = "\t\t\t " + to_string(gameTurn + 1) + '.';
                gameBoard[gameTurn + 1][9] = temp;
                gameBoard[gameTurn + 1][10] = "  " + moveMade;

            }else{
                cout << "DEBUG:i should not be here: add to moves array. " << endl;
            }
        }
        else{
            // agent goes second
            // input move 2nd col movesMade array
            gameBoard[gameTurn+1][11] = "\t  " + moveMade;


        }
    }
    else{
        // i am opponent
        if(iGoFirst == 1){
            // agent goes first
            // input move 1st col movesMade array
            string temp;// add '1.' ... to board

            // print 1. ... 32. ; has different formats
            if(gameTurn < 8) {
                temp = "\t  " + to_string(gameTurn + 1) + '.';
                gameBoard[gameTurn + 1][9] = temp;
                gameBoard[gameTurn + 1][10] = "  " + moveMade;
            }
            else if(gameTurn == 8) {
                // print 9. on board
                temp = "\t\t\t  " + to_string(gameTurn + 1) + '.';
                gameBoard[gameTurn + 1][9] = temp;
                gameBoard[gameTurn + 1][10] = "  " + moveMade;
            }else if(gameTurn > 8){
                // print 10. ... 11. on board
                temp = "\t\t\t " + to_string(gameTurn + 1) + '.';
                gameBoard[gameTurn + 1][9] = temp;
                gameBoard[gameTurn + 1][10] = "  " + moveMade;

            }else{
                cout << "DEBUG:i should not be here: add to moves array. " << endl;
            }
        }
        else{
            // opponent move goes second
            // input move 2nd col movesMade array
            gameBoard[gameTurn+1][11] = "\t  " + moveMade;

        }

    }

}

bool Game::checkIfValidMove(string moveMade) {
    //bool isIllegal = true;
    int locID;

    locID = checkPieceID(moveMade); // return location of string,
    if (locID == -1) {
        return true; // bounds error, not legal
    }

    return currPiecesOnBoard.at(locID) != '-';  // not legal if true,
}

int Game::checkPieceID(string moveMade) {
    int locID;

    // if string no size 2, return false
    if(moveMade.size() != 2){
        return  -1;
    }

    if (moveMade.at(0) == 'a') {
        if (moveMade.at(1) == '1') {
            return 0;
        } else if (moveMade.at(1) == '2') {
            return 1;
        } else if (moveMade.at(1) == '3') {
            return 2;
        } else if (moveMade.at(1) == '4') {
            return 3;
        } else if (moveMade.at(1) == '5') {
            return 4;
        } else if (moveMade.at(1) == '6') {
            return 5;
        } else if (moveMade.at(1) == '7') {
            return 6;
        } else if (moveMade.at(1) == '8') {
            return 7;
        } else {
            return -1;
        }
    } else if (moveMade.at(0) == 'b') {
        if (moveMade.at(1) == '1') {
            return 8;
        } else if (moveMade.at(1) == '2') {
            return 9;
        } else if (moveMade.at(1) == '3') {
            return 10;
        } else if (moveMade.at(1) == '4') {
            return 11;
        } else if (moveMade.at(1) == '5') {
            return 12;
        } else if (moveMade.at(1) == '6') {
            return 13;
        } else if (moveMade.at(1) == '7') {
            return 14;
        } else if (moveMade.at(1) == '8') {
            return 15;
        } else {
            return -1;
        }


    } else if (moveMade.at(0) == 'c') {
        if (moveMade.at(1) == '1') {
            return 16;
        } else if (moveMade.at(1) == '2') {
            return 17;
        } else if (moveMade.at(1) == '3') {
            return 18;
        } else if (moveMade.at(1) == '4') {
            return 19;
        } else if (moveMade.at(1) == '5') {
            return 20;
        } else if (moveMade.at(1) == '6') {
            return 21;
        } else if (moveMade.at(1) == '7') {
            return 22;
        } else if (moveMade.at(1) == '8') {
            return 23;
        } else {
            return -1;
        }

    } else if (moveMade.at(0) == 'd') {
        if (moveMade.at(1) == '1') {
            return 24;
        } else if (moveMade.at(1) == '2') {
            return 25;
        } else if (moveMade.at(1) == '3') {
            return 26;
        } else if (moveMade.at(1) == '4') {
            return 27;
        } else if (moveMade.at(1) == '5') {
            return 28;
        } else if (moveMade.at(1) == '6') {
            return 29;
        } else if (moveMade.at(1) == '7') {
            return 30;
        } else if (moveMade.at(1) == '8') {
            return 31;
        } else {
            return -1;
        }
    } else if (moveMade.at(0) == 'e') {
        if (moveMade.at(1) == '1') {
            return 32;
        } else if (moveMade.at(1) == '2') {
            return 33;
        } else if (moveMade.at(1) == '3') {
            return 34;
        } else if (moveMade.at(1) == '4') {
            return 35;
        } else if (moveMade.at(1) == '5') {
            return 36;
        } else if (moveMade.at(1) == '6') {
            return 37;
        } else if (moveMade.at(1) == '7') {
            return 38;
        } else if (moveMade.at(1) == '8') {
            return 39;
        } else {
            return -1;
        }

    } else if (moveMade.at(0) == 'f') {
        if (moveMade.at(1) == '1') {
            return 40;
        } else if (moveMade.at(1) == '2') {
            return 41;
        } else if (moveMade.at(1) == '3') {
            return 42;
        } else if (moveMade.at(1) == '4') {
            return 43;
        } else if (moveMade.at(1) == '5') {
            return 44;
        } else if (moveMade.at(1) == '6') {
            return 45;
        } else if (moveMade.at(1) == '7') {
            return 46;
        } else if (moveMade.at(1) == '8') {
            return 47;
        } else {
            return -1;
        }
    } else if (moveMade.at(0) == 'g') {
        if (moveMade.at(1) == '1') {
            return 48;
        } else if (moveMade.at(1) == '2') {
            return 49;
        } else if (moveMade.at(1) == '3') {
            return 50;
        } else if (moveMade.at(1) == '4') {
            return 51;
        } else if (moveMade.at(1) == '5') {
            return 52;
        } else if (moveMade.at(1) == '6') {
            return 53;
        } else if (moveMade.at(1) == '7') {
            return 54;
        } else if (moveMade.at(1) == '8') {
            return 55;
        } else {
            return -1;
        }
    } else if (moveMade.at(0) == 'h') {
        if (moveMade.at(1) == '1') {
            return 56;
        } else if (moveMade.at(1) == '2') {
            return 57;
        } else if (moveMade.at(1) == '3') {
            return 58;
        } else if (moveMade.at(1) == '4') {
            return 59;
        } else if (moveMade.at(1) == '5') {
            return 60;
        } else if (moveMade.at(1) == '6') {
            return 61;
        } else if (moveMade.at(1) == '7') {
            return 62;
        } else if (moveMade.at(1) == '8') {
            return 63;
        } else {
            return -1;
        }
    } else {
        cout << "DEBUG ERROR" << endl;
        return -1;

    }
}
