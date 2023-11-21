#include <iostream>
#include <string>
using namespace std;

int main()
{
    const int rows = 5, cols = 5;
    char board[rows][cols];
    bool playing = true;
    int Rx = 0, Ry = 0;

    do
    {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                board[i][j] = '*';
                board[Rx][Ry] = 'R';
                board[4][4] = 'T';
            }
        }

        cout << "     0   1   2   3   4" << endl;
        for (int i = 0; i < 5; i++) {
            cout << i << " ";
            if (i < 5) {
                cout << " | ";
            }
            for (int j = 0; j < 5; j++) {
                cout << board[i][j];
                if (j < 5) {
                    cout << " | ";
                }
            }
            cout << '\n';
        }

        cout << "enter next cell (row & col): ";
        cin >> Rx >> Ry;
        cout << endl << endl;

        if ((Rx < 0 || Rx > 4) || (Ry > 4 || Ry < 0)) {
            cout << "Bad ... Try again" << endl;
            cout << "enter next cell (row & col): ";
            cin >> Rx >> Ry;
        }
        else {
            board[Rx][Ry] = 'R';
        }


    } while (true);

    return 0;

}