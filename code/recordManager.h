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
#include "millionNode.h"

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
    void getM();
    void createTree();
    void fillNextLayer(int ilayer);
    void initTopNode();
    void fillLastLayer();
    void fillNode(MNODE *pNode);
    bool isSubNode(int iNode,MNODE *pNode);
    void changeBy01();
    void calculateMinRoad();
    int  getNodeWeight(MNODE *pNode);
    
    static recordManager* Instance();
    std::vector<MRECORD*> recordArr;
    std::vector<MRECORD*> resultArr;
    std::vector<int>      mArr;
    int itotalp;
    int iChemicalCount;
    int iTotalnum;
    std::vector<MNODE *> layerFillNodeArr;//当前要填充层的所有节点
    
    MNODE topNode;//顶点
};

#define RecordMag recordManager::Instance()

#endif /* defined(__airticket__recordManager__) */
