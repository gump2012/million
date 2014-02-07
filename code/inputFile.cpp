//
//  inputFile.cpp
//  airticket
//
//  Created by lazybone on 11/6/13.
//  Copyright (c) 2013 lazybone. All rights reserved.
//

#include "inputFile.h"
#include "millionRecord.h"
#include "recordManager.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include "stdio.h"
using namespace std;

inputFile::inputFile()
{
    
}

inputFile::~inputFile()
{
    
}

inputFile* inputFile::Instance()
{
   static inputFile inputf;
    return &inputf;
}

void inputFile::readFile(const char *strpath)
{
    ifstream i_file(strpath,ios::in);
    
    char *pf=new char[1024];
    while (!i_file.eof())
    {
        i_file.getline(pf,1024,'\n');
        int ilen = (int)strlen(pf);
        pf[ilen] = '\0';
        int ipos = 0;
        
        MRECORD *mrec = new MRECORD;
        mrec->m = readM(ipos,pf);
        mrec->c1 = readC(ipos,pf);
        mrec->c2 = readC(ipos, pf);
        mrec->p = readP(ipos, pf);
        
        if(mrec->m != -1)
        {
        	RecordMag->recordArr.push_back(mrec);
        }
    }
    
    RecordMag->calculateResult();
    
    delete []pf;
}

int inputFile::readM(int &ipos,char *str)
{
    int inum = -1;
    while (str[ipos] != '\0') {
        if (str[ipos] == 'M' || str[ipos] == 'm') {
            ipos++;
            inum = readNum(ipos,str);
            break;
        }
        else
        {
            ipos++;
        }
    }
    return inum;
}

int inputFile::readC(int &ipos,char *str)
{
    int inum = -1;
    while (str[ipos] != '\0') {
        if (str[ipos] == 'C' || str[ipos] == 'c') {
            ipos++;
            inum = readNum(ipos,str);
            break;
        }
        else
        {
            ipos++;
        }
    }
    return inum;
}

int inputFile::readP(int &ipos,char *str)
{
    int inum = -1;
    while (str[ipos] != '\0') {
        if (str[ipos] >= '0' && str[ipos] <= '9') {
            inum = readNum(ipos,str);
            break;
        }
        else
        {
            ipos++;
        }
    }
    return inum;
}


int inputFile::readNum(int &ipos,char *str)
{
    int inum = -1;
    char cnumarr[1024] = {'\0'};
    int icnum = 0;
    while (str[ipos] >= '0' && str[ipos] <= '9') {
        cnumarr[icnum++] = str[ipos++];
    }
    
    cnumarr[icnum] = '\0';
    inum = string2int(cnumarr);
    
    return inum;
}

int inputFile::string2int(char *str)
{
    int inum = 0;
    int ilen = (int)strlen(str);
    
    for (int i = 1; i <= ilen; ++i) {
        if (i > 1) {
            int ipower = 1;
            for (int j = 1; j <= i - 1; ++j) {
                ipower *= 10;
            }
            
            inum += (str[ilen - i] - '0') * ipower;
        }
        else
        {
            inum += str[ilen - i] - '0';
        }
    }
    
    return inum;
}

void inputFile::putoutResult()
{
    printf("%d\n",RecordMag->itotalp);
    
    std::vector<int>::iterator itend = RecordMag->mArr.end();
    for (std::vector<int>::iterator it = RecordMag->mArr.begin();
         it != itend; ++it) {
        int m = *it;
        printf("%d ",m);
    }
    
    printf("\n");
}
