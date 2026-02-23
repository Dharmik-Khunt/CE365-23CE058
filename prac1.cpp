#include <iostream>
using namespace std;

int main()
{
    string s;
    cout<<"enter string";
    cout<<endl;
    cin >> s;

    int i = 0;

    while (i < s.length() && s[i] == 'a')
    {
        i++;
    }

    if (i + 1 < s.length() && s[i] == 'b' && s[i + 1] == 'b' && i + 2 == s.length())
    {
        cout << "Valid String";
    }
    else
    {
        cout << "Invalid String";
    }

    return 0;
}