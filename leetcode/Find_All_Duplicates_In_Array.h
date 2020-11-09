/*
https://leetcode.com/problems/find-all-duplicates-in-an-array/
Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements that appear twice in this array.

Could you do it without extra space and in O(n) runtime?

Example:
Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        int n = nums.size();
        if(n>0)
        {
             // we add n to the index of the number we have, to indicate that we saw it already
            for(int i=0; i< n; i++)
            { int curr = nums[i];
              nums[(curr-1)%n] += n; //add n to the nums[i]-th element each time we see it
            }
            for(int i=0; i< n; i++) //get exact i-th element that got added by 2n
            {
                if(((nums[i]-1)/n)==2)
                    res.push_back(i+1);
            }
            
        }
        return res;
    }
};