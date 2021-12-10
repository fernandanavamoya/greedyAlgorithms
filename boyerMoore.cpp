/*
BOYER MOORE
Pattern searching algorith within a string.

Fernanda Nava Moya - A01023896
10/09/2021
*/

#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>

using namespace std;

// function to get maximum of the two intergers
// it is used to make sure that we get a positive shift
int findMax(int a, int b)
{
    if(a < b) return a;
    else return b;
}

// preprocessing function for boyer moore bad character heuristic
void badChar(string str, int len, vector<int> badchar) {
    // insert the last occurence of a character 
    for(int i = 0; i < len; i++)
        badchar[int(str[i])] = i;
}

// pattern searching function using boyer moore algorithm
vector<int> boyerMoore(string str, string pattern) {
    int strLen = str.length();
    int patternLen = pattern.size();

    vector<int> solution; // solution vector 
    vector<int> badchar(256,-1); // initialize badchar vector

    // fill the bad character vector with badChar function
    badChar(pattern, patternLen, badchar);

    // shift of pattern with respect to str
    int shift = 0;

    while (shift < (strLen - patternLen)) {
        int j = patternLen - 1;

        // reduce index of pattern while the character of pattern and str are matching at the shift
        while (j >= 0 && pattern[j] == str[shift + j]) j--;

        // if the pattern is at the current shift, the the index is -1
        if (j < 0) {
            // inserts the position of the match to the solution vector
            solution.push_back(shift);
            // shifts to next character in str to align with the last occurence of it in pattern
            // shift += (shift + strLen < patternLen) identifies if the patter occurs at the end of str
            shift += (shift + strLen < patternLen) ? strLen - badchar[str[shift + patternLen]] : 1; 
        }
        // else it shift the pattern so that the bad character in str aligns with the last occurence of it with pattern.
        // if the last occurance of bad character in pattern is on the right side of the current then we have a negative shift.
        else 
            shift += findMax(1, j - badchar[str[shift + j]]);
    }

    sort(solution.begin(), solution.end());
    return solution;
}
 
// Reads input values
int main(int argc, char *argv[]) 
{
    string str = argv[1];
    string pattern = argv[2];
    vector<int> solution = boyerMoore(str, pattern);

    for(int i = 0; i < solution.size();i++) {
        cout << solution[i] << " ";
    }
    cout << endl;

    return 0;
}