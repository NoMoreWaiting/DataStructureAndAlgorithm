/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        main.cpp
 * Author:      xuwei.huang
 * Describe:    
 * Created on   2018年1月10日, 上午9:55
 * 
 * 参考: http://blog.csdn.net/zhangjikuan/article/details/49095533
 *      http://blog.csdn.net/k346k346/article/details/50791102
 *      http://blog.csdn.net/u013074465/article/details/42083607
 *      https://www.cnblogs.com/wzhiq896/p/5904891.html
 *      http://blog.csdn.net/qq_21688757/article/details/53749198
 *      http://blog.csdn.net/a2796749/article/details/46609401
 * 
 */

#include <iostream>

#include "LeetCodeArray.hpp"
#include "LeetCodeList.hpp"
#include "LeetCodeMath.hpp"
#include "LeetCodeString.hpp"


using namespace std;

// array 

void LeetCodeArray() {

    TwoSum twoSum;
    twoSum.Test();

    MedianOfTwoSortedArrays medianOfTwoSortedArrays;
    medianOfTwoSortedArrays.Test();

    PascalTriangle pascalTriangle;
    pascalTriangle.Test();

    ContainerWithMostWater containerWithMostWater;
    containerWithMostWater.Test();

    ThreeSum threeSum;
    threeSum.Test();

    ThreeSumClosest threeSumClosest;
    threeSumClosest.Test();

    MajorityElement majorityElement;
    majorityElement.Test();

    ArrayPartition arrayPartition;
    arrayPartition.Test();

    FourSumSolution fourSumSolution;
    fourSumSolution.Test();

    RemoveDuplicatesFromSortedArray removeDuplicatesFromSortedArray;
    removeDuplicatesFromSortedArray.Test();

    RemoveElement removeElement;
    removeElement.Test();

    NextPermutation nextPermutation;
    nextPermutation.Test();

    SearchInRotatedSortedArray searchInRotatedSortedArray;
    searchInRotatedSortedArray.Test();

    SearchForARange searchForARange;
    searchForARange.Test();

    SearchInsertPosition searchInsertPosition;
    searchInsertPosition.Test();
}

// list

void LeetCodeList() {
    AddTwoNumbers addTwoNumbers;
    addTwoNumbers.Test();

    RemoveNthNodeFromEnd removeNthNodeFromEnd;
    removeNthNodeFromEnd.Test();

    MergeTwoSortedLists mergeTwoSortedLists;
    mergeTwoSortedLists.Test();

    MergeKSortedLists mergeKSortedLists;
    mergeKSortedLists.Test();

    SwapNodesInPairs swapNodesInPairs;
    swapNodesInPairs.Test();

    ReverseNodesInkGroup reverseNodesInkGroup;
    reverseNodesInkGroup.Test();
}

// math

void LeetCodeMath() {
    ReverseInteger reverseInteger;
    reverseInteger.Test();

    PalindromeNumber palindromeNumber;
    palindromeNumber.Test();

    Integer2Roman integer2Roman;
    integer2Roman.Test();

    Roman2Integer roman2Integer;
    roman2Integer.Test();

    DivideTwoIntegers divideTwoIntegers;
    divideTwoIntegers.Test();
}

// string

void LeetCodeString() {
    LongestSubstring longestSubstring;
    longestSubstring.Test();

    LongestPalindromicSubstring longestPalindromicSubstring;
    longestPalindromicSubstring.Test();

    ZigZagConversion zigZagConversion;
    zigZagConversion.Test();

    String2Integer string2Integer;
    string2Integer.Test();

    RegularExpressionMatching regularExpressionMatching;
    regularExpressionMatching.Test();

    LongestCommonPrefix longestCommonPrefix;
    longestCommonPrefix.Test();

    LetterCombinationsOfPhoneNumber letterCombinationsOfPhoneNumber;
    letterCombinationsOfPhoneNumber.Test();

    ValidParentheses validParentheses;
    validParentheses.Test();

    GenerateParentheses generateParentheses;
    generateParentheses.Test();

    ImplementStrStr implementStrStr;
    implementStrStr.Test();

    SubstringaWithConcatenationAllWords substringaWithConcatenationAllWords;
    substringaWithConcatenationAllWords.Test();

    LongestValidParentheses longestValidParentheses;
    longestValidParentheses.Test();

}

void LeetCode() {
    LeetCodeArray();
    //    LeetCodeList();
    //    LeetCodeMath();
    //    LeetCodeString();
}

/**
 * main 函数
 * para:    argc
 * para:    argv
 * return:  int, 0 is ok, other is abnormal
 */
int main(int argc, char** argv) {
    LeetCode();
    return 0;
}

