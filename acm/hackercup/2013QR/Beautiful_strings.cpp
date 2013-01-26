#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;


int n;
char buf[10000];

int main() {
    //freopen("sample.in", "r", stdin);
    freopen("beautiful_stringstxt.txt", "r", stdin);
freopen("beautiful_stringstxt.out", "w", stdout);
    cin >> n;
    gets(buf);
    for (int ca = 1; ca <= n; ca++) {
        gets(buf);
        int ct[26];
        memset(ct, 0, sizeof(ct));
        for (int i = 0; buf[i]; i++) {
            char ch = tolower(buf[i]);
            if ('a' <= ch && ch <= 'z') {
                ct[ch - 'a']++;
            }
        }
        sort(ct, ct + 26);
        int ans = 0;
        for (int i = 0; i < 26; i++) {
            ans += (i + 1) * ct[i];
        }
        printf("Case #%d: %d\n", ca, ans);
    }
    return 0;
}
