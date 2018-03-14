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
 *Given a string, find the length of the longest substring without repeating characters.
 *
 *Examples:
 *
 *Given "abcabcbb", the answer is "abc", which the length is 3.
 *
 *Given "bbbbb", the answer is "b", with the length of 1.
 *
 *Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
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
 *Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
 *
 *Example:
 *Input: "babad"
 *Output: "bab"
 *Note: "aba" is also a valid answer.
 *
 *Example:
 *Input: "cbbd"
 *Output: "bb"
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


#endif /* LEETCODESTRING_HPP */

