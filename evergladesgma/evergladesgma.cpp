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
#include <Random>
#include <iomanip>
#include <string>
using namespace std;

//Function Prototypes

void showBoard(int[][5]);
void showRules();
int validMenuOption(int);

int main()
{
    const int ROWS = 5, COLS = 5;
    int board[ROWS][COLS];
    bool playing = true;
    int menu_option;

    do {

        cout << "Lost in the Everglades ..." << endl << endl;
        cout << "Let's play! Pick a menu option";
        cin >> menu_option;

        switch (menu_option) {
        case 1:
            showRules();
            break;
        case 2:
            break;


        case 3:
            break;
        default:
            cout << "Invalid menu option.";
        }
    } while (menu_option != 3);

    }

void showRules()
{
    cout << "Please read the rules below." << endl << endl;
    cout << "1. Player begins with 12 gongs of time; Game ends once gongs reaches 0."
        << endl << "2. Ranger must move one cell at a time; Loses a gong per turn unless danger encountered." 
        << endl << "3. If encountering danger, ranger must: Wait or Fight." 
        << endl << "4. If Ranger waits: Moves to desired cell, loses 5 gongs of time, danger remains in cell."
        << endl << "5. If Ranger fights and wins: Moves to desired cell, loses 2 gongs of time."
        << endl << "6. If Ranger fights and loses: Goes back to initial cell, loses 3 gongs of time." << endl << endl;
}
