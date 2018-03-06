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
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// Array

// 119 Pascal's Triangle II

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


// 561 Array Partition I

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
        
        cout << arrayPairSum(vecTest1) <<endl;
    }
};





#endif /* LEETCODEARRAY_H */

