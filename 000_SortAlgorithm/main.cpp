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
 */

#include <iostream>

#include "InsertSort.hpp"
#include "ShellSort.hpp"
#include "SelectSort.hpp"


using namespace std;

/**
 * main 函数
 * para:    argc
 * para:    argv
 * return:  int, 0 is ok, other is abnormal
 */
int main(int argc, char** argv) {

    TestInsertSort();
    TestBInsertSort();
    TestDoubleInsertSort();
    TestShellSort();
    TestSelectSort();
    TestBinarySelectSort();
    
    return 0;
}

