/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LeetCodeMath.hpp
 * Author: xuwei.huang
 *
 * Created on 2018年3月27日, 下午8:41
 */

#ifndef LEETCODEMATH_HPP
#define LEETCODEMATH_HPP
#include "Common.h"

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;


// 7. Reverse Integer
// Topics: math

/*
 *Given a 32-bit signed integer, reverse digits of an integer.
 *
 *Input: 123
 *Output:  321
 *
 *Input: -123
 *Output: -321
 *
 *Note:
 *Assume we are dealing with an environment which could only hold integers within the 32-bit signed integer range. For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
 */

class ReverseInteger {
public:

    int reverse(int x) {
        long long total = 0;
        while (x) {
            total = total * 10 + x % 10;
            x /= 10;
            if (total > INT_MAX || total < INT_MIN) {
                return 0;
            }
        }
        return total;
    }

    void Test() {
        int test = -1234555555;
        cout << "ReverseInteger: " << reverse(test) << endl;
    }
};


#endif /* LEETCODEMATH_HPP */

