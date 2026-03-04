#include <iostream>
using namespace std;

//==============================
//function to test replace
//==============================
bool printAnimal() {
    char choice;
    cout << "dogs are cool.\n";
    cout << "do you like dogs? [Y]/[N]\n";
    cin >> choice;
    if (choice == 'Y') {
        cout << "yeah! dogs are awesome\n";
        return true;
    } else {
        cout << "that is too bad. I think dogs are cool\n";
        return false;
    }
}

int main() {
    string yourname = "Skylar Miles";
    cout << "Hi " << yourname << ". Welcome.\n";
    cout << "==============================\n"; 
    printAnimal();
    return 0;
};

/* Task 5
 * (1) :wq
 * (2) :q, unless you made changes, in which case you can force with :q!
 * (3) u key or :u
 * (4) 5igo[space]<ESC>
 * (5) 100G or 100j from the top of the file
*/


