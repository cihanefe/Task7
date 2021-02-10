
#include <iostream>
#include <windows.h>
using namespace std;

int boyut;
int length, height;
int score = 0;
bool gameUpdate = true;
string dif;

void ClearScreen() 
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

class Ekran {
public:
    Ekran() {
    }


    void initEkran(int x, int y) {
        screenx = x;
        screeny = y;
        for (int i = 0; i < screeny; i++) {
            for (int j = 0; j < screenx; j++) {
                if (j == 0) {
                    screen[j][i] = '#';
                }
                else if (i == 0 || i == screeny - 1) {
                    screen[j][i] = '#';
                }
                else {
                    screen[j][i] = ' ';
                }
            }
            cout << endl;
        }
    }
    void addChar(int x, int y, char c) {
        if (x != 0 && x != screenx - 1  && y != 0 && y != screeny - 1) {
            screen[x][y] = c;
        }
    }
    void moveChar(int x, int y, char c, int r, int l) {
        if (x != 0 && x != screenx - 1 && y != 0 && y != screeny - 1 && x + r != 0 && x + r != screenx - 1 && y + l != 0 && y + l != screeny - 1) {
            screen[x][y] = ' ';
            screen[x + r][y + l] = c;
        }

        
    }
    void drawScreen(string mod) {
        if (mod == "Normal") {
            x = "";
            for (int i = 0; i < screeny; i++) {
                for (int j = 0; j < screenx; j++) {
                    x += screen[j][i];
                    x += " ";
                }
                x += "\n";
            }
            system("cls");
            cout << x;
        }
        else if (mod == "Hard") {
            x = "";
            for (int i = 0; i < screeny; i++) {
                for (int j = 0; j < screenx; j++) {
                    x += screen[j][i];
                    x += " ";
                }
                x += "\n";
            }
            ClearScreen();
            cout << x;
        }
        else {
            x = "";
            for (int i = 0; i < screeny; i++) {
                for (int j = 0; j < screenx; j++) {
                    x += screen[j][i];
                    x += " ";
                }
                x += "\n";
            }
            ClearScreen();
            cout << x;
        }
    }
private:
    string x;
    char screen[100][100];
    int screeny;
    int screenx;
    
};

Ekran ekran;

class Player {
public:
    Player(int x, int y, char c, int size) {
        playerx = x;
        playery = y;
        players = c;
        playeru = size;
        playery2 = playery - playeru - 1;
        for (int i = playery; i > playery - playeru; i--) {
            ekran.addChar(playerx, i, players);
        }
    }
    void move(int mod, int y1, int y2) {
        if (mod == 1) {
            ekran.moveChar(playerx, playery2, players, 0, playeru);
            if (playery != height - 1) {
                playery2 += 1;
                playery += 1;
            }
        }
        else if (mod == -1) {
            ekran.moveChar(playerx, playery, players, 0, -playeru);
            if (playery2 != 0) {
                playery2 -= 1;
                playery -= 1;
            }
        }
        else if (mod == 0) {
            ekran.moveChar(playerx, playery, players, yatay, dusey);
            playerx += yatay;
            playery += dusey;
            if (playerx == length - 2) {
                gameUpdate = false;
            }
            if ((playery >= y2 && playery <= y1) && playerx == length - 3 ) {
                yatay = yatay * -1;
                score++;
            }
            else if (playerx == 1 && yatay == -1) {
                yatay = yatay * -1;
            }
            if ((playery == 1 && dusey == -1) || (playery == height - 2 && dusey == 1)) {
                dusey = dusey * -1;
            }
        }
    }

    int getY() { return playery; }
    int getY2() { return playery2; }
        
private:
    int playerx, playery, playeru, playery2;
    int yatay = 1;
    int dusey = 1;
    char players;
};

int main() {
    cout << "Map Length" << endl;
    cin >> length;
    cout << "Map Height" << endl;
    cin >> height;
    cout << "Racket Size" << endl;
    cin >> boyut;
    cout << "Difficulty(Normal/Hard)" << endl;
    cin >> dif;
    system("pause");
    ekran.initEkran(length, height);
    Player top(1, 1, 'O', 1);
    Player raket(length - 2, height - 2, '|', boyut);
    while (gameUpdate) {
        top.move(0, raket.getY(), raket.getY2());
        ekran.drawScreen(dif);
        Sleep(20);
        if (GetAsyncKeyState(VK_DOWN) < 0) {
            raket.move(1, 0, 0);
        }
        if (GetAsyncKeyState(VK_UP) < 0) {
            raket.move(-1, 0, 0);
        }
        cout << "score: " << score << endl;
    }
    ekran.drawScreen(dif);
    cout << "score: " << score << endl;
    cout << "Good Luck Next Time :D" << endl;
    system("pause");
    return 0;
}