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
    int x = 1; int y = 1;
    int xBall, yBall;
    bool isGameStopped = false;
    bool Selected = false;
    bool VisitedCells[9][9];
    bool FindedWay = false;
    int searchX, searchY;

public:
    Game() {
        int x1 = rand() % 10, x2 = rand() % 10, x3 = rand() % 10, x4 = rand() % 10, x5 = rand() % 10;
        int y1 = rand() % 10, y2 = rand() % 10, y3 = rand() % 10, y4 = rand() % 10, y5 = rand() % 10;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                field[i][j] = *new Cell(i, j);
            }
        }
        if (field[y1][x1].color == Black) this->field[y1][x1].color = (Color)(rand() % 16);
        if (field[y2][x2].color == Black) this->field[y2][x2].color = (Color)(rand() % 16);
        if (field[y3][x3].color == Black) this->field[y3][x3].color = (Color)(rand() % 16);
        if (field[y4][x4].color == Black) this->field[y4][x4].color = (Color)(rand() % 16);
        if (field[y5][x5].color == Black) this->field[y5][x5].color = (Color)(rand() % 16);
    }
    
    void Show() {
        SetColor(White, Black);
        SetCursor(0, 0);
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                if (((i == 0) || (i == 10)) && ((j == 0) || (j == 10))) { 
                    cout << " "; 
                }
                else if ((i == 0) || (i == 10)) { 
                    cout << j; 
                }
                else if ((j == 0) || (j == 10)) { 
                    cout << i; 
                }
                else { 
                    cout << " "; 
                }
            }
            cout << "\n";
        }
    }
    void ShowField() {
        int xTemp = 1;int yTemp = 1;
        SetCursor(1, 1);
        SetColor(White, Black);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                SetCursor(xTemp, yTemp);
                SetColor(field[i][j].color, Black);
                if (xTemp == x && yTemp == y) {
                    SetColor(field[x - 1][y - 1].color, White);
                }
                cout << "O";
                yTemp++;
            }
            xTemp++;
            yTemp = 1;
        }
    }
    void ititVisCells() {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                VisitedCells[i][j] = false;
        searchX = x;
        searchY = y;
    }
    bool FindingWay() {
        VisitedCells[searchX - 1][searchY - 1] = true;
        if (FindedWay) return true;
        if (xBall == searchX && yBall == searchY) {
            FindedWay = true;
            return true;
        }
        if (searchX + 1 == xBall && searchY == yBall) {
            searchX++;
            if (FindingWay()) return true;
        }
        if (searchX - 1 == xBall && searchY == yBall) {
            searchX--;
            if (FindingWay()) return true;
        }
        if (searchX == xBall && searchY + 1 == yBall) {
            searchY++;
            if (FindingWay()) return true;
        }
        if (searchX == xBall && searchY - 1 == yBall) {
            searchY--;
            if (FindingWay()) return true;
        }
        if ((VisitedCells[searchX - 1 + 1][searchY - 1] == false) && (field[searchX - 1 + 1][searchY - 1].color == Black)) {
            //VisitedCells[x - 1 + 1][y - 1] = true;
            if (searchX < 9 && searchX >= 1) {
                searchX++;
                if (FindingWay()) return true;
                else searchX--;
            }
        }
        if ((VisitedCells[searchX - 1 - 1][searchY - 1] == false) && (field[searchX - 1 - 1][searchY - 1].color == Black)) {
            //VisitedCells[x - 1 - 1][y - 1] = true;
            if (searchX <= 9 && searchX > 1) {
                searchX--;
                if (FindingWay()) return true;
                else searchX++;
            }
        }
        if ((VisitedCells[searchX - 1][searchY + 1 - 1] == false) && (field[searchX - 1][searchY + 1 - 1].color == Black)) {
            //VisitedCells[x - 1][y + 1 - 1] = true;
            if (searchY < 9 && searchY >= 1) {
                searchY++;
                if (FindingWay()) return true;
                else searchY--;
            }
        }
        if ((VisitedCells[searchX - 1][searchY - 1 - 1] == false) && (field[searchX - 1][searchY - 1 - 1].color == Black)) {
            //VisitedCells[x - 1][y - 1 - 1] = true;
            if (searchY <= 9 && searchY > 1) {
                searchY--;
                if (FindingWay()) return true;
                else searchY++;
            }
        }
        return false;
    }
    void newBalls() {
        int x1 = rand() % 10, x2 = rand() % 10, x3 = rand() % 10, x4 = rand() % 10, x5 = rand() % 10;
        int y1 = rand() % 10, y2 = rand() % 10, y3 = rand() % 10, y4 = rand() % 10, y5 = rand() % 10;
        if (this->field[y1][x1].color == Black) this->field[y1][x1].color = (Color)(rand() % 16);
        if (this->field[y2][x2].color == Black) this->field[y2][x2].color = (Color)(rand() % 16);
        if (this->field[y3][x3].color == Black) this->field[y3][x3].color = (Color)(rand() % 16);
        if (this->field[y4][x4].color == Black) this->field[y4][x4].color = (Color)(rand() % 16);
        if (this->field[y5][x5].color == Black) this->field[y5][x5].color = (Color)(rand() % 16);
    }
    void Move() {
        switch (_getch()) {
            case(27): {         //Exit
                exit(0);
                break;
            }
            case(13): {         //Enter
                if (Selected) {
                    if (field[x - 1][y - 1].color != Black) break;
                    ititVisCells();
                    if (FindingWay() == true) {
                        SetCursor(xBall, yBall);
                        Color temp = field[xBall - 1][yBall - 1].color;
                        SetColor(Black, Black);
                        cout << "O";
                        field[xBall - 1][yBall - 1].color = Black;
                        SetCursor(x, y);
                        SetColor(temp, White);
                        cout << "O";
                        field[x - 1][y - 1].color = temp;
                        newBalls();
                    }
                    Selected = false;
                    FindedWay = false;
                    SetCursor(12, 0);
                    SetColor(White, Black);
                    cout << "Selected: False";
                    SetCursor(x, y);
                }
                else 
                {
                    if (field[x - 1][y - 1].color != Black) {
                        xBall = x; yBall = y;
                        Selected = true;
                        SetCursor(12, 0);
                        SetColor(White, Black);
                        cout << "Selected: True ";
                        SetCursor(x, y);
                    }
                }
                break;
            }
            case(72): {         //Up
                if (y > 1) {
                    SetColor(field[x - 1][y - 1].color, Black);
                    y--;
                    SetCursor(x, y);
                }
                break;
            }
            case(80): {         //Down
                if (y < 9) {
                    SetColor(field[x - 1][y - 1].color, Black);
                    y++;
                    SetCursor(x, y);
                }
                break;
            }
            case(75): {         //Left
                if (x > 1) {
                    SetColor(field[x - 1][y - 1].color, Black);
                    x--;
                    SetCursor(x, y);
                }
                break;
            }
            case(77): {         //Right
                if (x < 9) {
                    SetColor(field[x - 1][y - 1].color, Black);
                    x++;
                    SetCursor(x, y);
                }
                break;
            }
        }
        SetColor(field[x - 1][y - 1].color, White);
        cout << "O";
        SetColor(field[x - 1][y - 1].color, Black);
    }
    void ChekLines() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (field[i][j].color != Black) {
                    searchX = i; searchY = j;
                    
                }

            }
        }
    }
    bool checkBounds(int x, int y) {
        bool BOUNDS = false;
        if ((x >= 0) && (x < 9) && (y >= 0) && (y < 9))BOUNDS = !BOUNDS;
        return BOUNDS;
    }
    int checkLine(int X, int Y, int I, int J) {
        int dx = 0, dy = 0, points = 0;
        dx = X;
        dy = Y;
        while (field[X][Y].color == field[dx][dy].color)
        {
            if (checkBounds(dx, dy)) {
                dx += I;
                dy += J;
                points++;
            }
            else break;
        }
        return points;
    }
    void destroyBalls(int X, int Y, int points, int I, int J)
    {
        int n = 0, dx = 0, dy = 0;
        dx = X;
        dy = Y;
        while (n != points)
        {
            field[dx][dy].color = Black;
            n++;
            dx += I;
            dy += J;
        }
    }
    void destroyLines() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (field[i][j].color != Black) {
                    if (checkLine(i, j, 1, 0) > 4)
                        destroyBalls(i, j, checkLine(i, j, 1, 0), 1, 0);
                    else if (checkLine(i, j, 1, 1) > 4)
                        destroyBalls(i, j, checkLine(i, j, 1, 1), 1, 1);
                    else if (checkLine(i, j, 0, 1) > 4)
                        destroyBalls(i, j, checkLine(i, j, 0, 1), 0, 1);
                    else if (checkLine(i, j, -1, 1) > 4)
                        destroyBalls(i, j, checkLine(i, j, -1, 1), -1, 1);
                }
            }
        }
    }
    void Stop() {
        system("cls");
        SetColor(Red, White);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << " ";
            }
            cout << endl;
        }
        SetCursor(1, 3);
        cout << "You Lose";  
    }
    void checkEmptyCells() {
        int max = 60;
        int counter = 0;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                if(field[i][j].color != Black) counter++;
                if (counter > max) {
                    Stop();
                    break;
                }
            }
    }
    void StartGame() {
        Show();
        while (!isGameStopped)
        {
            checkEmptyCells();
            ShowField();
            Move();
            Show();
            destroyLines();
            
        }
    }
};
int main() {
    srand(time(NULL));
    Game *game = new Game();
    game->StartGame();
    system("pause");
}