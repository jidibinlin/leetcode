#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        vector <vector<bool>> dp(s.length(),vector<bool>(s.length(),0));
        for (int i = 1; i < s.length(); ++i) {
            dp[i][i]=true;
        }
        int longest = 1;
        int start=0;

        for (int i=2; i <= s.length(); ++i) {
            for (int j=0 ; j+i<=s.length(); ++j) {
                if(i==2){
                    dp[j][j+1]=(s[j]==s[j+1]);
                    if(longest <=2 && dp[j][j+1]){
                        longest = i;
                        start=j;
                    }
                    continue;
                }

                dp[j][j+i-1]=dp[j+1][j+i-2] && (s[j]==s[j+i-1]);

                if(dp[j][j+i-1] && i>=longest){
                    longest = i;
                    start=j;
                }
            }
        }

        cout << longest<< endl;

        return s.substr(start, longest);
    }
};

int main() {
    Solution *s = new Solution();
    cout << s->longestPalindrome("bb") <<endl;

}
