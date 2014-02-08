//
//  main.cpp
//  airticket
//
//  Created by lazybone on 11/6/13.
//  Copyright (c) 2013 lazybone. All rights reserved.
//

#include "inputFile.h"
#include "stdio.h"

#include <iostream>
using namespace std;

int main(int argc, const char * argv[])
{
//    if (argc != 2) {
//        printf("parameter error!");
//        
//        return 0;
//    }
//  
//    InputF->readFile(argv[1]);
    InputF->readFile("/Users/lishiming/Desktop/million/testfile/t1.txt");
    InputF->putoutResult();
    
    return 0;
}




