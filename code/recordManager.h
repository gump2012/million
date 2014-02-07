//
//  recordManager.h
//  airticket
//
//  Created by lazybone on 11/6/13.
//  Copyright (c) 2013 lazybone. All rights reserved.
//

#ifndef __airticket__recordManager__
#define __airticket__recordManager__

#include <iostream>
#include <vector>

#include "millionRecord.h"

class recordManager
{
public:
    recordManager();
    ~recordManager();
    
    void calculateResult();
    void getResult();
    bool isSolution(std::vector<MRECORD*>& sarr,const MRECORD* sr);
    void getMin(std::vector<MRECORD*>& sarr);
    void createResult(int *markarr);
    
    static recordManager* Instance();
    std::vector<MRECORD*> recordArr;
    std::vector<MRECORD*> resultArr;
    std::vector<int>      mArr;
    int itotalp;
    int iChemicalCount;
    int iTotalnum;
    int iTotalroad;
};

#define RecordMag recordManager::Instance()

#endif /* defined(__airticket__recordManager__) */
