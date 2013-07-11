#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

#define mp make_pair

vector<int> pr;

typedef long long ll;
using namespace std;

char board[10][10];

bool match(char a, char b) {
    if (a == '.' || b == '.') {
        return false;
    }
    return a == b || a == 'T' || b == 'T';
}

void update(int &owin, int &xwin, char ch) {
    if (ch == 'O') {
        owin ++;
    } else {
        xwin ++;
    }
}

void calc(int &owin, int &xwin) {
    int i, j;
    int xray, yray;
    char ch;
    xray = yray = 0;
    for (i = 0; i < 4; i++) {
        if (match(board[i][i],  board[0][0])) {
            xray ++;
        }
        if (match(board[i][3 - i],  board[0][3])) {
            yray ++;
        }
        for (j = 0; j < 4; j++) {
            if (!match(board[i][j], board[i][0])) {
                break;
            }
        }
        if (j == 4) {
            ch = board[i][0];
            update(owin, xwin, ch);
        }
        for (j = 0; j < 4; j++) {
            if (!match(board[j][i], board[0][i])) {
                break;
            }
        }
        if (j == 4) {
            ch = board[0][i];
            update(owin, xwin, ch);
        }
    }
    if (xray == 4) {
        ch = board[0][0];
        update(owin, xwin, ch);
    }
    if (yray == 4) {
        ch = board[0][3];
        update(owin, xwin, ch);
    }
}

void process(int cas) {
    int i, j;
    int empty = 0;
    int owin, xwin;
    owin = xwin = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            empty += board[i][j] == '.';
        }
    }

    bool found = false;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (board[i][j] == 'T') {
                board[i][j] = 'O';
                calc(owin, xwin);
                board[i][j] = 'X';
                calc(owin, xwin);
                found = true;
            }
        }
    }
    if (!found) {
        calc(owin, xwin);
    }

    string ans = "";

    if (owin) {
        ans = "O won";
    } else {
        if (xwin) {
            ans = "X won";
        } else {
            if (empty == 0) {
                ans = "Draw";
            } else {
                ans = "Game has not completed";
            }
        }
    }
    cout<<"Case #"<<cas<<": "<<ans<<endl;
}

void read() {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            scanf(" %c", &board[i][j]);
        }
    }
}

void run(int cas) {
    read();
    process(cas);
}

int main() {
    char *v = "1212";
    while (*v == '\0') putchar(*v), v++;

    return 0;
}
