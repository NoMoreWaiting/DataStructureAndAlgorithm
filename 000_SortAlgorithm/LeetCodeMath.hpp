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


// 9. Palindrome Number
// Topics: math

/*
 *Determine whether an integer is a palindrome. Do this without extra space.
 *
 *Some hints:
 *Could negative integers be palindromes? (ie, -1)
 *If you are thinking of converting the integer to string, note the restriction of using extra space.
 *You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?
 *There is a more generic way of solving this problem.
 */

class PalindromeNumber {
public:

    bool isPalindrome(int x) {
        if (x < 0 || (x != 0 && x % 10 == 0)) {
            return false;
        }
        int reverse = 0;
        while (x > reverse) {
            reverse = reverse * 10 + x % 10;
            x = x / 10;
        }
        return (x == reverse || x == reverse / 10);
    }

    void Test() {
        int test = 123454321;
        cout << "PalindromeNumber: " << isPalindrome(test) << endl;
    }
};


// 12. Integer to Roman
// Topics: math, string

/*
 *Given an integer, convert it to a roman numeral.
 *Input is guaranteed to be within the range from 1 to 3999.
 */

class Integer2Roman {
public:

    string intToRoman(int num) {
        // 1, 5, 10分界. 1可以重复3次表示3, 第四次需要加在5, 10的左侧表示减1. 增加一个分界
        // C++中的定义, 看中运算符的优先级, 先结合[], 表示是一个数组, int 表示存储的元素是 int 类型
        static int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        // M 1000
        // D 500
        // C 100
        // L 50
        // X 10
        // V 5
        // I 1
        static string strings[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        string romanStr;
        for (int i = 0; i < sizeof (values) / sizeof (int); i++) {
            while (num >= values[i]) {
                num -= values[i]; // 依次相减
                romanStr.append(strings[i]);
            }
        }
        return romanStr;
    }

    string betterIntToRoman(int num) {
        // 将个十百千位上的数字表示完毕, 整除可得倍数
        //                       1000  2000   3000   
        static string M[] = {"", "M", "MM", "MMM"}; // 罗马数字在此后使用上划线, 表示扩大1000倍, 然后表示所有的数
        //                        100  200   300     400   500   600   700    800      900 
        static string C[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
        //                        10   20     30     40    50    60    70     80       90  
        static string X[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
        //                        1    2      3      4     5     6     7      8        9  
        static string I[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
        
        return M[num/1000] + C[num%1000/100] +X[num%100/10] + I[num%10];
    }

    void Test() {
        int num = 3459;
        cout << "intToRoman: " << intToRoman(num) << endl;
        cout << "betterIntToRoman: " << betterIntToRoman(num) << endl;
    }
};


#endif /* LEETCODEMATH_HPP */

