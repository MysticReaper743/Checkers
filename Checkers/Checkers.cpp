#include <iostream>
#include <string>
#include <cmath>

using namespace std;

void Board();
void GameStart();
void Game(char X_or_O);
int ValidLetterNotation(char inputToCheck);
int ValidNumberNotation(int inputToCheck);
bool legalMove(int fromColumn, int fromRow, int toColumn, int toRow, char X_or_O);
void win(char winner);


bool game_end = false;

char x_o_Entries[8][8] = {
    {' ', 'O', ' ', 'O', ' ', 'O', ' ', 'O'},
    {'O', ' ', 'O', ' ', 'O', ' ', 'O', ' '},
    {' ', 'O', ' ', 'O', ' ', 'O', ' ', 'O'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'X', ' ', 'X', ' ', 'X', ' ', 'X', ' '},
    {' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X', ' ', 'X', ' '}
};

/*
 char x_o_Entries[8][8] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', 'O', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'X', ' ', 'X', ' ', 'X', ' ', 'X', ' '},
    {' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X', ' ', 'X', ' '}
};
*/


int main()
{
    GameStart();
}

void Board()
{ 
    for(int i = 0; i < 8; i++)
    {
        puts("\n   +---+---+---+---+---+---+---+---+");
        printf(" %d | %c | %c | %c | %c | %c | %c | %c | %c | ", i+1, x_o_Entries[i][0], x_o_Entries[i][1], x_o_Entries[i][2], x_o_Entries[i][3], x_o_Entries[i][4], x_o_Entries[i][5], x_o_Entries[i][6], x_o_Entries[i][7]);
    }
        puts("\n   +---+---+---+---+---+---+---+---+");
        puts("     A   B   C   D   E   F   G   H");
}
void GameStart()
{
    puts("Welcome to my checkers game!!!");

    while(true) {

        int choice  = 0;

        puts("\nWould you like to:");
        puts("Start the Game (1)");
        puts("Review the Rules (2)");
        fputs("Exit (3):", stdout);

        scanf_s("%d", &choice);

        if (choice == 1) {
            while(!game_end) {

                char startingColor;

                cin.clear();
                cin.ignore(1000, '\n');

                fputs("\nWhich color would you like to start with? (X or O):", stdout);

                scanf_s("%c", &startingColor);
                //startingColor = toupper(startingColor);
                startingColor = char(::toupper((unsigned char)startingColor));

                if (startingColor == 'X' || startingColor == 'O'){
                    while(!game_end) {
                        Game(startingColor);
                        startingColor = startingColor == 'X' ? 'O': 'X';
                    }
                }
                else puts("Not a valid input. Try again:");
            }
        } else if (choice == 2) {
            puts("\nThe Rules are as followed:\n"
                 "Unless kinged, each piece must move to the other side of the board while moving diagonally.\n"
                 "You may diagonally jump over another opponent and capture their piece.\n"
                 "To king a piece it must cross to the end of the board\n"
                 "When a piece is kinged it may move backwards as well as forwards in a diagonal fashion.\n"
                 "The Objective of the game is to capture all of the opponents pieces.");
            Board();
            puts("\nTo move a piece on the board you must first select the piece you wish to move.\n"
            "To do this you must type the coordinate of the piece you wish to move\nby typing the letter followed by the number associated with its Column and Row.\n"
            "Next you must select an empty space to move the piece to by using the same coordinate system.\n"
            "Have Fun and Enjoy! :D");
        } else if (choice == 3) break;
        else puts("\nNot a valid input. Try again:");

        cin.clear();
        cin.ignore(1000, '\n');
    }
}
void Game(char X_or_O){
    returnToPieceSelection:
    bool validInput = false;

    char kingPiece = X_or_O == 'X' ? '#' : '@';

    while(!validInput) {
        int fromRow, fromColumn, toColumn, toRow;

        char uFromColumn, uToColumn;
        int uFromRow, uToRow;


        Board();

        printf("It is %c's turn.\n", X_or_O);

        while (!validInput) {
            cin.clear();
            cin.ignore(1000, '\n');

            fputs("Which piece would you like to move?:", stdout);
            scanf_s("%c%d", &uFromColumn, 1, &uFromRow);

            fromRow = ValidNumberNotation(uFromRow);
            fromColumn = ValidLetterNotation(uFromColumn);

            (fromColumn == -1 || fromRow == -1 || (x_o_Entries[fromRow][fromColumn] != X_or_O && x_o_Entries[fromRow][fromColumn] != kingPiece))  ? puts("Incorrect input type or illegal move.") : validInput = true;
        }

        validInput = false;
        printf("You chose %c%d.\n", uFromColumn, uFromRow);

        while (!validInput) {
            cin.clear();
            cin.ignore(1000, '\n');

            fputs("What square would you like to move to?(Type X0 to reselect the piece you want to move):", stdout);
            scanf_s("%c%d", &uToColumn, 1, &uToRow);

            if (toupper(uToColumn) == 'X' && uToRow == 0) goto returnToPieceSelection;

            toRow = ValidNumberNotation(uToRow);
            toColumn = ValidLetterNotation(uToColumn);

            (toColumn == -1 || toRow == -1 || x_o_Entries[toRow][toColumn] != ' ') ? puts("\nIncorrect input type or illegal move.") : validInput = true;
        }
            validInput = false;
        if(legalMove(fromColumn, fromRow, toColumn, toRow, x_o_Entries[fromRow][fromColumn])) {
            x_o_Entries[toRow][toColumn] = (X_or_O == 'O' && toRow == 7) || (X_or_O == 'X' && toRow == 0) ? kingPiece : x_o_Entries[fromRow][fromColumn];
            x_o_Entries[fromRow][fromColumn] = ' ';
            validInput = true;

            bool xFound = false, oFound = false;
            for(int i = 0; i < 7 && !(xFound && oFound); i++){
                for(int j = 0; j < 7 && !(xFound && oFound); j++){
                    if(x_o_Entries[i][j] != ' ') {
                        if (x_o_Entries[i][j] == 'X' || x_o_Entries[i][j] == '#') xFound = true;
                        else if (x_o_Entries[i][j] == 'O' || x_o_Entries[i][j] == '@') oFound = true;
                    }
                }
            }
            if(!(xFound && oFound)) win(xFound ? 'X' : 'O');
        }else puts("\nillegal move detected. Try again:");
    }
}
bool legalMove(int fromColumn, int fromRow, int toColumn, int toRow, char X_or_O){

    if(abs(fromColumn - toColumn) == 1) {
        if ((X_or_O == 'X' && fromRow - 1 == toRow) || (X_or_O == 'O' && fromRow + 1 == toRow)) return true;
        else if ((X_or_O == '#' || X_or_O == '@') && abs(fromRow - toRow) == 1) return true;
    }

    char pieceCaptured = x_o_Entries[(fromRow + toRow) / 2][(fromColumn + toColumn) / 2];

    if(abs(fromColumn - toColumn) == 2) {
        if (((X_or_O == 'X' && fromRow - 2 == toRow) || (X_or_O == '#' && abs(fromRow - toRow) == 2) && (pieceCaptured == 'O' || pieceCaptured == '@')) ||
            ((X_or_O == 'O' && fromRow + 2 == toRow) || (X_or_O == '@' && abs(fromRow - toRow) == 2) && (pieceCaptured == 'X' || pieceCaptured == '#'))) {
                x_o_Entries[(fromRow + toRow) / 2][(fromColumn + toColumn) / 2] = ' ';
                return true;
        }
    }
    return false;
}
void win(char winner){
    printf("\nThe Winner is %c!", winner);
    game_end = true;
}

int ValidLetterNotation(char inputToCheck){
    switch(tolower(inputToCheck)){
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
        default:
            return -1;
    }
}
int ValidNumberNotation(int inputToCheck) {
    switch(inputToCheck) {
        case 1:
            return 0;
        case 2:
            return 1;
        case 3:
            return 2;
        case 4:
            return 3;
        case 5:
            return 4;
        case 6:
            return 5;
        case 7:
            return 6;
        case 8:
            return 7;
        default:
            return -1;
    }
}
