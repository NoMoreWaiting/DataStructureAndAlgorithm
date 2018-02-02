/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RadixSort.hpp
 * Author: xuwei.huang
 *
 * Created on 2018年1月13日, 下午6:30
 * 
 * 参考: http://blog.csdn.net/k346k346/article/details/45576137
 * 
 */

#ifndef RADIXSORT_HPP
#define RADIXSORT_HPP

#include "Common.h"


/*
 * 非比较 -- 分配式排序 -- 基数排序
 * 
 * 平均时间复杂度: O(n * k)   k为最大数的位数
 * 最好情况: O(n * k)
 * 最坏情况: O(n * k)
 * 空间复杂度: O(n + k)
 * 排序方式: Out-place
 * 稳定性: 稳定
 * 
 * 基本思想: 它是透过键值的部分信息，将要排序的元素分配至某些“桶”中，藉以达到排序的作用. 基数排序号称线性时间排序算法中性能最好，速度最快的排序算法
 * 
 * 注意要点: 
 * 
 * 改进1: C/C++串行版本
 *
 */


/******************************************************** 
 *函数名称：GetDigitInPos 
 *参数说明：num 一个整形数据 
 *        pos 表示要获得的整形的第pos位数据 
 *说明：   找到num的从低到高的第pos位的数据 
 *********************************************************/
int GetDigitInPos(int num, int pos) {
    int temp = 1;
    for (int i = 0; i < pos - 1; i++)
        temp *= 10;
    return (num / temp) % 10;
}



/******************************************************** 
 *函数名称：RadixSort 
 *参数说明：unorderArray无序数组； 
 *        dataNum无序数据个数 
 *说明：   基数排序 
 *时间复杂度：O(dn),d无序数最大位数，n无序数个数
 *********************************************************/
#define RADIX 10    //整形排序,基数为10,需要十个桶  
#define KEYNUM 10   //关键字位数，这里为整形位数  

void RadixSort(int* unorderArray, int dataNum) {
    int *radixArrays[RADIX]; //分别为0~9基数的存放空间  
    for (int i = 0; i < 10; i++) {
        radixArrays[i] = (int *) malloc(sizeof (int)*(dataNum + 1));
        radixArrays[i][0] = 0; //index为0处记录这组数据的个数  
    }
    for (int pos = 1; pos <= KEYNUM; pos++) //从个位开始入桶并出桶
    {
        for (int i = 0; i < dataNum; i++) //分配过程  
        {
            int num = GetDigitInPos(unorderArray[i], pos);
            int index = ++radixArrays[num][0];
            radixArrays[num][index] = unorderArray[i];
        }
        for (int i = 0, j = 0; i < RADIX; i++)//收集  
        {
            for (int k = 1; k <= radixArrays[i][0]; k++)
                unorderArray[j++] = radixArrays[i][k];
            radixArrays[i][0] = 0; //出桶完毕，复位  
        }
    }
}

void TestRadixSort() {
    int arr[] = {6, 9, 6, 12, 3, 6, 10, 6};
    int len = sizeof (arr) / sizeof (int);
    cout << "排序前: ";
    ShowArr(arr, len);

    RadixSort(arr, len);

    cout << "排序后: ";
    ShowArr(arr, len);
}



#endif /* RADIXSORT_HPP */

