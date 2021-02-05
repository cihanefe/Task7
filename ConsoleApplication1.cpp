
#include <iostream>
#include <windows.h>
using namespace std;

int boyut;
int length, height;
char screen[100][100];
int screenx;
int screeny;

int n = 1;

class Ekran {
public:
    Ekran(int x, int y) {
        screenx = x;
        screeny = y;
        for (int i = 0; i < screeny; i++) {
            for (int j = 0; j < screenx; j++) {
                if (i == 0 || i == screeny - 1) {
                    screen[j][i] = '#';
                }
                else if (j == 0) {
                    screen[j][i] = '#';
                }
                else {
                    screen[j][i] = ' ';
                }
            }
            cout << endl;
        }
    }
    void drawScreen() {
        system("cls");
        for (int i = 0; i < screeny; i++) {
            for (int j = 0; j < screenx; j++) {
                cout << screen[j][i] << " ";
            }
            cout << endl;
        }
    }
};
class Player {
public:
    Player(int x, int y, char e, int d) {
        posx = x;
        posy = y;
        c = e;
        size = d;
        if (x != 0 && x != screenx  && y != 0 && y != screeny ) {
            for (int i = 0; i < d; i++) {
                screen[x][y] = e;
                 y++;
            }
        }
    }
    void move(int mod) {
        if (mod == 0) {
            if (posx != 0 && posx != screenx + 1 && posy != 0 && posy != screeny - 1 && posx + yatay != 0 && posx + yatay != screenx + 1 && posy + dusey != 0 && posy + dusey != screeny - 1) {
                screen[posx][posy] = ' ';
                screen[posx + yatay][posy + dusey] = c;
            }
            posx = posx + yatay;
            posy = posy + dusey;
            if (posx == 1 && yatay == -1) {
                yatay = yatay * -1;
            }
            if (posx == length-2 && (posy == q || posy == q + (size - 1)|| posy == q +size) && yatay == 1) {                    //burasý
                yatay = yatay * -1;
            }
            if (posx == length + 1 &&  yatay == 1) {                    //burasý
                yatay = yatay * -1;
            }
            if ((posy == 1 && dusey == -1) || (posy == height - 2 && dusey == 1)) {
                dusey = dusey * -1;
            }
            if (GetAsyncKeyState(VK_UP) < 0) {
                q--;
            }
            if (GetAsyncKeyState(VK_DOWN) < 0) {
                q++;
            }
            
            if (posx == length + 1) {
                system("cls");
                system("pause");
                cout << "Game Over" << endl;;
                cout << "Try again?" << endl;
                system("pause");
            }
        }
        else if (mod == 1) {
            if (GetAsyncKeyState(VK_UP) < 0) {
                if(posy != 1){
                    screen[posx][posy + (size - 1)] = ' ';
                    screen[posx][posy - 1] = c;
                    posy--;
                }
            }
            else if (GetAsyncKeyState(VK_DOWN) < 0) {
                if (posy + size != screeny - 1) {
                    screen[posx][posy] = ' ';
                    screen[posx][posy + size] = c;
                    posy++;
                }
            }
        }
    }
private:
    char c ;
    int q = 3;
    int posx = 1;
    int posy = 1;
    int dusey = 1;
    int yatay = 1;
    int size;
};

int main() {
    cout << "Please Insert " << endl;
    cout << "Lenght: ";
    cin >> length;
    cout << "Height: ";
    cin >> height;
    cout << "Racket size: ";
    cin >> boyut;
    system("pause");
    Ekran ekran(length, height);
    Player top(5, 3, 'O', 1);
    Player raket(length - 1, 3, '|', boyut);
    while (true) {
        raket.move(1);
        top.move(0);
        ekran.drawScreen();
        Sleep(20);
    }
    system("pause");
    return 0;
}