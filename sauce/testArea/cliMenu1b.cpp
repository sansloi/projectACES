/* try to simulate an ongoing loop */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

bool flayStart = 0, rdyFlag = 1, rdyFlag2 = 1;
int rdyPot1, rdyPot2, rdyPot3;
char junk = ' ';
long temps; // ms
int a;

void startMenu() {
    cout << "Please select an option" << endl;
    cout << "1: Start Program 1" << endl;
    cout << "2: Start Program 2" << endl;
    cout << "3: Start Program 3" << endl;
    cout << "4: Start Program 4" << endl;
}

void program4() {
    cout << "a = 4" << endl;
    }

void setup() {
    printf("Hello World!\n");
    cout << "hello world" << endl;
}

int main() {
   startMenu();
    cin  >> a;          // declared above
    if (a == 1) {
        cout << "a = 1" << endl;
        cout << " you have selected 1" << endl;
    }
    else if (a == 2) {
        cout << "a = 2" << endl;
        cout << "you have selected 2" << endl;
   }
    else if (a == 3) {
        cout << "a = 3" << endl;
  }
    else if (a == 4) {
        program4();
    }
    else {
//        startMenu();
          main();
        }
    cout << "a + 1 = " << a+1 << endl;
    return 0;
}

// a keeps equaling '1'. if you give it a letter, you get a segmentation
// fault.. so find a way to protect against this.. -j
