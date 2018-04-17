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

#include "InsertSort.hpp"
#include "SelectSort.hpp"
#include "SwapSort.hpp"
#include "MergeSort.hpp"
#include "CountSort.hpp"
#include "RadixSort.hpp"
#include "BucketSort.hpp"

#include "LeetCodeArray.hpp"
#include "LeetCodeList.hpp"
#include "LeetCodeMath.hpp"
#include "LeetCodeString.hpp"

#include "ClassicAlgorithmAnalysis.hpp"


using namespace std;

/*
 * 基本的C++算法分为三类：排序算法、树算法、图算法
 * 算法思想有三种：递推、分治、动态规划 以及 贪心算法。
 * 
 * 
 * 常见排序算法一般分为以下几种： 
 * 
 * （1）非线性时间比较类排序：交换类排序（快速排序和冒泡排序）、插入类排序（简单插入排序和希尔排序）、选择类排序（简单选择排序和堆排序）、归并排序（二路归并排序和多路归并排序）；
 * 
 * （2）线性时间非比较类排序：计数排序、基数排序和桶排序。
 * 
 * 
 * 总结： 
 * （1）在比较类排序中，归并排序号称最快，其次是快速排序和堆排序，两者不相伯仲，
 *      但是有一点需要注意，
 *      数据初始排序状态对堆排序不会产生太大的影响，而快速排序却恰恰相反。
 * （2）线性时间非比较类排序一般要优于非线性时间比较类排序，
 *      但前者对待排序元素的要求较为严格，
 *      比如计数排序要求待排序数的最大值不能太大，
 *      桶排序要求元素按照hash分桶后桶内元素的数量要均匀。
 *      线性时间非比较类排序的典型特点是以空间换时间。
 * 
 * 基数排序 vs 计数排序 vs 桶排序
 * 这三种排序算法都利用了桶的概念，但对桶的使用方法上有明显差异：
 *      基数排序：根据键值的每位数字来分配桶
 *      计数排序：每个桶只存储单一键值
 *      桶排序：每个桶存储一定范围的数值
 * 
 */



// 排序算法测试

void SortAlgorithm() {
    TestInsertSort();
    TestBInsertSort();
    TestDoubleInsertSort();
    TestShellSort();
    TestSelectSort();
    TestBinarySelectSort();
    TestHeapSort();
    TestBigHeapSort();
    TestBubbleSort();
    TestBubbleSort1();
    TestBubbleSort2();
    TestBubbleSort3();
    TestBubbleSort4();
    TestQuickSort1Left();
    TestQuickSort1Right();
    TestQuickSort2HoareLeft();
    TestQuickSort2HoareRight();
    TestQuickSort3HoleLeft();
    TestQuickSort3HoleRight();
    TestQuickSort3HoleNoRecursion();
    TestQuickSort4Rand();
    TestQuickSort5TriValue();
    TestMergeSortBinaryWay();
    TestMergeSortBinaryWay1();
    //    TestMultiWayMergeSort();
    TestCountSort();
    TestRadixSort();
    TestBucketSort();
}



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
}

void LeetCode() {
    LeetCodeArray();
    //    LeetCodeList();
    //    LeetCodeMath();
    //    LeetCodeString();
}

void ClassicAlgorithmAnalysis() {
    FullRangeAlgorithm fullRangeAlgorithm;
    fullRangeAlgorithm.Test();

}

/**
 * main 函数
 * para:    argc
 * para:    argv
 * return:  int, 0 is ok, other is abnormal
 */
int main(int argc, char** argv) {

    //    SortAlgorithm();
    LeetCode();
    //    ClassicAlgorithmAnalysis();

    return 0;
}

