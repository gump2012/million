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
:itotalp(0)
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
    getM();
    createTree();
    calculateMinRoad();
    
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
        getMin(solutionArr);
    }
}

void recordManager::getM()
{
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
}

void recordManager::createTree()
{
    initTopNode();
    
    for (int i = iChemicalCount - 1; i > 1; --i) {
        fillNextLayer(iChemicalCount - i);
    }
    
    fillLastLayer();
}

void recordManager::fillNextLayer(int ilayer)
{
    layerFillNodeArr.clear();
    std::vector<MNODE *> tempNodeArr;
    std::vector<MNODE *>::iterator itresultend = topNode.subNodeArr.end();
    for (std::vector<MNODE *>::iterator resultit = topNode.subNodeArr.begin();
         resultit != itresultend; ++resultit) {
        MNODE *mresult = *resultit;
        layerFillNodeArr.push_back(mresult);
    }
    
    for (int i = 1; i < ilayer; ++i) {
        tempNodeArr.clear();
        std::vector<MNODE *>::iterator itresultend = layerFillNodeArr.end();
        for (std::vector<MNODE *>::iterator resultit = layerFillNodeArr.begin();
             resultit != itresultend; ++resultit) {
            MNODE *mresult = *resultit;
            if (mresult->subNodeArr.size() != 0) {
                std::vector<MNODE *>::iterator itresultend = layerFillNodeArr.end();
                for (std::vector<MNODE *>::iterator resultit = layerFillNodeArr.begin();
                     resultit != itresultend; ++resultit) {
                    MNODE *mresult = *resultit;
                    tempNodeArr.push_back(mresult);
                }
            }
        }
        
        layerFillNodeArr.clear();
        
        std::vector<MNODE *>::iterator itresultTempEnd = tempNodeArr.end();
        for (std::vector<MNODE *>::iterator resultit = tempNodeArr.begin();
             resultit != itresultTempEnd; ++resultit) {
            MNODE *mresult = *resultit;
            layerFillNodeArr.push_back(mresult);
        }
    }
    
    std::vector<MNODE *>::iterator itresultLayerEnd = layerFillNodeArr.end();
    for (std::vector<MNODE *>::iterator resultit = layerFillNodeArr.begin();
         resultit != itresultLayerEnd; ++resultit) {
        MNODE *mresult = *resultit;
        fillNode(mresult);
    }
}

void recordManager::initTopNode()
{
    topNode.topNode = NULL;
    topNode.iWeight = -1;
    topNode.iEdge = -1;
    topNode.iNode = 1;
    
    std::vector<MRECORD *>::iterator itresultend = recordArr.end();
    for (std::vector<MRECORD *>::iterator resultit = recordArr.begin();
         resultit != itresultend; ++resultit) {
        MRECORD *mresult = *resultit;
        if (mresult->c1 == topNode.iNode) {
            MNODE *subnode = new MNODE;
            subnode->topNode = &topNode;
            subnode->iWeight = mresult->p;
            subnode->iEdge = mresult->m;
            subnode->iNode = mresult->c2;
            
            topNode.subNodeArr.push_back(subnode);
        }
    }
}

void recordManager::fillLastLayer()
{
    std::vector<MNODE *> tempNodeArr;
    std::vector<MNODE *>::iterator itresultLayerEnd = layerFillNodeArr.end();
    for (std::vector<MNODE *>::iterator resultit = layerFillNodeArr.begin();
         resultit != itresultLayerEnd; ++resultit) {
        MNODE *mNodeResult = *resultit;
        std::vector<MRECORD *>::iterator itresultend = recordArr.end();
        for (std::vector<MRECORD *>::iterator resultit = recordArr.begin();
             resultit != itresultend; ++resultit) {
            MRECORD *mresult = *resultit;
            
            if (mresult->c1 == mNodeResult->iNode && mresult->c2 == 1) {
                MNODE *subnode = new MNODE;
                subnode->topNode = mNodeResult;
                subnode->iWeight = mresult->p;
                subnode->iEdge = mresult->m;
                subnode->iNode = mresult->c2;
                
                mNodeResult->subNodeArr.push_back(subnode);
                tempNodeArr.push_back(subnode);
            }
        }
    }
    
    layerFillNodeArr.clear();
    
    std::vector<MNODE *>::iterator itresultTempEnd = tempNodeArr.end();
    for (std::vector<MNODE *>::iterator resultit = tempNodeArr.begin();
         resultit != itresultTempEnd; ++resultit) {
        MNODE *mresult = *resultit;
        layerFillNodeArr.push_back(mresult);
    }
}

void recordManager::fillNode(MNODE *pNode)
{
    std::vector<MRECORD *>::iterator itresultend = recordArr.end();
    for (std::vector<MRECORD *>::iterator resultit = recordArr.begin();
         resultit != itresultend; ++resultit) {
        MRECORD *mresult = *resultit;
        if (isSubNode(mresult->c1, pNode)) {
            MNODE *subnode = new MNODE;
            subnode->topNode = pNode;
            subnode->iWeight = mresult->p;
            subnode->iEdge = mresult->m;
            subnode->iNode = mresult->c2;
            
            pNode->subNodeArr.push_back(subnode);
        }
    }
}

bool recordManager::isSubNode(int iNode, MNODE *pNode)
{
    bool bSub = true;
    
    MNODE *top = pNode->topNode;
    while (top != NULL) {
        if (top->iNode == iNode) {
            bSub = false;
            break;
        }
        
        top = top->topNode;
    }
    
    return bSub;
}

void recordManager::changeBy01()
{
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
}

void recordManager::calculateMinRoad()
{
    MNODE *minNode = NULL;
    int itotalWeight = 0;
    std::vector<MNODE *>::iterator itresultLayerEnd = layerFillNodeArr.end();
    for (std::vector<MNODE *>::iterator resultit = layerFillNodeArr.begin();
         resultit != itresultLayerEnd; ++resultit) {
        MNODE *mNodeResult = *resultit;
        int iTempTotalW = getNodeWeight(mNodeResult);
        if (minNode == NULL) {
            minNode = mNodeResult;
            itotalWeight = iTempTotalW;
        }
        else if (itotalWeight > iTempTotalW)
        {
            minNode = mNodeResult;
            itotalWeight = iTempTotalW;
        }
    }
    
    mArr.clear();
    MNODE *top = minNode;
    while (top) {
        mArr.push_back(top->iEdge);
        top = top->topNode;
    }
}

int recordManager::getNodeWeight(MNODE *pNode)
{
    int iTotal = 0;
    MNODE *top = pNode;
    while (top) {
        iTotal += top->iWeight;
        top = top->topNode;
    }
    
    return iTotal;
}