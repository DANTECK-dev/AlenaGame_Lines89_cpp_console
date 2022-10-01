#include <iostream>
#include <conio.h>
#include<windows.h>
#include <time.h>
#include <cstdlib>

using namespace std;

enum Color
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};
void SetCursor(int x, int y) {
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}
void SetColor(Color text, Color background)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((background << 4) | text));
}
class Cell {
public:
    int x = 1;
    int y = 1;
    Color color = Black;
    Cell() {};
    Cell(int x, int y, Color color) {
        this->color = color;
        this->x = x;
        this->y = y;
    }
    Cell(int x, int y) {
        this->x = x;
        this->y = y;
    }
};
class Game {
    Cell field[9][9];
    int x, y;
    int xBall, yBall;

public:
    Game() {
        int x1 = rand() % 9 + 1, x2 = rand() % 9 + 1, x3 = rand() % 9 + 1, x4 = rand() % 9 + 1, x5 = rand() % 9 + 1;
        int y1 = rand() % 9 + 1, y2 = rand() % 9 + 1, y3 = rand() % 9 + 1, y4 = rand() % 9 + 1, y5 = rand() % 9 + 1;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                field[i][j] = *new Cell(i, j);
            }
        }
        field[y1][x1].color = (Color)(rand() % 16);
        field[y2][x2].color = (Color)(rand() % 16);
        field[y3][x3].color = (Color)(rand() % 16);
        field[y4][x4].color = (Color)(rand() % 16);
        field[y5][x5].color = (Color)(rand() % 16);
    }
    
    void Show() {
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                if (((i == 0) || (i == 10)) && ((j == 0) || (j == 10))) {
                    cout << " ";
                    continue;
                }
                else if ((i == 0) || (i == 10))cout << j;
                else if ((j == 0) || (j == 10))cout << i;
                else cout << " ";
            }
            cout << "\n";
        }
    }
    void ShowField() {
        int x = 1;int y = 1;
        SetCursor(1, 1);
        SetColor(White, Black);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                SetCursor(x, y);
                SetColor(field[i][j].color, Black);
                cout << "O";
                y++;
            }
            x++;
            y = 1;
        }
    }
    void Move() {
        switch (_getch()) {
            case(27): {         //Exit
                exit(0);
                break;
            }
            case(13): {         //Enter
                if (field[y][x].color != Black) {
                    xBall = x; yBall = y;
                    SetCursor(x, y);
                    SetColor(field[y][x].color, White);
                }
            }
            case(72): {         //Up

            }
            case(80): {         //Down

            }
            case(75): {         //Left

            }
            case(77): {         //Right

            }
        }
    }
    void StartGame() {
        Show();
        ShowField();
    }
};
int main() {
    srand(time(NULL));
    Game *game = new Game();
    game->StartGame();
    system("pause");
}