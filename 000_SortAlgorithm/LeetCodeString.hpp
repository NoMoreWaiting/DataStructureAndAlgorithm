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
        for (int i = 0; i != (int) s.length(); i++) {
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
        for (int i = 0; i < (int) s.length() - 1; i++) {
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
        while (i >= 0 && j < (int) s.length()) {
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
        for (int i = 0; i < (int) s.size();) {
            if ((int) s.size() - i < maxLen / 2)
                break;
            int j = i, k = i;
            while (k < (int) s.size() - 1 && s[k + 1] == s[k])
                ++k; // 过滤中间的重叠位置. aba , abba. 奇数: j == k, 偶数: k = j + 1;
            i = k + 1; // 下一次循环位置

            while (k < (int) s.size() - 1 && j > 0 && s[k + 1] == s[j - 1]) {
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
        if ((int) s.size() <= numRows || numRows < 2)
            return s;
        string *strings = new string[numRows];
        int row = 0;
        int step = 1;
        for (int i = 0; i < (int) s.size(); i++) {
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
 * isMatch("aab", "c*a*b") -> true
 */

class RegularExpressionMatching {
public:
    static const int FRONT = -1;

    bool isMatchBackTrace(string s, string p) {
        // this is too hard
        return myMatch(s, s.length() - 1, p, p.length() - 1);
    }

    // 递归, 回溯思想
    // 从后往前匹配, 遇到*时前方必有一个字符, 不需要考虑越界问题

    bool myMatch(string& s, int i, string& p, int j) {
        if (j == FRONT) {
            if (i == FRONT)
                return true; // 两个字符串都走完时, 匹配完成, 否则不匹配
            else
                return false;
        }

        if (p[j] == '*') { // '*' 字符分2种情况 存在或者不存在
            if (i > FRONT && (p[j - 1] == '.' || p[j - 1] == s[i]))
                if (myMatch(s, i - 1, p, j)) // 去除目标字符串的一个值, 递归找下一层, 符合情况为匹配到
                    return true;
            return myMatch(s, i, p, j - 2); // X* 已经无法匹配字符串, 去掉'*'以及前一位, 继续匹配 
        }
        if (p[j] == '.' || p[j] == s[i]) // 普通字符, 直接比较
            return myMatch(s, i - 1, p, j - 1);
        return false;
    }

    // DP 动态规划. 二维bool数组寻找真值匹配路径

    bool isMatchDP(string s, string p) {
        int m = s.length(), n = p.length();
        // 加入空串
        vector < vector<bool> > dp(m + 1, vector<bool> (n + 1, false));
        dp[0][0] = true; // 空串一定匹配
        for (int i = 0; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (p[j - 1] == '*')
                    // 需要研究
                    dp[i][j] = dp[i][j - 2] || (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
                else
                    dp[i][j] = i > 0 && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
        return dp[m][n];
    }

    void Test() {
        string target = "aa";
        string source = "aa";
        if (isMatchBackTrace(target, source))
            cout << "isMatchBackTrace: true" << endl;
        else
            cout << "isMatchBackTrace: false" << endl;
        if (isMatchDP(target, source))
            cout << "isMatchDP: true" << endl;
        else
            cout << "isMatchDP: false" << endl;
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
        if (strs.size() == 1) {
            return strs[0];
        }
        string minStr = strs[0];
        int suffix = 0;
        for (int i = 1; i < (int) strs.size() - 1; i++) {
            if (strs[i].length() < minStr.length()) {
                minStr = strs[i];
                suffix = i;
            }
        }
        string pre = "";
        for (int i = 0; i < (int) minStr.length(); i++) {
            for (int j = 0; j < (int) strs.size(); j++) {
                if (j == suffix) {
                    continue;
                }
                if (minStr[i] != strs[j][i]) {
                    return pre;
                }
            }
            pre = minStr.substr(0, i + 1);
        }
        return pre;
    }

    void Test() {
        string arrs[] = {"a", "b"};
        vector<string> vecStr(arrs, arrs + sizeof (arrs) / sizeof (string));
        cout << "longestCommonPrefix: " << longestCommonPrefix(vecStr) << endl;
    }
};



// 17. Letter Combinations of a Phone Number
// Topics: string, backtracking

/*
 * Given a digit string, return all possible letter combinations that the number could represent.
 * 
 * A mapping of digit to letters (just like on the telephone buttons) is given below.
 * 
 * Input:Digit string "23"
 * Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 * Note:
 * Although the above answer is in lexicographical order, your answer could be in any order you want
 */

class LetterCombinationsOfPhoneNumber {
public:
    // 迭代Iterative

    vector<string> letterCombinationsIterative(string digits) {
        vector<string> res;
        if (digits.empty())
            return res;

        static string keys[] = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        res.push_back("");
        for (int i = 0; i < (int) digits.size(); i++) {
            int n = res.size();
            if (digits[i] > '9' || digits[i] < '0')
                break;
            string str = keys[digits[i] - '0'];
            for (int j = 0; j < n; ++j) {
                string tmp = res.front();
                res.erase(res.begin());
                for (int k = 0; k < (int) str.size(); k++) {
                    res.push_back(tmp + str[k]);
                }
            }
        }
        return res;
    }

    // dfs, backtracking 方式

    vector<string> letterCombinationsDFS(string digits) {
        vector<string> res;
        if (digits.empty())
            return res;

        static string keyArr[] = {"0", "1", "abc", "def", "ght", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        static vector<string> dict(keyArr, keyArr + sizeof (keyArr) / sizeof (string));
        DFSImpl(digits, dict, 0, "", res);
        return res;
    }

    void DFSImpl(string digits, vector<string>& dict, int level, string out, vector<string> &res) {
        if (level == (int) digits.size())
            res.push_back(out);
        else {
            if (digits[level] > '9' || digits[level] < '0')
                return;

            string str = dict[digits[level] - '0'];
            for (int i = 0; i < (int) str.size(); i++) {
                out.push_back(str[i]);
                DFSImpl(digits, dict, level + 1, out, res);
                out.pop_back();
            }
        }
    }

    void Test() {
        string str = "a123456";
        vector<string> res;
        cout << "letterCombinationsIterative: " << endl;
        res = letterCombinationsIterative(str);
        ShowVector<string>(res);

        cout << "letterCombinationsDFS: " << endl;
        res = letterCombinationsDFS(str);
        ShowVector<string>(res);
    }
};


// 20. Valid Parentheses
// Topics: string, stack

/*
 * Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 * 
 * The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
 */

class ValidParentheses {
public:

    bool isValid(string s) {
        std::unordered_map<char, char> pareMap;
        pareMap = {
            {']', '['},
            {'}', '{'}
        };
        list<char> stack;
        std::unordered_map<char, char>::iterator iter;
        pareMap.insert(std::pair<char, char>(')', '('));
        for (int i = 0; i < (int) s.length(); i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                stack.push_back(s[i]);
            }
            else if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
                if (*stack.rbegin() == pareMap[s[i]])
                    stack.pop_back();
                else
                    return false;
            }
        }
        if (stack.empty())
            return true;
        return false;
    }

    void Test() {
        string str = "{geg[geg](}";
        if (isValid(str))
            cout << "ValidParentheses: true" << endl;
        else
            cout << "ValidParentheses: false" << endl;
    }
};

// 22. Generate Parentheses
// Topics: string, backtracking

/*
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
 * 
 * For example, given n = 3, a solution set is:
 * 
 * [
 *   "((()))",
 *   "(()())",
 *   "(())()",
 *   "()(())",
 *   "()()()"
 * ]
 */

class GenerateParentheses {
public:

    struct Control {
        int left; // 左侧有几个为配对的"("
        int remain; // 剩余可入队的"("
    };

    vector<string> generateParentheses(int n) {
        vector<string> result;
        Control con;
        con.left = 0;
        con.remain = n;
        Impl("", result, con);
        return result;
    }

    void Impl(string pre, vector<string> &result, Control con) {
        if (con.remain == 0 && con.left == 1) {
            result.push_back(pre + ")");
        }
        else if (con.left == 0) {
            con.left++;
            con.remain--;
            Impl(pre + "(", result, con);
        }
        else if (con.remain >= 0) {
            {
                Control newCon = con;
                newCon.left++;
                newCon.remain--;
                Impl(pre + "(", result, newCon);
            }
            {
                Control newCon = con;
                newCon.left--;
                Impl(pre + ")", result, newCon);
            }
        }
    }

    vector<string> betterGenerateParentheses(int n) {
        vector<string> result;
        helper(result, "", n, n);
        return result;
    }

    /**
     * 
     * @param result  返回结果集
     * @param pre     传过来的前置字符串
     * @param left    剩余多少'('
     * @param right   剩余多少')'
     */
    void helper(vector<string> &result, string pre, int left, int right) {
        if (0 == left && 0 == right) {
            result.push_back(pre);
            return;
        }
        if (left > 0)
            helper(result, pre + "(", left - 1, right);
        if (right > left) // 剩余的')'比'('多才可以插入')', 对于第一次来说, 就是'('先插入
            helper(result, pre + ")", left, right - 1);
    }

    void Test() {
        vector<string> result = generateParentheses(3);
        cout << "generateParentheses: " << endl;
        ShowVector<string>(result);

        result = betterGenerateParentheses(4);
        cout << "betterGenerateParentheses: " << endl;
        ShowVector<string>(result);
    }
};


// 28. Implement strStr()
// Topics: string, two pointers

/*
 * Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
 * 
 * Example 1:
 * Input: haystack = "hello", needle = "ll"
 * Output: 2
 * 
 * Example 2:
 * Input: haystack = "aaaaa", needle = "bba"
 * Output: -1
 * 
 * Clarification:
 * What should we return when needle is an empty string? This is a great question to ask during an interview.
 * For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().
 */

class ImplementStrStr {
public:

    int strStr(string haystack, string needle) {
        if (needle == "")
            return 0;
        int i = 0, j = 0;
        int m = int(haystack.length()), n = int(needle.length());
        for (i = 0; i <= m - n; i++) {
            for (j = 0; j < n && haystack[i + j] == needle[j]; j++) {
            }
            if (j == n)
                return i;
        }
        return -1;
    }

    int strStrKMP(string haystack, string needle) {
        int m = int(haystack.length()), n = int(needle.length());
        if (!n)
            return 0;
        vector<int> lps = kmpProcess(needle);
        for (int i = 0, j = 0; i < m;) {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
            }
            if (j == n) return
                i - j;
            if (i < m && haystack[i] != needle[j]) {
                if (j)
                    j = lps[j - 1]; // 每次j从 next数组中寻找后移位置.(最长前缀后缀公共字串)
                else
                    i++;
            }
        }
        return -1;
    }

    // 计算kmp数组

    vector<int> kmpProcess(string& needle) {
        int n = needle.length();
        vector<int> lps(n, 0);
        for (int i = 1, len = 0; i < n;) { // 从前向后数, 每个字符串的最大前缀后缀公共字串的长度
            if (needle[i] == needle[len])
                lps[i++] = ++len;
            else if (len) // 之前字符的最长字串
                len = lps[len - 1];
            else
                lps[i++] = 0;
        }
        return lps;
    }

    void Test() {
        string str1 = "adbac";
        string str2 = "bac";

        cout << "strStr: " << strStr(str1, str2) << endl;
        cout << "strStrKMP: " << strStrKMP(str1, str2) << endl;
    }
};


#endif /* LEETCODESTRING_HPP */

