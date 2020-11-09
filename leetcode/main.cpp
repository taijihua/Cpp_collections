#include "Find_All_Duplicates_In_Array.h"
int main()
{
    Solution test;
    vector<int> input {4,3,2,7,8,2,3,1};
    vector<int> ans = test.findDuplicates(input);
    for_each(ans.begin(), ans.end(), [](int j){cout<<j<<", ";});
    
    return 0;
}