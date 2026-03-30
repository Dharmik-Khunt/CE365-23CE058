#include <bits/stdc++.h>
using namespace std;

// Function to check operator
bool isOperator(string s) {
    return (s == "+" || s == "-" || s == "*" || s == "/");
}

// Function to perform calculation
double applyOp(double a, double b, string op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b;
    return 0;
}

// Check if string is number
bool isNumber(string s) {
    for (char c : s) {
        if (!isdigit(c) && c != '.') return false;
    }
    return true;
}

// Tokenize input
vector<string> tokenize(string s) {
    vector<string> tokens;
    string temp = "";

    for (int i = 0; i < s.size(); i++) {
        if (isspace(s[i])) continue;

        if (isdigit(s[i]) || s[i] == '.') {
            temp += s[i];
        }
        else if (isalpha(s[i])) {
            temp += s[i];
        }
        else {
            if (!temp.empty()) {
                tokens.push_back(temp);
                temp = "";
            }
            tokens.push_back(string(1, s[i]));
        }
    }
    if (!temp.empty()) tokens.push_back(temp);

    return tokens;
}

// Constant Folding
string constantFold(vector<string> tokens) {

    // First handle * and /
    for (int i = 0; i < tokens.size(); i++) {
        if ((tokens[i] == "*" || tokens[i] == "/") &&
            isNumber(tokens[i-1]) && isNumber(tokens[i+1])) {

            double a = stod(tokens[i-1]);
            double b = stod(tokens[i+1]);
            double res = applyOp(a, b, tokens[i]);

            tokens[i-1] = to_string(res);
            tokens.erase(tokens.begin() + i);     // remove operator
            tokens.erase(tokens.begin() + i);     // remove operand

            i--;
        }
    }

    // Then handle + and -
    for (int i = 0; i < tokens.size(); i++) {
        if ((tokens[i] == "+" || tokens[i] == "-") &&
            isNumber(tokens[i-1]) && isNumber(tokens[i+1])) {

            double a = stod(tokens[i-1]);
            double b = stod(tokens[i+1]);
            double res = applyOp(a, b, tokens[i]);

            tokens[i-1] = to_string(res);
            tokens.erase(tokens.begin() + i);
            tokens.erase(tokens.begin() + i);

            i--;
        }
    }

    // Build final expression
    string result = "";
    for (auto &t : tokens) {
        result += t + " ";
    }

    return result;
}

int main() {
    string input;

    cout << "Enter expression: ";
    getline(cin, input);

    vector<string> tokens = tokenize(input);

    string optimized = constantFold(tokens);

    cout << "\nOptimized Expression:\n" << optimized << endl;

    return 0;
}