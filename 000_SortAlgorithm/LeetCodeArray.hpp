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
#include <list>
#include <set>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::list;
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
        for (int i = 0; i < (int) nums.size() - 1; i++) {
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
        for (int i = 0; i < (int) nums.size(); i++) {
            hash[nums[i]] = i;
        }
        for (int i = 0; i < (int) nums.size(); i++) {
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
        for (int i = 0; i < (int) nums.size(); i++) {
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
        return -1;
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
        for (int pivot = 1; pivot < (int) nums.size() - 1; pivot++) {
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
        for (int i = 0; i < (int) num.size(); i++) {

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
            while (i + 1 < (int) num.size() && num[i + 1] == num[i])
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
        for (int i = 0; i < (int) nums.size() - 2; i++) {
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
        for (int i = 0; i < (int) nums.size() / 2 + 1; i++) {
            int times = 0;
            for (int j = i; j < (int) nums.size(); j++) {
                if (nums[i] == nums[j]) {
                    times++;
                }
                if (times > (int) nums.size() / 2) {
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
        for (int i = 0; i < (int) nums.size(); i += 2) {
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

// 18. 4Sum
// Topics: array, hash table, two pointers

/*
 * Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.
 * 
 * Note: The solution set must not contain duplicate quadruplets.
 * 
 * For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.
 * 
 * A solution set is:
 * [
 *   [-1,  0, 0, 1],
 *   [-2, -1, 1, 2],
 *   [-2,  0, 0, 2]
 * ]
 */

class FourSumSolution {
public:

    // 降维打击
    // 玩五阶魔方的思路就是从五阶降到四阶，然后再从四阶降到三阶，最后再按照玩三阶魔方的老套路解决问题。

    vector<vector<int> > FourSum(vector<int> & nums, int target) {
        vector<vector<int> > vecRes;
        list<list<int> > listRes = KSum(nums, target, 4);
        for (list<list<int> >::iterator iter = listRes.begin(); iter != listRes.end(); iter++) {
            vector<int> tmp(iter->begin(), iter->end());
            vecRes.push_back(tmp);
        }
        return vecRes;
    }

    list<list<int> > KSum(vector<int> & nums, int target, int k) {
        list<list<int> > res;
        if (nums.empty() || (int) nums.size() < k || k < 2)
            return res;
        std::sort(nums.begin(), nums.end());
        list<int> prePath;
        kSumImpl(nums, target, k, 0, res, prePath);
        return res;

    }

    void kSumImpl(vector<int> & nums, int target, int k, int start, list<list<int> > &result, list<int> & prePath) {
        if (nums[start] * k > target || nums[nums.size() - 1] * k < target)
            return;
        if (2 == k) {
            // two sum, two pointer
            int left = start;
            int right = nums.size() - 1;
            while (left < right) {
                if (nums[left] + nums[right] < target)
                    left++;
                else if (nums[left] + nums[right] > target)
                    right--;
                else {
                    // 是经过排序后, 从左往右查找的序列, insert 和 push_back 一定是有序的
                    list<int> tempList;
                    tempList.insert(tempList.end(), prePath.begin(), prePath.end());
                    tempList.push_back(nums[left]);
                    tempList.push_back(nums[right]);
                    result.push_back(tempList);
                    left++;
                    right--;
                    while (left < right && nums[left] == nums[left - 1]) // 过滤重复
                        left++;
                    while (left < right && nums[right] == nums[right + 1]) // 过滤重复
                        right--;
                }
            }
        }
        else {
            for (int i = start; i < (int) nums.size() - k + 1; i++) {
                if (i > start && nums[i] == nums[i - 1]) // 去重
                    continue;
                if (nums[i] + nums[nums.size() - 1] *(k - 1) < target) // 最大情况也小于target
                    continue;
                if (nums[i] * k > target) // 最小情况也大于target
                    continue;
                if (nums[i] * k == target) { // 多个数相同的和等于目标
                    if (nums[i + k - 1] == nums[i]) {
                        list<int> tempList;
                        tempList.insert(tempList.end(), prePath.begin(), prePath.end());
                        tempList.insert(tempList.end(), nums.begin() + i, nums.begin() + i + k);
                        result.push_back(tempList);
                    }
                    break;
                }
                prePath.push_back(nums[i]);
                kSumImpl(nums, target - nums[i], k - 1, i + 1, result, prePath);
                // prePath.remove(prePath.size() - 1); // java 的用法, 和C++不一致
                prePath.pop_back(); // backtracking
            }
        }
        return;
    }

    void Test() {
        int arr[] = {2, 1, 0, -1};
        vector<int> nums(arr, arr + sizeof (arr) / sizeof (int));
        vector<vector<int> > vecRes = FourSum(nums, 2);
        cout << "FourSum: " << endl;
        for (int i = 0; i < (int) vecRes.size(); i++) {
            ShowVector<int>(vecRes[i]);
        }
    }
};


// 26. Remove Duplicates from Sorted Array
// Topics: array, two pointers

/*
 * Given a sorted array nums, remove the duplicates in-place such that each element appear only once and return the new length.
 * 
 * Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.
 * 
 * Example 1:
 * Given nums = [1,1,2],
 * Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively.
 * It doesn't matter what you leave beyond the returned length.
 */

class RemoveDuplicatesFromSortedArray {
public:

    int removeDuplicates(vector<int>& nums) {
        if (nums.size() < 2)
            return 0;

        int id = 1;
        int size = nums.size();
        for (int i = 1; i < size; i++) {
            if (nums[i] != nums[i - 1])
                nums[id++] = nums[i];
        }
        for (int i = size - id; i > 0; i--)
            nums.pop_back();
        return id;
    }

    void Test() {
        int arr[] = {0};
        vector<int> vec(arr, arr + sizeof (arr) / sizeof (int));
        removeDuplicates(vec);
        cout << "removeDuplicates: " << endl;
        ShowVector<int>(vec);
    }
};


// 27. Remove Element
// Topics: array, two pointers

/*
 * Given an array nums and a value val, remove all instances of that value in-place and return the new length.
 * Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.
 * The order of elements can be changed. It doesn't matter what you leave beyond the new length.
 * 
 * Example 1:
 * Given nums = [3,2,2,3], val = 3,
 * Your function should return length = 2, with the first two elements of nums being 2.
 * 
 * It doesn't matter what you leave beyond the returned length.
 * It doesn't matter what you leave beyond the returned length.
 */

class RemoveElement {
public:

    int removeElement(vector<int>& nums, int val) {
        if (nums.empty())
            return 0;
        int id = 0;
        for (int i = 0; i < int(nums.size()); i++) {
            if (val != nums[i]) {
                nums[id++] = nums[i];
            }
        }
        return id;
    }

    int anotherRemoveElement(vector<int> & nums, int val) {
        if (nums.empty())
            return 0;
        int i = 0, j = int(nums.size()) - 1;
        // 模仿快速排序, 两头指针, 注意输出剩余多少数据的i. 剩余数目不是下标. 
        while (j >= i) {
            while (val != nums[i] && j >= i)
                i++;
            while (val == nums[j] && j >= i)
                j--;
            if (j > i) {
                nums[i] += nums[j];
                nums[j] = nums[i] - nums[j];
                nums[i] = nums[i] - nums[j];
            }
        }
        return i;
    }

    void Test() {
        int arr[] = {3, 3, 3};
        vector<int> vec(arr, arr + sizeof (arr) / sizeof (int));
        vector<int> vec_back = vec;

        cout << "removeElement: " << removeElement(vec, 3) << endl;
        ShowVector<int>(vec);

        cout << "anotherRemoveElement: " << anotherRemoveElement(vec_back, 3) << endl;
        ShowVector<int>(vec_back);
    }
};


// 31. Next Permutation
// Topics: array

/*
 * Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
 * If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
 * The replacement must be in-place and use only constant extra memory.
 * 
 * Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
 * 
 * 1,2,3 → 1,3,2
 * 3,2,1 → 1,2,3
 * 1,1,5 → 1,5,1
 */

class NextPermutation {
public:
    // this is the key method in all range problem

    void nextPermutation(vector<int>& nums) {
        int size = int(nums.size());
        if (size < 2)
            return;
        int right = nums.size() - 1;
        while (right > 0) {
            if (nums[right - 1] < nums[right])
                break;
            right--;
        }
        if (0 == right) {
            std::reverse(nums.begin(), nums.end());
        }
        else {
            int left = right - 1;
            int big = nums.size() - 1;
            while (big > right) {
                if (nums[big] > nums[left])
                    break;
                big--;
            }
            nums[big] += nums[left];
            nums[left] = nums[big] - nums[left];
            nums[big] = nums[big] - nums[left];
            std::reverse(nums.begin() + right, nums.end());
        }
    }

    void Test() {
        int arr1[] = {1, 2, 3};
        int arr2[] = {3, 2, 1};
        int arr3[] = {1, 1, 5};
        vector<int> vec1(arr1, arr1 + sizeof (arr1) / sizeof (int));
        vector<int> vec2(arr2, arr2 + sizeof (arr2) / sizeof (int));
        vector<int> vec3(arr3, arr3 + sizeof (arr3) / sizeof (int));

        cout << "nextPermutation: " << endl;
        nextPermutation(vec1);
        nextPermutation(vec2);
        nextPermutation(vec3);

        ShowVector<int>(vec1);
        ShowVector<int>(vec2);
        ShowVector<int>(vec3);
    }
};


// 33. Search in Rotated Sorted Array
// Topics: array, binary search

/*
 * Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
 * (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
 * 
 * You are given a target value to search. If found in the array return its index, otherwise return -1.
 * 
 * You may assume no duplicate exists in the array.
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * 
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 * 
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 */

class SearchInRotatedSortedArray {
public:

    int search(vector<int>& nums, int target) {
        if (nums.empty())
            return -1;

        int left = 0, right = int(nums.size()) - 1, mid = 0;
        while (left < right) {
            mid = (left + right) / 2;
            if (nums[mid] > nums[right]) {
                left = mid + 1; // 注意这里需要+1, 不然那会无限循环(因为 2/2=1, 3/2 =1, 无法区分)
            }
            else {
                right = mid;
            }
        }

        int low = left; // left = mid+1, 保证元素是最大之后的最小元素
        left = 0;
        right = int(nums.size()) - 1;
        int real_mid = 0;

        // 用表面数组下标控制边界, 用实际数组的大小找到元素
        while (left <= right) {
            mid = (left + right) / 2;
            real_mid = (mid + low) % (int(nums.size())); // 循环数组用法. 余数
            if (nums[real_mid] == target) {
                return real_mid;
            }
            else if (nums[real_mid] > target) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return -1;
    }

    int anotherSearch(vector<int>& nums, int target) {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (nums[mid] == target) return mid;

            // 直接使用实际的数组下标来操作
            if (nums[lo] <= nums[mid]) {
                if (target >= nums[lo] && target < nums[mid]) {
                    hi = mid - 1;
                }
                else {
                    lo = mid + 1;
                }
            }
            else {
                if (target > nums[mid] && target <= nums[hi]) {
                    lo = mid + 1;
                }
                else {
                    hi = mid - 1;
                }
            }
        }
        return -1;
    }

    void Test() {
        int arr[] = {4};
        vector<int> vec(arr, arr + sizeof (arr) / sizeof (int));
        cout << "SearchInRotatedSortedArray: " << search(vec, 4) << endl;
        cout << "anotherSearch: " << anotherSearch(vec, 4) << endl;
    }
};


// 34. Search for a Range
// Topics: array, binary search

/*
 * Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.
 * 
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * If the target is not found in the array, return [-1, -1].
 * 
 * Example 1:
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3,4]
 * 
 * Example 2:
 * Input: nums = [5,7,7,8,8,10], target = 6
 * Output: [-1,-1]
 */

class SearchForARange {
public:

    vector<int> searchRange(vector<int>& nums, int target) {

        int size = nums.size();
        int left = 0, right = size - 1;
        vector<int> res(2, -1);
        if (nums.empty()) {
            return res;
        }

        // 第一次查找 下界
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        if (nums[left] != target)
            return res;
        else
            res[0] = left;

        // 第二次查找 上界. left 不清零
        right = size - 1;
        while (left < right) {
            int mid = (left + right) / 2 + 1; // 保证left偏向right
            if (nums[mid] > target) {
                right = mid - 1; // >
            }
            else {
                left = mid; // <=
            }
        }
        res[1] = right;
        return res;
    }

    vector<int> searchRangeLowerBound(vector<int>& nums, int target) {
        if (nums.empty()) {
            return {-1, -1};
        }
        int idx1 = lower_bound(nums, target);

        // 如果找到的数是有一个重复的, 那么-1 ok, 如果没有重复, 那么是同一个, 如果多个则显示的同样值的范围
        int idx2 = lower_bound(nums, target + 1) - 1;
        if (idx1 < int(nums.size()) && nums[idx1] == target)
            return {idx1, idx2};
        else
            return {-1, -1};
    }

    // 找到第一个不小于target的数的位置

    int lower_bound(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int mid = (r - l) / 2 + l;
            if (nums[mid] < target)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return l;
    }

    void Test() {
        int arr[] = {5, 6, 6, 6, 7, 8, 8, 10};
        vector<int> vec(arr, arr + sizeof (arr) / sizeof (int));
        vector<int> result = searchRange(vec, 6);
        cout << "SearchForARange: " << endl;
        ShowVector<int>(result);
        cout << "注意找的是这个数在数组内的范围" << endl;
        result = searchRangeLowerBound(vec, 6);
        cout << "searchRangeLowerBound: " << endl;
        ShowVector<int>(result);
    }
};


#endif /* LEETCODEARRAY_H */

