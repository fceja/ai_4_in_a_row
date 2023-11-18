#include "AlphaBetaPruning.h"

string AlphaBetaPruning::alphaBetaSearch(string currGameBoard){
    int infinity = 1000;
    int negInfinity = -1000;

    maxValue(currGameBoard, negInfinity, infinity);

    return getBestMove();
}

int AlphaBetaPruning::maxValue(string childGameBoard, int alpha, int beta){

    if(depth == 0 || isAtTerminal(childGameBoard)){
        depth++;
        goingDown++;
        return getHeuristic(childGameBoard); /*reached terminal, add heuristic*/
    }
    int maxValue = -1000;

    for(int i = 0; i < 64; i++){
        if(childGameBoard.at(i) != '-'){ // position on board already occupied
            continue;
        }
        else{
            if(whoAmI == 0){
                // agent is 'X'
                childGameBoard.at(i) = 'X';
            }else{
                // agent is 'O'
                childGameBoard.at(i) = 'O';
            }
        }
        depth--;
        goingDown--;
        maxValue = max(maxValue, minValue(childGameBoard, alpha, beta));// currGameBoard with new position

        if(maxValue >= beta){
            depth++;
            goingDown++;
            return maxValue; /*bestIndex*/
        }

        if(maxValue > alpha){
            bestMoveIndexSoFar = i;
            bestEval = maxValue;

        }
        alpha = max(alpha, maxValue);
    }
    depth++;
    goingDown++;

    return maxValue;
}

int AlphaBetaPruning::minValue(string childGameBoard, int alpha, int beta){

    if(depth == 0 || isAtTerminal(childGameBoard)){
        depth ++;
        goingDown++;
        return getHeuristic(childGameBoard) ; /*reached terminal, add heuristic*/
    }

    int minValue = 1000;

    for(int i = 0; i < 64; i++){
        if(childGameBoard.at(i) != '-'){
            continue;
        } else{
            if(whoAmI == 0){
                // agent plays as opponent, 'O'
                childGameBoard.at(i) = 'O';
            }else{
                // agent plays as opponent, 'X'
                childGameBoard.at(i) = 'X';
            }
        }
        depth--;
        goingDown--;
        minValue = min(minValue, maxValue(childGameBoard, alpha, beta));
        if(minValue <= alpha){
            return minValue;
        }
        beta = min(beta, minValue);
    }
    depth++;
    goingDown++;
    return minValue;
}

string AlphaBetaPruning::getBestMove() {
    switch(bestMoveIndexSoFar){
        case 0: return "a1";
        case 1: return "a2";
        case 2: return "a3";
        case 3: return "a4";
        case 4: return "a5";
        case 5: return "a6";
        case 6: return "a7";
        case 7: return "a8";
        case 8: return "b1";
        case 9: return "b2";
        case 10: return "b3";
        case 11: return "b4";
        case 12: return "b5";
        case 13: return "b6";
        case 14: return "b7";
        case 15: return "b8";
        case 16: return "c1";
        case 17: return "c2";
        case 18: return "c3";
        case 19: return "c4";
        case 20: return "c5";
        case 21: return "c6";
        case 22: return "c7";
        case 23: return "c8";
        case 24: return "d1";
        case 25: return "d2";
        case 26: return "d3";
        case 27: return "d4";
        case 28: return "d5";
        case 29: return "d6";
        case 30: return "d7";
        case 31: return "d8";
        case 32: return "e1";
        case 33: return "e2";
        case 34: return "e3";
        case 35: return "e4";
        case 36: return "e5";
        case 37: return "e6";
        case 38: return "e7";
        case 39: return "e8";
        case 40: return "f1";
        case 41: return "f2";
        case 42: return "f3";
        case 43: return "f4";
        case 44: return "f5";
        case 45: return "f6";
        case 46: return "f7";
        case 47: return "f8";
        case 48: return "g1";
        case 49: return "g2";
        case 50: return "g3";
        case 51: return "g4";
        case 52: return "g5";
        case 53: return "g6";
        case 54: return "g7";
        case 55: return "g8";
        case 56: return "h1";
        case 57: return "h2";
        case 58: return "h3";
        case 59: return "h4";
        case 60: return "h5";
        case 61: return "h6";
        case 62: return "h7";
        case 63: return "h8";
        default:
            cout << "DEBUG: error in AlphaBetaPruning::getBestMove()." << endl;
            return NULL;
    }
}

int AlphaBetaPruning::getHeuristic(string childGameBoard){

    int myValue = 0;

    for(int i = 0; i < 64; i++){
        if(childGameBoard.at(i) == 'X'){
            myValue = i+1;
        }
    }

    return myValue;
}

bool AlphaBetaPruning::isAtTerminal(string currGameBoard){

    int start = 0;
    int end = 4;
    int lastCol = 8;

    // checks for horizontal 4 in a row
    for(int row = 0; row < 8; row++) {
        for (int i = start; i < end; i++) {
            if ((currGameBoard.at(i) == 'X' && currGameBoard.at(i + 1) == 'X' &&
                    currGameBoard.at(i + 2) == 'X' && currGameBoard.at(i + 3) == 'X') ||
                (currGameBoard.at(i) == 'O' && currGameBoard.at(i + 1) == 'O' &&
                        currGameBoard.at(i + 2) == 'O' && currGameBoard.at(i + 3) == 'O')) {
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
            if ((currGameBoard.at(i) == 'X' && currGameBoard.at(i + 8) == 'X' &&
                    currGameBoard.at(i + 16) == 'X' && currGameBoard.at(i + 24) == 'X') ||
                (currGameBoard.at(i) == 'O' && currGameBoard.at(i + 8) == 'O' &&
                        currGameBoard.at(i + 16) == 'O' && currGameBoard.at(i + 24) == 'O')) {
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

bool AlphaBetaPruning::clockExpired(){
    return false;
}
