#include <limits.h>
#include <iostream>
#include <stdio.h>

using namespace std;
 
void f(int x) {
  if(x>=0) printf("x is positive");
  else if(x==-x) printf("x==-x\n");
  else printf("x != -x\n");
} 
 
int main(void) {
    string s(3, ' ');
    s[0] = char(0);
    s[1] = char(0);
    s[2] = char(0);
    cout << s.size() << endl;
  //f(INT_MIN);
  return 0;
}
