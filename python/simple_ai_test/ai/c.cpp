#include <iostream>
#include <string>
using namespace std;

string msg;
int key = 0;

int main() 
{
    while (1) {
        cin >> msg;
        if (msg == "GUESS") {
            cout<<key<<endl;
        }  
        if (msg == "END") {
            break;
        }
    }
    return 0;
}
