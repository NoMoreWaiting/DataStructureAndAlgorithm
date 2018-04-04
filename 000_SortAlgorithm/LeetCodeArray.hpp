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
#include <set>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::unordered_map;
using std::vector;

// Array

// 1 Two Sum
// topics: array, hash table

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


// 4. Median of Two Sorted Arrays
// topics: array, binary search, divide and conquer

/*
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 * 
 * Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 * 
 * Example 1:
 * nums1 = [1, 3]
 * nums2 = [2]
 * 
 * The median is 2.0
 * Example 2:
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 * 
 * The median is (2 + 3)/2 = 2.5
 */

class MedianOfTwoSortedArrays {
public:

    double findMedianSortedArrays(vector<int> & A, vector<int> & B) {
        if (A.size() > B.size()) {
            return findMedianSortedArrays(B, A);
        }

        int m = A.size();
        int n = B.size();
        int imin = 0, imax = m, mid = (m + n + 1) / 2;
        while (imin <= imax) {
            int i = (imin + imax) / 2; // 二分查找
            int j = mid - i;
            if (i > 0 && A[i - 1] > B[j]) {
                // i is too big, must decrease it
                imax = i - 1;
            }
            else if (i < m && B[j - 1] > A[i]) {
                // i is too small, must increase it
                imin = i + 1;
            }
            else {
                // now i is perfect
                int maxOfLeft = 0;
                int minOfRight = 0;
                if (i == 0)
                    maxOfLeft = B[j - 1];
                else if (j == 0)
                    maxOfLeft = A[i - 1];
                else
                    maxOfLeft = A[i - 1] > B[j - 1] ? A[i - 1] : B[j - 1];

                if ((m + n) % 2 == 1)
                    return maxOfLeft;

                if (i == m)
                    minOfRight = B[j];
                else if (j == n)
                    minOfRight = A[i];
                else
                    minOfRight = A[i] < B[j] ? A[i] : B[j];

                return (maxOfLeft + minOfRight) / 2.0;
            }
        }
    }

    void Test() {
        int array1[] = {1, 3};
        int array2[] = {2};
        vector<int> vec1(array1, array1 + sizeof (array1) / sizeof (int));
        vector<int> vec2(std::begin(array2), std::end(array2));

        cout << "findMedianSortedArrays " << findMedianSortedArrays(vec1, vec2) << endl;

    }
};



// 11. Container With Most Water
// Topics: array, two pointers

/*
 * Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.
 *
 * Note: You may not slant the container and n is at least 2.
 */

class ContainerWithMostWater {
public:

    int maxArea(vector<int>& height) {
        if (height.size() < 2) {
            return 0;
        }

        int i = 0, j = height.size() - 1;
        int water = 0;
        while (i < j) {
            int h = std::min(height[i], height[j]);
            water = std::max(water, h * (j - i));
            while (height[i] <= h && i < j) // 向右扩张, 找到大于上次高度值的数字(包括本身)
                i++;
            while (height[j] <= h && i < j) // 向左扩张, 找到大于上次高度值的数字(包括本身), 两者小量向前扩张
                j--;
        }
        return water;
    }

    void Test() {
        vector<int> vec = {1, 3, 5, 2, 54, 2, 41, 4};
        cout << "ContainerWithMostWater: " << maxArea(vec) << endl;
    }
};



// 119 Pascal's Triangle II
// topics: array

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


// 15. 3Sum
// Topics: array, two pointers

/*
 * Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
 * 
 * Note: The solution set must not contain duplicate triplets.
 * 
 * For example, given array S = [-1, 0, 1, 2, -1, -4],
 * A solution set is:
 * [
 *   [-1, 0, 1],
 *   [-1, -1, 2]
 * ]
 */

class ThreeSum {
public:

    vector<vector<int> > threeSum(vector<int>& nums) {
        set<vector<int> > resultSet;
        vector<vector<int> > resultVec;
        if (nums.size() < 3)
            return resultVec;

        std::sort(nums.begin(), nums.end());
        // 以中间值作为过滤虽然看似比较次数少了, 但逻辑有点乱, 带来了去重问题
        for (int pivot = 1; pivot < nums.size() - 1; pivot++) {
            int i = 0, j = nums.size() - 1;
            int needSum = 0 - nums[pivot];
            for (; i < pivot && j > pivot;) {
                int sum = nums[i] + nums[j];
                if (sum == needSum) {
                    vector<int> tempVec(3, 0);
                    tempVec[0] = nums[i];
                    tempVec[1] = nums[pivot];
                    tempVec[2] = nums[j];
                    resultSet.insert(tempVec);
                    while (i < pivot && nums[i] == tempVec[0])
                        i++;
                    while (j > pivot && nums[j] == tempVec[2])
                        j--;
                    i++;
                    j--;
                }
                else if (sum > needSum) {
                    j--; // 排序之后, 坐标向左移动, 和减小
                }
                else
                    i++; // 排序之后, 坐标向右移动, 和增大
            }
        }

        if (!resultSet.empty()) {
            resultVec.insert(resultVec.end(), resultSet.begin(), resultSet.end());
        }

        return resultVec;
    }

    vector<vector<int> > betterThreeSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> res;
        for (int i = 0; i < n - 2; i++) { // 从左侧开始向右遍历排序的集合
            if (i > 0 && (nums[i] == nums[i - 1]))
                continue;
            int l = i + 1, r = n - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum < 0)
                    l++;
                else if (sum > 0)
                    r--;
                else {
                    res.push_back(vector<int>{nums[i], nums[l], nums[r]});
                    while (l + 1 < r && nums[l] == nums[l + 1])
                        l++;
                    while (l < r - 1 && nums[r] == nums[r - 1])
                        r--;
                    l++;
                    r--;
                }
            }
        }

        return res;
    }

    vector<vector<int> > anotherThreeSum(vector<int>& num) {
        vector<vector<int> > res;
        std::sort(num.begin(), num.end());
        for (int i = 0; i < num.size(); i++) {

            int target = -num[i];
            int front = i + 1;
            int back = num.size() - 1;

            if (target < 0) {
                break; // num[i] is min, a < b < c, a+b+c =0, if a<0, then b+c >0
            }

            while (front < back) {

                int sum = num[front] + num[back];

                // Finding answer which start from number num[i]
                if (sum < target)
                    front++;

                else if (sum > target)
                    back--;

                else {
                    vector<int> triplet(3, 0);
                    triplet[0] = num[i];
                    triplet[1] = num[front];
                    triplet[2] = num[back];
                    res.push_back(triplet);

                    // Processing duplicates of Number 2
                    // Rolling the front pointer to the next different number forwards
                    while (front < back && num[front] == triplet[1]) front++;

                    // Processing duplicates of Number 3
                    // Rolling the back pointer to the next different number backwards
                    while (front < back && num[back] == triplet[2]) back--;
                }

            }

            // Processing duplicates of Number 1
            while (i + 1 < num.size() && num[i + 1] == num[i])
                i++;
        }

        return res;
    }

    void Test() {
        int arr[] = {-1, 0, 1, 2, -1, -4};
        vector<int> srcVec(arr, arr + sizeof (arr) / sizeof (int));
        vector<vector<int> > threeSumVec = threeSum(srcVec);
        if (threeSumVec.empty())
            return;

        cout << "ThreeSum: " << endl;
        for (vector<vector<int> >::iterator iter = threeSumVec.begin(); iter != threeSumVec.end(); iter++) {
            ShowVector<int>(*iter);
        }
        cout << "<--ThreeSum" << endl;



        threeSumVec = betterThreeSum(srcVec);
        if (threeSumVec.empty())
            return;

        cout << "ThreeSum: " << endl;
        for (vector<vector<int> >::iterator iter = threeSumVec.begin(); iter != threeSumVec.end(); iter++) {
            ShowVector<int>(*iter);
        }
        cout << "<--ThreeSum" << endl;

    }
};


// 16. 3Sum Closest
// Topics: array, two pointers

/*
 * Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.
 * 
 * For example, given array S = {-1 2 1 -4}, and target = 1.
 * The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */

class ThreeSumClosest {
public:

    int threeSumClosest(vector<int>& nums, int target) {
        if (nums.size() <= 3) {
            return std::accumulate(nums.begin(), nums.end(), 0);
        }
        std::sort(nums.begin(), nums.end());

        int sum = 0;
        int res = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < nums.size() - 2; i++) {
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                sum = nums[i] + nums[left] + nums[right];
                if (std::abs(target - res) > abs(target - sum)) {
                    res = sum;
                    if (res == target)
                        return res;
                }
                (sum > target) ? right-- : left++;
            }
        }
        return res;
    }

    void Test() {
        int arr[] = {-1, 2, 1, -4};
        vector<int> vec(arr, arr + sizeof (arr) / sizeof (int));
        int target = 1;
        cout << "threeSumClosest: " << threeSumClosest(vec, target) << endl;
    }

};



// 169. Majority Element
// topics: array, divide and conquer, bit manipulation

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
// topics: array

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

