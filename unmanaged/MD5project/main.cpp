/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on 2017年3月9日, 下午3:37
 */

#include <cstdlib>
#include <string>
#include "MessageDigestAlgorithm5.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    MD5 test;
    string password = "0123456789";
    cout << password << endl;
    test.update(password,10);
    cout << password << endl;

    
    
    return 0;
}

