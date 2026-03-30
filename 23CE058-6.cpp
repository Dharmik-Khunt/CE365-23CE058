#include <stdio.h>
#include <string.h>

int i = 0;
char input[100];

/* Function declarations */
int S();
int L();
int Ldash();

/* Match terminal symbol */
int match(char expected)
{
    if(input[i] == expected)
    {
        i++;
        return 1;
    }
    return 0;
}

/* S → ( L ) | a */
int S()
{
    if(input[i] == 'a')
    {
        i++;
        return 1;
    }
    else if(input[i] == '(')
    {
        i++;
        if(L())
        {
            if(match(')'))
                return 1;
        }
        return 0;
    }
    return 0;
}

/* L → S L' */
int L()
{
    if(S())
        return Ldash();
    return 0;
}

/* L' → , S L' | ε */
int Ldash()
{
    if(input[i] == ',')
    {
        i++;
        if(S())
            return Ldash();
        return 0;
    }
    return 1;   /* ε (empty string) */
}

int main()
{
    printf("Enter the string: ");
    scanf("%s", input);

    if(S() && input[i] == '\0')
        printf("Valid string\n");
    else
        printf("Invalid string\n");

    return 0;
}