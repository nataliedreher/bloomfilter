#include <iostream>
#include <fstream>
#include <limits>
#include "../code/Bloom.h"
using namespace std;

int main(int argc, char* argv[])
{
    cout << "Welcome to the Bloom Filter!\n\n";
    cout << "Please enter a size for your bloom filter (100+).\n";
    int size;
    bool inputted = false;
    
    while (!inputted) {
        cin >> size;
        if (cin.fail()) {  
                    // If the user failed to enter a valid input an error output is given. 
                    // The cin is cleared so the user can try again
            cout << "\nInvalid number entered.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            inputted = true;
        }

    }

    cout << "Hi 1\n";

    Bloom mybloom;
    shared_ptr<bloom_filter> fltr = mybloom.InitFilter(size, true);
    cout << "Hi 2\n";
    bool done = false; 
    string selection;
    while (!done){
        cout << "Please choose from the following options:\n\n";
        cout << "1) Enter a username.\n";
        cout << "2) Check if username is available.\n";
        cout << "3) Show probability of a false positive.\n";
        cout << "4) Clear the bloom filter.\n";
        cout << "Q) Exit.\n\n";
        
        cin >> selection;

        if (selection == "q" || selection =="Q") {
            cout << "\nThank you for using my program!\nQuitting...\n\n";
            done = true;
        } else if (selection == "1") {
            bool valid = false;
            string user;
            while (!valid) {
                cout << "Please enter a username (minimum length of 4 characters).\n";
                cin >> user;
                if (user.size() > 3) {
                    if (mybloom.IsUsernamePossiblyAvailable(fltr,user)) {
                        valid = true;
                    } else {
                        cout << "\nUsername may not be available. Please enter a new username\n";
                    }
                    
                } else {
                    cout << "\nError. Please enter a valid username.\n";
                }
            }
            
            mybloom.AddToBloom(fltr,user); 
            cout << "\nUsername succcessfully added.\n";        
            
        } else if (selection == "2") {
            bool valid = false;
            string user;
            while (!valid) {
                cout << "\nPlease enter a username to see if it's available (minimum length of 4 characters).\n";
                cin >> user;
                if (user.size() > 3) {
                    if (mybloom.IsUsernamePossiblyAvailable(fltr,user)) {
                        cout << "\nThat username is available.\n\n";
                        valid = true;
                    } else {

                        cout << "\nThat username may not be available.\n\n";
                        valid = true;
                    }
                    
                } else {
                    cout << "\nError. Please enter a valid username.\n";
                }
            }
               
        } else if (selection == "3") {

            float p = mybloom.FalsePositiveChance(fltr);
            cout << "\nThe probability of a false positive is: " << p << "\n\n";

        } else if (selection == "4") {
            mybloom.Clear(fltr);
            cout << "\nBloom filter has been cleared.\n\n";
        } else {
            cout << "\nError, please reenter your selection.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    }
    

    return 0;
}