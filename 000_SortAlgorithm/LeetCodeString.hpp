/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LeetCodeString.hpp
 * Author: xuwei.huang
 *
 * Created on 2018年3月7日, 下午7:37
 */

#ifndef LEETCODESTRING_HPP
#define LEETCODESTRING_HPP

#include "Common.h"

#include <algorithm>
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

// 3. Longest Substring Without Repeating Characters
// topics: hash table, two pointers, string

/*
 * Given a string, find the length of the longest substring without repeating characters.
 * 
 * Examples:
 * 
 * Given "abcabcbb", the answer is "abc", which the length is 3.
 * 
 * Given "bbbbb", the answer is "b", with the length of 1.
 * 
 * Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 */
class LongestSubstring {
public:

    int lengthOfLongestSubstring(string s) {
        vector<int> dict(256, -1);
        int maxLen = 0, start = -1;
        for (int i = 0; i != s.length(); i++) {
            if (dict[s[i]] > start)
                start = dict[s[i]]; // 如果有重复的字符, 那么start的位置就是上一个重复的字符位置
            dict[s[i]] = i; // 保存每个字符最新出现的位置
            maxLen = std::max(maxLen, i - start);
        }
        return maxLen;
    }

    void Test() {
        string str = "adggdwegdasga";
        cout << "字符串: " << str << ", 最长字串长度: " << lengthOfLongestSubstring(str) << endl;
    }
};


// 5. Longest Palindromic Substring
// topics: string, dynamic programming

/*
 * Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
 * 
 * Example:
 * Input: "babad"
 * Output: "bab"
 * Note: "aba" is also a valid answer.
 * 
 * Example:
 * Input: "cbbd"
 * Output: "bb"
 */

class LongestPalindromicSubstring {
public:

    string longestPalindrome(string s) {
        /*
         * dp[j][i] = true                              i = j
         *          = str[i] == str[j]                  i - j = 1
         *          = str[i] == str[j] && dp[j+1][i-1]  i-j > 1
         * 选中一个字符, 向两侧扩展, n*n 复杂度
         */
        if (s.length() < 2) {
            return s;
        }
        int max_len = 1, min_start = 0;
        for (int i = 0; i < s.length() - 1; i++) {
            int len1 = extend(s, i, i);
            int len2 = extend(s, i, i + 1);
            int tempLen = len1 > len2 ? len1 : len2;
            if (max_len < tempLen) {
                max_len = tempLen;
                min_start = (len1 > len2) ? (i - len1 / 2) : (i - len2 / 2 + 1);
            }
        }
        return s.substr(min_start, max_len);
    }

    int extend(string & s, int i, int j) {
        while (i >= 0 && j < s.length()) {
            if (s[i] != s[j])
                break;
            i--;
            j++;
        }
        return j - i - 2 + 1;
    }

    string longestPalindrome1(string s) {
        if (s.length() < 2) {
            return s;
        }

        int minStart = 0, maxLen = 1;
        for (int i = 0; i < s.size();) {
            if (s.size() - i < maxLen / 2)
                break;
            int j = i, k = i;
            while (k < s.size() - 1 && s[k + 1] == s[k])
                ++k; // 过滤中间的重叠位置. aba , abba. 奇数: j == k, 偶数: k = j + 1;
            i = k + 1; // 下一次循环位置

            while (k < s.size() - 1 && j > 0 && s[k + 1] == s[j - 1]) {
                j--; // 向两侧扩展
                k++;
            }

            int newLen = k - j + 1;
            if (newLen > maxLen) {
                maxLen = newLen;
                minStart = j;
            }
        }
        return s.substr(minStart, maxLen);
    }

    void Test() {
        cout << "longestPalindrome: " << longestPalindrome("aaaaaaaaaaaaaaaaaabcaaaaaaaaaaaaaaaaa") << endl;
        cout << "longestPalindrome1: " << longestPalindrome1("aaaaaaaaaaaaaaaaaabcaaaaaaaaaaaaaaaaa") << endl;
    }
};


// 6. ZigZag Conversion
// Topics: String

/*
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)
 * 
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * And then read line by line: "PAHNAPLSIIGYIR"
 * Write the code that will take a string and make this conversion given a number of rows:
 * 
 * string convert(string text, int nRows);
 * convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
 */

class ZigZagConversion {
public:

    string convert(string s, int numRows) {
        int size = s.size();
        if (size <= numRows || numRows < 2)
            return s;
        int totalCircu = numRows + (numRows - 2);
        string *strings = new string[numRows];
        for (int i = 0; i < size; i++) {
            int nowTotalPos = i % totalCircu;
            int nowRow = 0;
            if (nowTotalPos > numRows - 1) {
                // 注意这里的算法逻辑. 画图更清晰. numRows是行数, 需要换算为行的下标, 所以-1. 另外折向时需要在-1;
                nowRow = (numRows - 1 - 1) - (nowTotalPos) % numRows;
            }
            else {
                nowRow = nowTotalPos % numRows;
            }
            strings[nowRow].push_back(s[i]);
            cout << strings[nowRow] << endl;
        }
        string result;
        for (int i = 0; i < numRows; i++) {
            result.append(strings[i]);
        }
        return result;
    }

    string betterConvert(string s, int numRows) {
        if (s.size() <= numRows || numRows < 2)
            return s;
        string *strings = new string[numRows];
        int row = 0;
        int step = 1;
        for (int i = 0; i < s.size(); i++) {
            if (0 == row) {
                step = 1;
            }
            if (row == numRows - 1) {
                step = -1;
            }
            strings[row].push_back(s[i]);
            row += step;
        }
        string result;
        for (int i = 0; i < numRows; i++) {
            result.append(strings[i]);
        }
        return result;
    }

    void Test() {
        string testStr = "ABCDEF";
        cout << "TestZigZagConversion: " << convert(testStr, 4) << endl;
        cout << "TestZigZagConversion: " << betterConvert(testStr, 4) << endl;
    }
};


// 8. String to Integer (atoi)
// Topics: math, string

/*
 * Implement atoi to convert a string to an integer.
 * 
 * Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.
 * 
 * Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.
 * 
 * Requirements for atoi:
 * The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.
 * The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.
 * If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.
 * If no valid conversion could be performed, a zero value is returned. If the correct value is out of the range of representable values, INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
 */

class String2Integer {
public:

    int myAtoi(string str) {
        if ("" == str) {
            return 0;
        }
        int len = str.length();
        bool isPositive = true;

        int i = 0;
        while (' ' == str[i]) {
            i++;
        }
        if ('+' == str[i]) {
            i++;
            isPositive = true;
        }
        else if ('-' == str[i]) {
            i++;
            isPositive = false;
        }

        long long sum = 0;
        for (; i < len && str[i] >= '0' && str[i] <= '9'; i++) {
            if (isPositive) {
                sum = sum * 10 + str[i] - 48;
                if (sum > INT_MAX)
                    return INT_MAX;
            }
            else {
                sum = sum * 10 - (str[i] - 48);
                if (sum < INT_MIN)
                    return INT_MIN;
            }
        }

        return sum;
    }

    void Test() {
        string str = "9223372036854775809";
        cout << "String2Integer: " << myAtoi(str) << endl;
    }
};

// 10. Regular Expression Matching
// Topics: string, dynamic programming, backtracking

/*
 * Implement regular expression matching with support for '.' and '*'.
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
 * The matching should cover the entire input string (not partial).
 * 
 * The function prototype should be:
 * bool isMatch(const char *s, const char *p)
 * 
 * Some examples:
 * isMatch("aa","a") -> false
 * isMatch("aa","aa") -> true
 * isMatch("aaa","aa") -> false
 * isMatch("aa", "a*") -> true
 * isMatch("aa", ".*") -> true
 * isMatch("ab", ".*") -> true
 * isMatch("aab", "c*a*b") → true
 */

class RegularExpressionMatching {
public:

    bool isMatch(string s, string p) {
        // this is too hard
    }
};



// 14. Longest Common Prefix
// Topics: string

/*
 * Write a function to find the longest common prefix string amongst an array of strings.
 */

class LongestCommonPrefix {
public:

    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty())
            return "";
        if(strs.size() == 1){
            return strs[0];
        }
        string minStr = strs[0];
        int suffix = 0;
        for (int i = 1; i < strs.size() - 1; i++) {
            if (strs[i].length() < minStr.length()) {
                minStr = strs[i];
                suffix = i;
            }
        }
        string pre = "";
        for (int i = 0; i < minStr.length(); i++) {
            for (int j = 0; j < strs.size(); j++) {
                if (j == suffix) {
                    continue;
                }
                if (minStr[i] != strs[j][i]) {
                    return pre;
                }
            }
            pre = minStr.substr(0, i+1);
        }
        return pre;
    }

    void Test() {
        string arrs[] = {"a", "b"};
        vector<string> vecStr(arrs, arrs+sizeof(arrs)/sizeof(string));
        cout << "longestCommonPrefix: "<< longestCommonPrefix(vecStr) << endl;
    }
};

#endif /* LEETCODESTRING_HPP */

