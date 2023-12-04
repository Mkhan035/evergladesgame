/*
Algorithm:
Step 1: Show user menu options. (See rules, play game, quit)
Step 2: User chooses 1 to show rules, 2 to play game, and 3 to quit game. If player selects 2, proceed to s3
Step 3: Show board and gongs left, then prompt for move.
    a. Validate input; ensure it is within range of the ranger (adjacent to the player)
Step 4: When player makes move, check to see if there's a Danger laced inside cell. if so, prompt them
to fight or wait. Decrement gongs by 2 if they win the fight or by 3 if they lose. If Ranger retreats, decrement by 5.
If there is no danger, decrement gongs by 1.
Step 5. Update board, reflecting player's movement (or lack thereof) and the monster character if the player lost
Step 6: Repeat steps 3-5 until gongs reach 0 or the player reaches the tourists
Step 7: Tell user if they won or lost
Step 8: Re-loop menu until the player chooses 3 to quit
*/

/*
Mechanics of board
5x5 table (two dimensional array)
Move to any adjacent cell, including diagonally and backwards
May go onto any previous positions (remove asterisk to show vacant positions)
Preset Danger positions, but randomly select what danger entity is present
Ranger starts at top left; Tourists bottom right
Ranger moves first; consequences after
*/

#include <iostream>
#include <string>
#include <random>
using namespace std;

//Function prototypes
int menu();
void rules();
int randomNum(int, int);
void showBoard(string[5][5]);
string dangerIdentified(string[][5], int&, bool&);

int main()
{
    string displayBoard[5][5];
    bool playing = true;
    
    bool notValid = true;


    do {
        // R = Ranger, D = Danger, S = Safe, T = Tourists
        string board[5][5] = {
        {"S", "D", "S", "S", "D"},
        {"D","S", "S", "S", "S"},
        {"S", "D", "D", "S", "D"},
        {"S","D", "S", "D", "S"},
        {"S","D","S","D","T"}
        };
        //Position player wants to move to
        int Rx = 0, Ry = 0;

        //Position player is currently at
        int initial_x = 0, initial_y = 0;

        bool advance = true;
        int menu_option, gongs = 12;

        //Will control if the player won the game or not
        int win = 0;

        //Introduce program to player
        cout << "\nLost in the Everglades ..." << endl;
        cout << "\nWelcome to Lost in the Everglades, a game in which you, the Ranger, will traverse the\n"
            << "treacherous terrain of the Everglades to rescue a group of hapless tourists. With only 12\n"
            << "gongs of time, you must reach the tourists quickly, with luck on your side. Your map is\n"
            << "a board, with 'R' marking your location and 'T' marking the tourists. As you heroically\n"
            << "advance, carefully consider the hidden Danger you might expose yourself to . . .\n";
        menu_option = menu();

        switch (menu_option) {
        case 1:
            rules();
            break;

        case 2:
            for (int i = 0; i < 5; ++i)
            {
                for (int j = 0; j < 5; ++j) {
                    displayBoard[i][j] = '*';
                    displayBoard[Rx][Ry] = 'R';
                    displayBoard[4][4] = 'T';

                }
            }

            cout << "\nLet's begin! Remember, you can only move to cells adjacent to the Ranger.";

            while (gongs > 0 && win == 0)
            {
                cout << '\n';
                showBoard(displayBoard);
                cout << "\nGongs left: " << gongs << endl;
                cout << "\nEnter next cell (row & col): ";
                cin >> Rx >> Ry;
              

                do {
                    notValid = false;
                    while (Rx < 0 || Rx > 4 || Ry > 4 || Ry < 0)
                    {
                        notValid = true;
                        cout << "\nYou must stay within the board's boundaries. Try again." << endl;
                        cout << "\nEnter next cell (row & col): ";
                        cin >> Rx >> Ry;
                        
                    }
                    
                    while (Rx > initial_x + 1 || Ry > initial_y + 1 || Rx < initial_x - 1 || Ry < initial_y - 1)
                    {
                        notValid = true;
                        cout << "\nNo jumping! You may only move to the squares adjacent to the Ranger.";
                        cout << "\n\nRe-enter next cell (row & col): ";
                        cin >> Rx >> Ry;
                    }
                } while (notValid == true);
                /* Algorithm: Updating the board
                1. Check if player is moving to danger space; if so, call danger function
                and update the board with its mark. It'll go away if advance is true
                    1a. If the player won the fight/waited, advance will be true. We
                    will update the display board to show the player's previous position as
                    a " " and current one with an "R". On its parallel array (board),
                    update player's initial and current positions to "S" to deactivate danger
                    1b. Update player's initial position to new position

                    1c. If player lost the fight, keep the player's previous position

                2. If player went to safe space, tell player it is safe and update the
                player's previous position on the display board to " " and mark their new one
                with a "R"
                    2a. Update player's initial position to the "R"'s current position
                    2b. Decrement gongs by 1
                */
                //Check for Danger, marked by anything that's not "S" or "T"
                if (board[Rx][Ry] != "S" && board[Rx][Ry] != "T")
                {
                    displayBoard[Rx][Ry] = board[Rx][Ry] = dangerIdentified(board, gongs, advance);

                    if (advance == true)
                    {
                        displayBoard[initial_x][initial_y] = " ";
                        board[initial_x][initial_y] = "S";
                        board[Rx][Ry] = "S";
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
                    cout << "\nCell (" << Rx << "," << Ry << ") is free... You advance!";
                    displayBoard[initial_x][initial_y] = " ";
                    initial_x = Rx; initial_y = Ry;
                    displayBoard[Rx][Ry] = "R";
                    gongs -= 1;
                }

                //We'll lazily get around scope and update win's memory location instead
                //0 = false, 1 = true
                if (board[Rx][Ry] == "T")
                    win++;
            }

            /*
            Algorithm: winning
            1. Check if win ever incremented to 1.
                1a. If so, the player won; display heartfelt congratulations
                1b. If not, offer the player condolences
            */
            if (win == 1)
                cout << "\nCongrats! You win, with " << gongs << " gongs remaining!" << endl;
            else
                cout << "\nYou ran out of gongs! Better luck next time!" << endl;
            break;

        case 3:
            cout << "\nAw, we're sad to see you go! But, farewell!";
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
    cout << "\nPick a menu option to learn more, begin, or leave.";
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
        << "\n2. You may only move to squares ADJACENT to the Ranger, and only 1 cell at a time."
        << "\nThis includes going backwards and diagonally. You will lose only 1 gong per turn"
        << "\nunless the Ranger encounters a Danger."
        << "\n3. If the Ranger finds a Danger, you will have TWO options: WAIT or FIGHT."
        << "\n\t4. If you WAIT, you will lose 5 gongs of time and advance forward."
        << "\n\t5. If you FIGHT and WIN, you will advance forth and lose only 2 gongs"
        << "\n\tof time."
        << "\n\t6. If you FIGHT and LOSE, you will retreat and lose 3 gongs of time."
        << "\n\tThe cell will still harbor a Danger, so if you try moving to the cell,"
        << "\n\tyou will encounter a Danger, though it may be different entity.\n\n";
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
it as a subscript in the possibleDangers || array
2. Store the mark corresponding to the Danger inside a string var "board_mark"
3. Tell the player what Danger is present, followed by their two options (Wait or Fight)
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
        cout << "\n--->" << possibleDangers[rDanger] << " is gone! You advance!" << endl;
        gongs -= 5;
        advance = true;
    }
    //If the player chooses 2 and fights, we will use a random number to determine
    //if they win or lose
    if (choice == 2) {
        //1 = win, 0 = lose
        winOrLose = randomNum(0, 1);
        //If they win, decrement gongs by 2 and set advance to true
        if (winOrLose == 1) {
            cout << "\n--->You fight the " << possibleDangers[rDanger] << " and win! Go forth!" << endl;
            gongs -= 2;
            advance = true;
        }
        //If they lose, decrement gongs by 3 and set advance to false
        if (winOrLose == 0) {
            cout << "\n--->Uh oh, you lost! Retreat!" << endl;
            gongs -= 3;
            advance = false;
        }

    }
    return board_mark;
}
