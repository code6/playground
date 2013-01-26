#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

using namespace std;


bool check_binary_symmetric(int val) {
    int rval =  0;
    for (int tmp_val = val; tmp_val; tmp_val /=2) 
        rval = (rval << 1) + (tmp_val & 1); 
    return val == rval;
}

string get_bin(int val) {
    string ret = "";
    while (val) {
        char ch = val % 2 ? '1':'0';
        ret = ch + ret;
        val /= 2;
    }
    return ret;
}

int main() {
    for (int i = 0; i < 200; i++) {
        if (check_binary_symmetric(i)) {
            cout<<i<<" bin="<<get_bin(i)<<" "<<check_binary_symmetric(i)<<endl;
        }
    }
    return 0;
}
