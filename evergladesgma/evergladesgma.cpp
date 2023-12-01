/*
Algorithm:
Step 1: Show user menu options. (See rules, play game, quit)
Step 2: User chooses 1 to show rules, 2 to play game, and 3 to quit game. If player selects 2, proceed to s3
Step 3: Show board, gongs left, Cell movement options, remove asterisk from previous cell placement
    a. Validate input; ensure it is within range of the ranger (adjacent to the player, but cannot go backwards in any way)
Step 4: When player makes move, check to see if there's a Danger laced inside cell. if so, prompt them
to fight or wait. Decrement gongs by 2 if they win the fight or by 3 if they lose. If Ranger retreats, decrement by 5.
Step 5: Repeat steps 3-5 until gongs reach 0 or the player reaches the tourists
Step 6: Tell user if they won or lost
Step 7: Re-loop menu until the player chooses 3 to quit

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
int menu();
void rules();
int randomNum(int, int);
void showBoard(string[][5]);
string dangerIdentified(string[][5], int&, bool&);
int main()
{
    string displayBoard[5][5];
    cout << "\nLost in the Everglades ..." << endl << endl;
    cout << "Welcome to our game! You will play as a Ranger in the Everglades trying to rescue a group\n" <<
        "of tourists! Along the way, you will encounter Dangers that you must deal with to move forward. Good luck.";
    bool playing = true;
    do {
        string board[5][5] = {
        {"R", "D", "S", "S", "D"},
        {"D","S", "S", "S", "S"},
        {"S", "D", "D", "S", "D"},
        {"S","D", "S", "D", "S"},
        {"S","D","S","D","T"}
    };
        int Rx = 0, Ry = 0;
        int initial_x = 0, initial_y = 0;
        bool advance = true;
        int gongs = 12;
        int menu_option;
        int win = 0;
        

       
        menu_option = menu();
        

        switch (menu_option) {
        case 1:
            rules();
            break;
        case 2:
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    displayBoard[i][j] = '*';
                    displayBoard[Rx][Ry] = 'R';
                    displayBoard[4][4] = 'T';

                }
            }
            cout << "\nLet's begin! Remember, you can only move to cells adjacent to the Ranger.\n";
            while (gongs > 0 && win == 0) 
            {
                showBoard(displayBoard);
                cout << "Enter next cell (row & col): ";
                cin >> Rx >> Ry;
                cout << endl << endl;

                while (Rx < 0 || Rx > 4 || Ry > 4 || Ry < 0) 
                {
                    cout << "Bad ... Try again" << endl;
                    cout << "enter next cell (row & col): ";
                    cin >> Rx >> Ry;

                }


                while (Rx > initial_x + 1 || Ry > initial_y + 1 || Rx < initial_x - 1 || Ry < initial_y - 1)
                {
                    cout << "\nNo jumping! You may only move to the squares adjacent to the Ranger.";
                    cout << "\nRe-enter next cell (row & col): ";
                    cin >> Rx >> Ry;
                }

                if (board[Rx][Ry] != "S" && board[Rx][Ry] != "T") 
                {
                    
                    displayBoard[Rx][Ry] = board[Rx][Ry] = dangerIdentified(board, gongs, advance);
                    if (advance == true) 
                    {
                        displayBoard[initial_x][initial_y] = " ";
                        board[initial_x][initial_y] = "S";
                        initial_x = Rx; initial_y = Ry;
                        displayBoard[Rx][Ry] = "R";
                    }
                    else 
                    {
                        displayBoard[initial_x][initial_y] = "R";
                    }
                }
                else 
                {
                    displayBoard[initial_x][initial_y] = " ";
                    board[initial_x][initial_y] = "S";
                    initial_x = Rx; initial_y = Ry;
                    displayBoard[Rx][Ry] = "R";
                    gongs -= 1;
                }

                if (board[Rx][Ry] == "T")
                    win++;
                cout << "\nGongs left: " << gongs << endl;
            }
            
            if (win == 1)
                cout << "\nCongrats! You win, with " << gongs << " gongs left!";
            else
                cout << "\nYou ran out of gongs! Better luck next time!";
           
                
            break;
        case 3:
            cout << "\nBye bye!";
            playing = false;
            break;
        default:
            cout << "\nInvalid menu option. Try again";
        }
    } while (playing == true);
    return 0;
}
int menu() {
    int choice;
    cout << "\n1)\tSee rules\n2)\tPlay game\n3)\tQuit\n";
    cout << "\nChoice: ";
    cin >> choice;
    if (cin.fail()) {
        choice = 4;
    }
    return choice;
}

void rules() {
    cout << "\nPlease read the rules below.\n\n";
    cout << "1. You begin with 12 gongs of time; the game ends once you run out of gongs."
        << "\n2. You may only move to squares adjacent to the Ranger, and only one cell at a time."
        << "\nYou may even go backwards, though we do not recommend it. You will lose only"
        << "\none gong per turn unless the Ranger encounters a Danger."
        << "\n3. If the Ranger finds a Danger, you will have two options: Wait or Fight."
        << "\n\t4. If you WAIT, you will lose 5 gongs of time and advance forward. The cell will" 
        << "\n\tstill harbor a Danger, but it may be a different entity."
        << "\n\t5. If you FIGHT and WIN, you will advance forth and lose only 2 gongs of time."
        << "\n6. If you FIGHT and LOSE, you will have to retreat and lose 3 gongs of time." 
        << "\nKeep in mind that the cell will still have a Danger, so if you go back to the cell," 
        << "\you will encounter a Danger, though it may be different entity.\n\n";
}
//Random number generator
int randomNum(int x, int y) {
    int value;
    random_device myEngine;
    uniform_int_distribution<int>randomInt(x, y);
    value = randomInt(myEngine);
    return value;
}
/*
Mehreen's Algorithm: Handling Dangers
Condition: Check if the player's next move has a Danger; if so, the following function will
be called.
1. Randomly select what danger will be encountered using a number generator (range: 0-3) and using
it as a subscript in the possibleDangers array
2. Store the mark corresponding to the Danger inside a string var "board_mark"
3. Tell the player what Danger is present, followed by their two options (Wait or FIght)
    3a. Validate input, making sure they typed either 1 or 2
4. If they input 1, decrement ref var gongs by 5 and allow the player to advance (advance = true)
5. If they input 2, generate a random number (range: 0-1) to determine if they win or lose
    5a. If it's 1, the player won---decrement gongs by 2 and set advance to true
    5b. If it's 0, the player lost---decrement gongs by 3 and set advance to false
6. Return the board mark in case the player waited or lost so the board will reflect that
*/
string dangerIdentified(string board[][5], int& gongs, bool& advance) {
    //Declare dangers and their parallel marks
    string possibleDangers[4] = { "Famished Alligator", "Swarm of Mosquitos", "Venomous Spider", "Python" };
    string symbolBoard[4] = { "A", "M", "V", "P" };

    //Variable to be returned: the board symbol
    string board_mark;
    float choice;
    int rDanger, winOrLose;

    //Determine danger randomly
    rDanger = randomNum(0, 3);

    //Update board mark
    board_mark = symbolBoard[rDanger];

    //Tell player they've encountered a Danger and give them their options
    cout << "\nUh oh, you've encountered a " << possibleDangers[rDanger] << "!";
    cout << "\nChoose your next move: " << endl;
    cout << "\t1. Wait until it leaves" << endl;
    cout << "\t2. Fight it" << endl;
    cout << "\nMove: ";
    cin >> choice;

    //Ensure input is 1 or 2
    while (choice != 1 && choice != 2) {
        cout << "\nPick option 1 or 2---there are no alternatives";
        cout << "\nMove: ";
        cin >> choice;
    }
    //If the player chooses 1 and waits, decrement gongs by 5 and set advance to true
    if (choice == 1) {
        cout << "\n--->" << possibleDangers[rDanger] << " is gone! You advance!";
        gongs -= 5;
        advance = true;
    }
    //If the player chooses 2 and fights, we will see if they win or lose
    if (choice == 2) {
        //1 = win, 0 = lose
        winOrLose = randomNum(0, 1);
        //If they win, decrement gongs by 2 and set advance to true
        if (winOrLose == 1) {
            cout << "\n--->You fight the " << possibleDangers[rDanger] << " and win! Go forth!";
            gongs -= 2;
            advance = true;
        }
        //If they lose, decrement gongs by 3 and set advance to false
        if (winOrLose == 0) {
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
