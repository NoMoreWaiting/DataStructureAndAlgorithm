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

#include "ClassicAlgorithmAnalysis.hpp"


using namespace std;


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

    ClassicAlgorithmAnalysis();

    return 0;
}

