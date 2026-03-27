#include <iostream>
#include <string>
using namespace std;

class RecursiveDescentParser {
private:
    string input;
    int index;

    char currentChar() {
        if (index < input.length())
            return input[index];
        return '\0';
    }
    
    bool match(char expected) {
        if (currentChar() == expected) {
            index++;
            return true;
        }
        return false;
    }

    // S → ( L ) | a
    bool S() {
        if (match('a')) {
            return true;
        }
        else if (match('(')) {
            if (L()) {
                if (match(')'))
                    return true;
            }
            return false;
        }
        return false;
    }

    // L → S L'
    bool L() {
        if (S()) {
            return LPrime();
        }
        return false;
    }

    // L' → , S L' | ε
    bool LPrime() {
        if (match(',')) {
            if (S()) {
                return LPrime();
            }
            return false;
        }
        // epsilon production
        return true;
    }

public:
    RecursiveDescentParser(string str) {
        // Remove spaces from input
        for (char c : str) {
            if (c != ' ')
                input += c;
        }
        index = 0;
    }

    bool parse() {
        if (S() && index == input.length())
            return true;
        return false;
    }
};

int main() {
    string str;

    cout << "Enter string: ";
    getline(cin, str);

    RecursiveDescentParser parser(str);

    if (parser.parse())
        cout << "Valid string" << endl;
    else
        cout << "Invalid string" << endl;

    return 0;
}