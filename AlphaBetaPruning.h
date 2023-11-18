#include <iostream>

#ifndef UNTITLED2_ALPHABETAPRUNINGSEARCH_H
#define UNTITLED2_ALPHABETAPRUNINGSEARCH_H

using namespace std;

class AlphaBetaPruning {

public:
    int depth = 5;
    int goingDown = 0;
    int whoAmI; // 0 = 'X'; 1 = '0'
    int bestMoveIndexSoFar;
    int bestEval;

    string alphaBetaSearch(string);
    int maxValue(string, int, int);
    int minValue(string, int, int);
    string getBestMove();
    bool isAtTerminal(string);
    int getHeuristic(string);
    bool clockExpired();
};


#endif //UNTITLED2_ALPHABETAPRUNINGSEARCH_H
