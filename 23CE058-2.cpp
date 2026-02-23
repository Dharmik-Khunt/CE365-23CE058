#include <iostream>
using namespace std;

int main()
{
    int states, symbols;
    int start, acceptCount;
    int accept[10];
    int transition[10][10];
    string input;
    int current, i, j;

    cout << "Number of input symbols: ";
    cin >> symbols;

    cout << "Enter number of states: ";
    cin >> states;

    cout << "Initial state: ";
    cin >> start;

    cout << "Number of accepting states: ";
    cin >> acceptCount;

    cout << "Accepting states: ";
    for (i = 0; i < acceptCount; i++)
        cin >> accept[i];

    cout << "Transition table:\n";
    for (i = 1; i <= states; i++)
        for (j = 0; j < symbols; j++)
            cin >> transition[i][j];

    cout << "Input string: ";
    cin >> input;

    current = start;

    for (i = 0; i < input.length(); i++)
    {
        if (input[i] == 'a')
            current = transition[current][0];
        else if (input[i] == 'b')
            current = transition[current][1];
        else
        {
            cout << "Invalid String";
            return 0;
        }
    }

    for (i = 0; i < acceptCount; i++)
    {
        if (current == accept[i])
        {
            cout << "Valid String";
            return 0;
        }
    }

    cout << "Invalid String";
    return 0;
}
