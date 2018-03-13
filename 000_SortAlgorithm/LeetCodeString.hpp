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
    
    void Test(){
        string str = "adggdwegdasga";
        cout << "字符串: " << str << ", 最长字串长度: " << lengthOfLongestSubstring(str) << endl;
    }
};


#endif /* LEETCODESTRING_HPP */

