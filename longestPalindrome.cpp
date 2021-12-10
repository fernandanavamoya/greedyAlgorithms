#include <bits/stdc++.h>
using namespace std;

// finds palindromes of string and returns a vector with these
vector<int> LPS(string s)
{
	vector <int> LPS(s.size(), 1); // initialize vector 

    // start is the starting pos of palindrome  
    // end is the end pos of pastartndrome
    // i and j are the interators
	int i, j, end = 0, start = 0, center = 0;

    // for loop that finds the longest palindrome
	for(i=1; i < s.size(); i++) {
		if(i <= end) {
			LPS[i] = LPS[center - (i-center)];
            // if its bigger than end
			if((i+ (LPS[i]-1)/2) > end) 
				LPS[i] = 2 *(end- i) + 1;
            // if its equal than end
			else if((i+ (LPS[i]-1)/2) == end) {
				j = (LPS[i]-1)/2 + 1;
				while((i+j) < s.size() && (i-j)>= 0 && s[i+j]==s[i-j])
					j++;
				j--;
				LPS[i] = 2*j +1;
                // update variables
				center= i;
				start= i- j;
				end= i+ j; 
			}
		} 
		else {
           /*When index i for which we are calculating LPS is not inside parent pastartndrome.*/
			j=1;
			while((i+j) < s.size() && (i-j)>= 0 && s[i+j]==s[i-j])
					j++;
            // update variables
            j--;
            LPS[i] = 2*j +1;
            center= i;
            start= i- j;
            end= i+ j;
		}
	}
	return LPS; // vector with palindrome
}

// finds longest palindrome and returns a pair of int that are: length and index.
pair<int,int> longest(string str) {
    string s = "#"; // initialize with char that's going to be inserted between every chars in string

    // ans will store the store the length of longest palindrome and the index of where it starts
	pair<int,int> ans = make_pair(0, 1); // {length, index}

    //  --- FIRST CASE: get longest palindrome of ODD ---
    vector<int> palindrome = LPS(str); // its going to store palindrome of string

    // compare all palindromes to find longest 
	for(int i=0; i < palindrome.size(); i++) {
        // update ans, length and index 
		if(palindrome[i] > ans.first) {
			ans.first = palindrome[i];
			ans.second = i - (palindrome[i]-1)/2;
		}
	}

    // --- SECOND CASE: get longest palindrome of EVEN ---
    // for loop that's going to insert '#' and char in string
    for(int i =0; i < str.size(); i++) {
		s.push_back(str[i]); 
		s.push_back('#');
	}

    // update palindrome variable
	palindrome = LPS(s);

    // compare all palindromes to find longest 
	for(int i=0; i < palindrome.size(); i++) {
        // updates ans pair, length and index
		if((palindrome[i]-1)/2 > ans.first) {
			ans.first = (palindrome[i]-1)/2;
			ans.second = (i - (palindrome[i]-1)/2)/2;
		}
	}

	cout << "starts at index: " << ans.second << ", length: " << ans.first << endl; 
    return ans; 
}

int main(int argc, char *argv[])
{
	string str = argv[1]; // save input of a.out
    string noSpace; // string without spaces 

    // get the string without spaces and to lower case
    for(int i = 0; i < str.length(); i++) {
        if(str[i] != ' ') {
            noSpace += tolower(str[i]);
        }
    }
    pair<int, int> ans = longest(noSpace);
    return 0;
}