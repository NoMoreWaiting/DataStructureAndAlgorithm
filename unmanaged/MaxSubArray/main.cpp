/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        main.cpp
 * Author:      xuwei.huang
 * Describe:    
 *              这里的下标记录有个问题, 那就是如果 有多个相同和的子数组 , 那么之后显示第一个子数组
 * Created on   2017年7月3日, 上午11:00
 */

#include <iostream>

using namespace std;

bool getMaxArray(int arr[], unsigned int size, int &sum, unsigned int &begin, unsigned int &end)
{
    if((NULL == arr) || (size == 0))
        return false;
    int curSum = 0;
    int maxSum = 0;
    int tempBegin = 0;
    for(unsigned int i = 0; i < size; ++i)
    {
        curSum += arr[i];
        if(curSum > maxSum)
        {
            maxSum = curSum;
            begin = tempBegin;
            end = i;
        }
        if(curSum < 0)
        {
            curSum = 0;
            tempBegin = i + 1;
        }
    }

    if(0 == maxSum)
    {
        maxSum = arr[0];
        for(unsigned int i = 0; i < size; ++i)
        {
            if(arr[i] > maxSum)
            {
                maxSum = arr[i];
                begin = i;
                end = i;
            }
        }
    }
    sum = maxSum;
    return true;
}

/**
 * main 函数
 * para:    argc
 * para:    argv
 * return:  int, 0 is ok, other is abnormal
 */
int main()
{
    int arr[8] = {1, -2, 7, -4, -3, 4, 3, -5};
    unsigned int size = sizeof(arr) / sizeof(int);
    unsigned int begin = 0;
    unsigned int end = 0;
    int sum = 0;
    getMaxArray(arr, size, sum, begin, end);

    cout << "子数组和的最大值为: " << sum << endl;

    cout << "子数组为: " << endl;
    for(unsigned int i = begin; i < end + 1; ++i)
    {
        cout << arr[i] << " ,  ";
    }
    cout << "\n";
    cout << "这里的下标记录有个问题, 那就是如果 有多个相同和的子数组 , 那么之后显示第一个子数组" << endl;
    cout << "Bye";

    return 0;
}

