#include <iostream>

#include "Game.h"
#include "AlphaBetaPruning.h"

using namespace std;

// global variables
int timeAllowed;

void askUserInput(Game &, int &);

int main() {

    Game game;
    int iGoFirst;// agent = 0->'X', opponent = 1->'O'
    int iAmAgent = 0;
    int iAmOpponent = 1;
    bool gameOver = false;
    string agentsMove;


    // asks user for time allowed and who goes first
    askUserInput(game, iGoFirst);

    // creates initial game board
    game.createInitialPiecesOnBoard(); // all blank '-'
    game.printCurrGameBoard();

    // creates agent object
    AlphaBetaPruning ai;

    ai.whoAmI = 0;// i am agent
    agentsMove = ai.alphaBetaSearch(game.currPiecesOnBoard);

    while(!gameOver){
        if(iGoFirst == 0){ /*agent goes first*/
            agentsMove = ai.alphaBetaSearch(game.currPiecesOnBoard);
            game.agentsMove(agentsMove, iGoFirst, iAmAgent);

            gameOver = game.goalCheck();

            if(gameOver){break;}

            game.askOpponentMove(iGoFirst, iAmOpponent);
            gameOver = game.goalCheck();

            if(gameOver){break;}

            game.gameTurn++;
        }
        else{ /*opponent goes first*/
            game.askOpponentMove(iGoFirst, iAmOpponent);
            gameOver = game.goalCheck();

            if(gameOver){break;}

            game.agentsMove(agentsMove, iGoFirst, iAmAgent);
            gameOver = game.goalCheck();

            if(gameOver){break;}

            game.gameTurn++;
        }
    }
    cout << "\n\tGame over." << endl;



/*Player 1 vs Player two*/  /* no artificial intelligence*/
//    while(!gameOver){
//
//        if(iGoFirst == 0){
//            //agent goes first
//            game.askAgentMove(iGoFirst, iAmAgent);
//            gameOver = game.goalCheck(iGoFirst);
//
//            if(gameOver){break;}
//
//            game.askOpponentMove(iGoFirst, iAmOpponent);
//            gameOver = game.goalCheck(iGoFirst);
//
//            if(gameOver){break;}
//
//            game.gameTurn++;
//
//        }else{
//            //opponent goes first
//            game.askOpponentMove(iGoFirst, iAmOpponent);
//            gameOver = game.goalCheck(iGoFirst);
//
//            if(gameOver){break;}
//
//            game.askAgentMove(iGoFirst, iAmAgent);
//            gameOver = game.goalCheck(iGoFirst);
//
//            if(gameOver){break;}
//
//            game.gameTurn++;
//        }
//    }
//    cout << "\n\tGame over." << endl;

    return 0;
}

void askUserInput(Game &game, int &first) {

    string goesFirst;
    string goesSecond;
    char selection = ' ';
    bool invalidChar = true;

        cout << "\nPlease enter time allowed: \n";
        cin >> timeAllowed;

        while (cin.fail() || timeAllowed <= 0)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n'); // ignore last input
            cout << "\n** Please enter number greater than zero **\n";
            cout << "Please enter time allowed: ";
            cin >> timeAllowed;
            cout << endl << endl;
        }


    while (invalidChar) {
        // asks for who goes first
        cout << "Who goes first?\nEnter 'a' for Agent, 'o' for Opponent.\n\nSelection:\n";
        cin >> selection;
        cout << endl << endl << endl;

        if(selection == 'a' || selection == 'A'|| selection == 'o' || selection == 'O'){
            invalidChar = false;
        }
        else {
            cout << "** Please enter valid character **" << endl;
        }

    }

    if (selection == 'a') {
        first = 0;
        goesFirst = "Agent";
        goesSecond = "Opponent";
    } else if (selection == 'o') {
        first = 1;
        goesFirst = "Opponent";
        goesSecond = "Agent";
    }

    // creates game
    game.createInitialGameBoard(goesFirst, goesSecond);

}


