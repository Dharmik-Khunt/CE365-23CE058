#include <iostream>
#include <fstream>
#include <cctype>
#include <set>
#include <vector>
using namespace std;

/* ---------- Keywords ---------- */
string keywords[] = {
    "int","char","float","double","if","else",
    "while","for","return","void"
};

bool isKeyword(string s) {
    for (string k : keywords)
        if (k == s)
            return true;
    return false;
}

/* ---------- Operators ---------- */
string operators[] = {
    "+","-","*","/","%","=",
    "<",">","<=",">=","==","!="
};

bool isOperator(string s) {
    for (string op : operators)
        if (op == s)
            return true;
    return false;
}

/* ---------- Punctuation ---------- */
char punctuations[] = {
    '{','}','[',']','(',')',';',','
};

bool isPunctuation(char c) {
    for (char p : punctuations)
        if (p == c)
            return true;
    return false;
}

/* ---------- MAIN ---------- */
int main() {

    ifstream file("prac3_data.c");
    if (!file) {
        cout << "Error opening file!" << endl;
        return 0;
    }

    set<string> symbolTable;
    vector<string> lexicalErrors;

    char ch;
    int lineNo = 1;

    cout << "TOKENS\n";

    while (file.get(ch)) {

        /* Track line numbers */
        if (ch == '\n') {
            lineNo++;
            continue;
        }

        if (isspace(ch))
            continue;

        /* -------- Comments -------- */
        if (ch == '/') {
            char next = file.peek();
            if (next == '/') {
                while (file.get(ch) && ch != '\n');
                lineNo++;
                continue;
            }
            else if (next == '*') {
                file.get();
                while (file.get(ch)) {
                    if (ch == '\n') lineNo++;
                    if (ch == '*' && file.peek() == '/') {
                        file.get();
                        break;
                    }
                }
                continue;
            }
        }

        /* -------- Identifiers & Keywords -------- */
        if (isalpha(ch) || ch == '_') {
            string word;
            word += ch;

            while (isalnum(file.peek()) || file.peek() == '_') {
                file.get(ch);
                word += ch;
            }

            if (isKeyword(word)) {
                cout << "Keyword: " << word << endl;
            } else {
                cout << "Identifier: " << word << endl;
                symbolTable.insert(word);
            }
        }

        /* -------- Numbers & Invalid Lexemes -------- */
        else if (isdigit(ch)) {
            string num;
            num += ch;
            bool invalid = false;

            while (isalnum(file.peek())) {
                file.get(ch);
                if (isalpha(ch))
                    invalid = true;
                num += ch;
            }

            if (invalid) {
                lexicalErrors.push_back(
                    "Line " + to_string(lineNo) + " : " + num + " invalid lexeme"
                );
            } else {
                cout << "Constant: " << num << endl;
            }
        }

        /* -------- Character Constant -------- */
        else if (ch == '\'') {
            string literal;
            literal += ch;

            file.get(ch);
            literal += ch;

            file.get(ch);
            literal += ch;

            cout << "Constant: " << literal << endl;
        }

        /* -------- Operators -------- */
        else if (string("+-*/%=<>!").find(ch) != string::npos) {
            string op;
            op += ch;

            char next = file.peek();
            if (next != EOF && isOperator(op + next)) {
                file.get(ch);
                op += ch;
            }

            cout << "Operator: " << op << endl;
        }

        /* -------- Punctuation -------- */
        else if (isPunctuation(ch)) {
            cout << "Punctuation: " << ch << endl;
        }

        /* -------- Invalid Character -------- */
        else {
            lexicalErrors.push_back(
                "Line " + to_string(lineNo) + " : " + string(1, ch) + " invalid lexeme"
            );
        }
    }

    /* -------- LEXICAL ERRORS -------- */
    cout << "\nLEXICAL ERRORS\n";
    for (string err : lexicalErrors)
        cout << err << endl;

    /* -------- SYMBOL TABLE -------- */
    cout << "\nSYMBOL TABLE ENTRIES\n";
    int i = 1;
    for (auto id : symbolTable)
        cout << i++ << ") " << id << endl;

    file.close();
    return 0;
}