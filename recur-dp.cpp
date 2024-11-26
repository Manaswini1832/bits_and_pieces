/******************************************************************************
Print all permutations of a string
*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

vector<int> constructCandidates(string& s, vector<bool>& used){
    vector<int> candidates;
    for(int i = 0; i < used.size(); i++){
        if(!used[i]) candidates.push_back(i);
    }
    return candidates;
}

void Backtrack(string& s, string& permut, vector<string>& output, vector<bool>& used){
    //if a solution, process it
    if(permut.size() == s.size()){
        output.push_back(permut);
        return;
    }
    
    //else construct candidates for next element of partial solution and recursively build the solution
    vector<int> candidates = constructCandidates(s, used);
    
    for(int i = 0; i < candidates.size(); i++){
        int idx = candidates[i];
        used[idx] = true;
        permut += s[idx];
        Backtrack(s, permut, output, used);
        used[idx] = false;
        permut.pop_back();
    }
}

//main function
vector<string> permuts(string& s){
    vector<string> output;
    string permut = "";
    vector<bool> used(s.size(), false);
    Backtrack(s, permut, output, used);
    return output;
}

int main()
{
    string s = "mini";
    vector<string> res = permuts(s);
    for(string perm: res) cout << perm << "\n";

    return 0;
}

/******************************************************************************
Print all permutations of n-pairs parenthesis
*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void Backtrack(string& combo, vector<string>& output, int left, int right){
    //if no of leftParenths > rightParenths at any point, that means there was an imbalance so don't proceed down that path
    if(left < 0 || right < left || right < 0) return;
    
    if(left == 0 && right == 0){
        output.push_back(combo);
        return;
    }
    
    combo += '(';
    Backtrack(combo, output, left-1, right);
    combo.pop_back();
    
    combo += ')';
    Backtrack(combo, output, left, right-1);
    combo.pop_back();
}

vector<string> nPairsParenths(int n){
    vector<string> output;
    string combo = "";
    Backtrack(combo, output, n, n);
    return output;
}

int main()
{
    vector<string> res = nPairsParenths(3);
    for(string str: res){
        cout << str << "\n";
    }

    return 0;
}

/******************************************************************************
Implement the paint fill function seen in image editing pgms. Given a screen(represented
as a 2d array of colors), a point and a new color, fill the surrounding area until 
the color changes from the original color

*******************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

void print_(vector<vector<int>>& screen){
    int r = screen.size(), c = screen[0].size();
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            cout << screen[i][j] << " ";
        }
        cout << "\n";
    }
    cout << endl;
}

void dfs(vector<vector<int>>& screen, int oldColor, vector<int> point, int newColor){
    screen[point[0]][point[1]] = newColor;
    int dirx[] = {0, -1, 0, 1, -1, 1, 1, -1};
    int diry[] = {-1, 0, 1, 0, 1, -1, 1, -1};
    for(int i = 0; i < 8; i++){
        int x = point[0] + dirx[i];
        int y = point[1] + diry[i];
        if(x < screen.size() && x >= 0 && y < screen[0].size() && y >= 0 && screen[x][y] != newColor && screen[x][y] == oldColor){
            dfs(screen, oldColor, {x, y}, newColor);
        }
    }
}

void floodFill(vector<vector<int>>& screen, vector<int> point, int newColor){
    dfs(screen, screen[point[0]][point[1]], point, newColor);
}

int main()
{
    vector<vector<int>> screen = {
        {2, 1, 1, 2},
        {1, 2, 2, 1},
        {1, 2, 2, 1},
        {2, 1, 1, 2}
    };
    
    print_(screen);
    
    int newColor = 3;
    vector<int> point = {1, 2};
    
    floodFill(screen, point, newColor);
    print_(screen);
    

    return 0;
}

/******************************************************************************
Given an infinite number of coins of denominations 25,10,5,1, calculate the 
no of ways of representing the amount n
*******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Backtrack(vector<int>& denoms, int amount, int start){
    if(start < 0) return 0;
    if(amount == 0) return 1;
    //choose the denom
    int choose = 0;
    if(amount >= denoms[start])
        choose = Backtrack(denoms, amount-denoms[start], start);
    
    //skip this denom
    int skip = Backtrack(denoms, amount, start-1);
    
    return choose+skip;
}

int numWays(vector<int>& denoms, int amount){
    sort(denoms.begin(), denoms.end());
    //check the no of ways to make amount starting from index = idx in denoms and going right each time
    int result = Backtrack(denoms, amount, denoms.size()-1);
    return result;
}

int main()
{
    vector<int> denoms = {5,1,2};
    cout << numWays(denoms, 5) << endl;
    

    return 0;
}

/******************************************************************************
give widths, heights, depths of boxes stack a smaller one(in terms of w,h,d all) on top of bigger ones
such that the stack formed is of the max height
this code doesn't directly solve the problem but is similar to solving it.
At each stage choose a smaller box as compared to previous bigger one and keep track of maxStackHt, which is returned
at the end just like maxSum here
*******************************************************************************/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void Backtrack(vector<int>& nums, int& result, int sum, int start){
    if(start == nums.size()){
        result = max(result, sum);
        return;
    }
    //choose current num
    Backtrack(nums, result, sum+nums[start], start+1);
    //skip the current num
    Backtrack(nums, result, sum, start+1);
}

int maxSum(vector<int>& nums){
    int result = INT_MIN;
    Backtrack(nums, result, 0, 0);
    return result;
}

int main()
{
    
    vector<int> nums = {1,2,-3,4};
    cout << "Overall max sum : " << "\n";
    cout << maxSum(nums) << endl;

    return 0;
}
