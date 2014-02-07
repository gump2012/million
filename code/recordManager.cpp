//
//  recordManager.cpp
//  airticket
//
//  Created by lazybone on 11/6/13.
//  Copyright (c) 2013 lazybone. All rights reserved.
//

#include "recordManager.h"

#include <algorithm> 

class Csort
{
public:
    
    bool operator () (int a,int b) const
    {
        return a < b;
    };
};

recordManager::recordManager()
:itotalp(0),
iTotalroad(0)
{
    
}

recordManager::~recordManager()
{
    
}

recordManager* recordManager::Instance()
{
    static recordManager rm;
    return &rm;
}

void recordManager::calculateResult()
{
    //get m
    iTotalnum = (int)recordArr.size();
    int ibeginm = 2;
    int iTotalBym = 2;
    if (iTotalnum > 2) {
        while (iTotalnum != iTotalBym) {
            ibeginm++;
            iTotalBym = iTotalBym + (ibeginm - 1) * 2;
        }
    }
    
    iChemicalCount = ibeginm;
    
    //01 change
    int *tempNum = new int[iTotalnum];
    for (int i = 0; i < iTotalnum; i++) {
        if (i < iChemicalCount) {
            tempNum[i] = 1;
        } else {
            tempNum[i] = 0;
        }
    }
    
    createResult(tempNum);
    int iNodeEnd = iTotalnum - iChemicalCount;
    
    bool flag = false;
    do {
        int pose = 0;
        int sum = 0;
        
        for (int i = 0; i < (iTotalnum - 1); i++) {
            if (tempNum[i] == 1 && tempNum[i + 1] == 0) {
                tempNum[i] = 0;
                tempNum[i + 1] = 1;
                pose = i;
                
                break;
            }
        }
        createResult(tempNum);
        
        for (int i = 0; i < pose; i++) {
            if (tempNum[i] == 1)
                sum++;
        }
        
        for (int i = 0; i < pose; i++) {
            if (i < sum)
                tempNum[i] = 1;
            else
                tempNum[i] = 0;
        }
        
        flag = false;
        for (int i = iNodeEnd; i < iTotalnum; i++) {
            
            if (tempNum[i] == 0)
                flag = true;
            
        }
    } while (flag);
    
    delete []tempNum;
    
    getResult();
}

void recordManager::getResult()
{
    std::vector<MRECORD *>::iterator itresultend = resultArr.end();
    for (std::vector<MRECORD *>::iterator resultit = resultArr.begin();
         resultit != itresultend; ++resultit) {
        MRECORD *mresult = *resultit;
        mArr.push_back(mresult->m);
    }
    
    std::sort(mArr.begin(), mArr.end(),Csort());
}

bool recordManager::isSolution(std::vector<MRECORD*>& sarr,const MRECORD* sr)
{
    bool bsolution = true;
    std::vector<MRECORD *>::iterator itsend = sarr.end();
    for (std::vector<MRECORD *>::iterator it = sarr.begin();it != itsend; ++it) {
        MRECORD *ms = *it;
        if (ms->c1 != sr->c1 && ms->c2 != sr->c2) {
            continue;
        }
        else
        {
            bsolution = false;
            break;
        }
    }
    
    return bsolution;
}

void recordManager::getMin(std::vector<MRECORD*>& sarr)
{
    static int inum = 0;
    if (inum == 0) {
        resultArr = sarr;
        std::vector<MRECORD *>::iterator itresultend = resultArr.end();
        for (std::vector<MRECORD *>::iterator resultit = resultArr.begin();
             resultit != itresultend; ++resultit) {
            MRECORD *mresult = *resultit;
            itotalp += mresult->p;
        }
        
        inum++;
    }
    else
    {
        int istotal = 0;
        std::vector<MRECORD *>::iterator itresultend = sarr.end();
        for (std::vector<MRECORD *>::iterator resultit = sarr.begin();
             resultit != itresultend; ++resultit) {
            MRECORD *mresult = *resultit;
            istotal += mresult->p;
        }
        
        if (istotal < itotalp) {
            resultArr = sarr;
            itotalp = istotal;
        }
    }
}

void recordManager::createResult(int *markarr)
{
    std::vector<MRECORD*> solutionArr;
    bool isRight = true;
    int igroup = 0;
    for (int i = 0; i < iTotalnum; i++) {
        if (markarr[i] == 1) {
            igroup++;
            MRECORD *sr = recordArr.at(i);
            if (isSolution(solutionArr, sr)) {
                solutionArr.push_back(sr);
            }
            else
            {
                isRight = false;
                break;
            }
            
            if (igroup == iChemicalCount) {
                break;
            }
        }
    }
    
    if (isRight) {
        iTotalroad++;
        
        printf("\n");
        std::vector<MRECORD *>::iterator itresultend = solutionArr.end();
        for (std::vector<MRECORD *>::iterator resultit = solutionArr.begin();
             resultit != itresultend; ++resultit) {
            MRECORD *mresult = *resultit;
            printf("%d  ",mresult->m);
        }
        printf("   %d\n",iTotalroad);
        
        getMin(solutionArr);
    }
}