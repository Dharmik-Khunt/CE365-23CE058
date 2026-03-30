#include <iostream>
#include <string>
using namespace std;

int main() {
    int numSymbols;
    cout << "Number of input symbols: ";
    cin >> numSymbols;

    char symbols[10];
    cout << "Input symbols: ";
    for (int i = 0; i < numSymbols; i++) {
        cin >> symbols[i];
    }

    int numStates;
    cout << "Enter number of states: ";
    cin >> numStates;

    int currentState;
    cout << "Initial state: ";
    cin >> currentState;

    int numAccept;
    cout << "Number of accepting states: ";
    cin >> numAccept;

    int acceptStates[10];
    cout << "Accepting states: ";
    for (int i = 0; i < numAccept; i++) {
        cin >> acceptStates[i];
    }

    // Transition table
    int transition[20][20];
    cout << "Transition table:\n";

    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            int to;
            
            cout<<i+1<< " to " << symbols[j] <<" ->";
            cin>> to;
            transition[i+1][symbols[j]] = to;
        }
    }

    string inputString;
    cout << "Input string: ";
    cin >> inputString;

    // Process the string
    for (int i = 0; i < inputString.length(); i++) {
        char ch = inputString[i];
        currentState = transition[currentState][ch];
        cout<<currentState<<" ";
    }
    cout<<endl;
    // Check accepting state
    bool valid = false;
    for (int i = 0; i < numAccept; i++) {
        if (currentState == acceptStates[i]) {
            valid = true;
            break;
        }
    }

    if (valid)
        cout << "Valid String";
    else
        cout << "Invalid String";

    return 0;
}