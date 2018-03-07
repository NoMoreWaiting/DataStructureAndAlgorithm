/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LeetCodeArray.h
 * Author: xuwei.huang
 *         Array
 *
 * Created on 2018年3月6日, 下午2:03
 */

#ifndef LEETCODEARRAY_H
#define LEETCODEARRAY_H

#include "Common.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::unordered_map;
using std::vector;

// Array

// 1 Two Sum

/*
 * Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 * Example:
 *  Given nums = [2, 7, 11, 15], target = 9,
 *  Because nums[0] + nums[1] = 2 + 7 = 9,
 *  return [0, 1].
 */

class TwoSum {
public:
    // my first

    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> tempVec;
        for (int i = 0; i < nums.size() - 1; i++) {
            int surplus = target - nums[i];
            vector<int>::iterator iter = std::find(nums.begin() + i + 1, nums.end(), surplus);
            if (iter != nums.end()) {
                tempVec.push_back(i);
                tempVec.push_back(iter - nums.begin());
                break;
            }
        }
        return tempVec;
    }

    // better version O(N)

    vector<int> BetterTwoSum(vector<int> & nums, int target) {
        vector<int> tempVec;
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++) {
            hash[nums[i]] = i;
        }
        for (int i = 0; i < nums.size(); i++) {
            int surplus = target - nums[i];
            unordered_map<int, int>::iterator iter = hash.find(surplus);
            if (iter != hash.end() and i != iter->second) {
                tempVec.push_back(i);
                tempVec.push_back(iter->second);
                break;
            }
        }
        return tempVec;
    }

    // better version 2 O(N)

    vector<int> BetterTwoSum2(vector<int> & nums, int target) {
        vector<int> tempVec;
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++) {
            int surplus = target - nums[i];
            unordered_map<int, int>::iterator iter = hash.find(surplus);
            if (iter != hash.end() && i != iter->second) {
                tempVec.push_back(i);
                tempVec.push_back(iter->second);
            }
            hash[nums[i]] = i;
        }
        return tempVec;
    }

    void Test() {
        vector<int> vecTest1;
        vecTest1.push_back(3);
        vecTest1.push_back(2);
        vecTest1.push_back(4);
        vecTest1.push_back(15);
        vector<int> vecTest2 = twoSum(vecTest1, 6);
        ShowVector<int> (vecTest2);

        ShowVector<int>(vecTest1);

        vector<int> vecTest3 = BetterTwoSum(vecTest1, 6);
        ShowVector<int> (vecTest3);

        ShowVector<int>(vecTest1);

        vector<int> vecTest4 = BetterTwoSum2(vecTest1, 6);
        ShowVector<int> (vecTest4);
    }
};


// 119 Pascal's Triangle II

/*
 * Given an index k, return the kth row of the Pascal's triangle.
 * For example, given k = 3,
 * Return [1,3,3,1].
 * Note:
 * Could you optimize your algorithm to use only O(k) extra space? 
 */

class PascalTriangle {
public:

    // my first

    vector<int> getRow(int rowIndex) {
        if (0 == rowIndex) {
            vector<int> temp;
            temp.push_back(1);
            return temp;
        }
        vector<int> lastRow = getRow(rowIndex - 1);

        lastRow.push_back(0);
        vector<int> temp;

        for (int i = 0; i <= rowIndex; i++) {
            temp.push_back(lastRow[i] + lastRow[rowIndex - i]);
        }
        return temp;
    }

    // better answer

    vector<int> getRowBetter(int rowIndex) {
        vector<int> arr(rowIndex + 1, 0);
        arr[0] = 1;
        for (int i = 1; i < rowIndex + 1; i++) {
            // ShowVector<int> (arr);

            for (int j = i; j >= 1; j--) {
                arr[j] += arr[j - 1];
            }
        }
        return arr;
    }

    void Test() {
        vector<int> vecTest1 = getRow(5);

        vector<int> vecTest2 = getRowBetter(5);

        ShowVector<int> (vecTest1);
        ShowVector<int> (vecTest2);
    }
};


// 169. Majority Element

/*
 * Given an array of size n, find the majority element. The majority element is the element that appears more than n/2  times.
 * 
 * You may assume that the array is non-empty and the majority element always exist in the array.
 * 
 * Credits:
 * Special thanks to @ts for adding this problem and creating all test cases.
 */

class MajorityElement {
public:

    // first version  it's no good
    int majorityElement(vector<int> & nums) {
        for (int i = 0; i < nums.size() / 2 + 1; i++) {
            int times = 0;
            for (int j = i; j < nums.size(); j++) {
                if (nums[i] == nums[j]) {
                    times++;
                }
                if (times > nums.size() / 2) {
                    return nums[i];
                }
            }
        }
        return 0;
    }

    int betterMajorityElement(vector<int> & nums) {
        std::sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }

    void Test() {
        vector<int> vecTest1;
        vecTest1.push_back(1);
        vecTest1.push_back(1);
        vecTest1.push_back(1);
        vecTest1.push_back(1);
        vecTest1.push_back(3);
        vecTest1.push_back(4);
        vecTest1.push_back(2);
        cout << majorityElement(vecTest1) << " , ";
        cout << betterMajorityElement(vecTest1) << endl;
    }

};




// 561 Array Partition I

/*
 * Given an array of 2n integers, your task is to group these integers into n pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi) for all i from 1 to n as large as possible.
 * Example 1:
 * Input: [1,4,3,2]
 * Output: 4
 * Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
 * Note:
 * n is a positive integer, which is in the range of [1, 10000].
 * All the integers in the array will be in the range of [-10000, 10000].
 
 */

class ArrayPartition {
public:

    int arrayPairSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int sum = 0;
        for (int i = 0; i < nums.size(); i += 2) {
            sum += nums[i];
        }
        return sum;
    }

    void Test() {
        vector<int> vecTest1;
        vecTest1.push_back(1);
        vecTest1.push_back(3);
        vecTest1.push_back(4);
        vecTest1.push_back(2);

        cout << arrayPairSum(vecTest1) << endl;
    }
};





#endif /* LEETCODEARRAY_H */

