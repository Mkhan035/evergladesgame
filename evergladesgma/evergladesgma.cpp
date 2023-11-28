/*
Algorithm:
Step 1: Show user menu options. (See rules, play game, quit)
Step 2: User chooses 1 to show rules, 2 to play game, and 3 to quit game. If player selects 2, proceed to s3
Step 3: Show board, gongs left, Cell movement options, remove asterisk from previous cell placement
    a. Validate input; ensure it exists and was not already done before
Step 4: When player makes move, check to see if there's a Danger laced inside cell. if so, prompt them
to fight or wait. Decrement gongs accordingly
Step 5: Repeat steps 3-5 until gongs reach 0
Step 6: Tell user if they won or lost
Step 7: Ask if player wants to play again. Restart/stop game accordingly

*/

/*
Rules
We start with 12 gongs, game continues until we reach 0 gongs
Ranger progresses, one cell at a time, losing one gong, until Danger encountered. If that happens,
Ranger must pick one move: wait or fight.
fight has two possible outcomes:

    If the Ranger fights and wins
    Moves to the desired cell
    Loses 2 gongs of time

    If the Ranger fights and loses
    Goes back to the initial cell
    Loses 3 gongs of time

Wait has one outcome:
    If the Ranger waits
    Moves to the desired cell
    Loses 5 gongs of time
    The danger remains in the cell


Game ends with either ranger rescuing tourists or fate of tourists unknown
*/

/*
Mechanics of board

5x5 table (two dimensional array)
May not go onto any previous positions (remove asterisk to show vacant positions)
Randomly assign board coordinates with Dangers
Ranger starts at top left; Tourists bottom right
Ranger moves first; Options after
*/


// random ints, iomanip, 3 function prototypes
#include <iostream>
#include <string>
#include <random>
using namespace std;
int randomNum(int, int);
void showBoard(string[][5]);
string dangerIdentified(string[][5], int&, bool&);
int main()
{
    string displayBoard[5][5];
    const int rows = 5, cols = 5;
    string board[5][5] = {
        {"R", "D", "S", "S", "D"},
        {"D","S", "S", "S", "D"},
        {"S", "D", "S", "S", "D"},
        {"S","D", "S", "D", "S"},
        {"S","D","S","D","T"}
    };
    bool playing = true;
    int Rx = 0, Ry = 0;
    int initial_x = 0, initial_y = 0;
    bool advance = true;
    int gongs = 12;
    int menu_option;



    do {

        cout << "\nLost in the Everglades ..." << endl << endl;
        cout << "\nLet's play! Pick a menu option: ";
        cin >> menu_option;

        switch (menu_option) {
        case 1:

            break;
        case 2:
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    displayBoard[i][j] = '*';
                    displayBoard[Rx][Ry] = 'R';
                    displayBoard[4][4] = 'T';

                }
            }
            while (gongs > 0) {
                showBoard(displayBoard);
                cout << "Enter next cell (row & col): ";
                cin >> Rx >> Ry;
                cout << endl << endl;

                while (Rx < 0 || Rx > 4 || Ry > 4 || Ry < 0) {
                    cout << "Bad ... Try again" << endl;
                    cout << "enter next cell (row & col): ";
                    cin >> Rx >> Ry;

                }


                while (Rx > initial_x + 1 || Ry > initial_y + 1 || Rx == initial_x || Ry == initial_y - 1)
                {
                    cout << "bad";
                    cout << "STOP CHEATING!!! Re-enter next cell (row & col): ";
                    cin >> Rx >> Ry;
                }

                if (board[Rx][Ry] == "D") {
                    cout << "\nChecking for danger ...";
                    displayBoard[Rx][Ry] = board[Rx][Ry] = dangerIdentified(board, gongs, advance);
                    if (advance == true) {
                        cout << "\nAdvance is true";

                        displayBoard[initial_x][initial_y] = " ";
                        board[initial_x][initial_y] = "O";
                        initial_x = Rx; initial_y = Ry;
                        displayBoard[Rx][Ry] = "R";
                    }
                    else {
                        displayBoard[initial_x][initial_y] = "R";
                    }
                }
                else {
                    displayBoard[initial_x][initial_y] = " ";
                    board[initial_x][initial_y] = "O";
                    initial_x = Rx; initial_y = Ry;
                    displayBoard[Rx][Ry] = "R";
                    gongs -= 1;
                }
                cout << "\nGongs left: " << gongs << endl;
            }
            break;
        case 3:
            cout << "\nBye bye!";
            playing = false;
            break;
        default:
            cout << "Invalid menu option.";
        }
    } while (playing == true);
    return 0;
}

int randomNum(int x, int y) {
    int value;
    random_device myEngine;
    uniform_int_distribution<int>randomInt(x, y);
    value = randomInt(myEngine);
    return value;
}
string dangerIdentified(string board[][5], int& gongs, bool& advance) {
    string possibleDangers[4] = { "Famished Alligator", "Swarm of Mosquitos", "Venomous Spider", "Python" };
    string symbolBoard[4] = { "A", "M", "S", "P" };
    string board_mark = "N";
    int rDanger, choice, winOrLose;
    rDanger = randomNum(0, 3);
    board_mark = symbolBoard[rDanger];
    cout << "\nBegin danger execution";
    cout << "\nUh oh, you've encountered a " << possibleDangers[rDanger] << "!";
    cout << "\nChoose your next move: " << endl;
    cout << "\t1. Wait until it leaves" << endl;
    cout << "\t2. Fight it" << endl;
    cout << "\nMove: ";
    cin >> choice;

    while (choice < 1 || choice >2) {
        cout << "\nPick option 1 or two---there are no alternatives";
        cout << "\nMove: ";
        cin >> choice;
    }
    if (choice == 1) {
        cout << "\n--->" << possibleDangers[rDanger] << " is gone! You advance!";
        gongs -= 5;
    }
    if (choice == 2) {
        winOrLose = randomNum(0, 1);
        if (winOrLose == 0) {
            cout << "\n--->You fight the " << possibleDangers[rDanger] << " and win! Go forth!";
            gongs -= 2;
            advance = true;
        }
        if (winOrLose == 1) {
            cout << "\n--->Uh oh, you lost! Retreat!";
            gongs -= 3;
            advance = false;
        }

    }
    return board_mark;
}
void showBoard(string displayBoard[5][5]) {
    cout << "     0   1   2   3   4" << endl;
    for (int i = 0; i < 5; i++) {
        cout << i << " ";
        if (i < 5) {
            cout << " | ";
        }
        for (int j = 0; j < 5; j++) {
            cout << displayBoard[i][j];
            if (j < 5) {
                cout << " | ";
            }
        }
        cout << '\n';
    }
}
