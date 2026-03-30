#include <bits/stdc++.h>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convert Infix to Postfix
string infixToPostfix(string s) {
    stack<char> st;
    string postfix = "";

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        if (isdigit(c)) {
            postfix += c;
            postfix += ' ';
        }
        else if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.pop(); // remove '('
        }
        else { // operator
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        postfix += st.top();
        postfix += ' ';
        st.pop();
    }

    return postfix;
}

// Generate Quadruple Table
void generateQuadruple(string postfix) {
    stack<string> st;
    int tempCount = 1;

    cout << "Operator\tOperand1\tOperand2\tResult\n";

    stringstream ss(postfix);
    string token;

    while (ss >> token) {
        // If operand
        if (isdigit(token[0])) {
            st.push(token);
        }
        else {
            string op2 = st.top(); st.pop();
            string op1 = st.top(); st.pop();

            string temp = "t" + to_string(tempCount++);

            cout << token << "\t\t" << op1 << "\t\t" << op2 << "\t\t" << temp << endl;

            st.push(temp);
        }
    }
}

int main() {
    string input;

    cout << "Enter expression: ";
    getline(cin, input);

    // Remove spaces
    input.erase(remove(input.begin(), input.end(), ' '), input.end());

    string postfix = infixToPostfix(input);

    cout << "\nPostfix Expression: " << postfix << endl << endl;

    generateQuadruple(postfix);

    return 0;
}