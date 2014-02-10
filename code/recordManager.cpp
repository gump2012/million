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
}

void recordManager::getM()
{
    int iTotalnum = (int)recordArr.size();
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
    std::vector<MNODE *>::iterator itresultLayerEnd = layerFillNodeArr.end();
    for (std::vector<MNODE *>::iterator resultit = layerFillNodeArr.begin();
         resultit != itresultLayerEnd; ++resultit) {
        MNODE *mresult = *resultit;
        
        fillNode(mresult);
    }
    
    moveToNextLayer();
}

void recordManager::moveToNextLayer()
{
    tempNodeArr.clear();
    std::vector<MNODE *>::iterator itresultend = layerFillNodeArr.end();
    for (std::vector<MNODE *>::iterator resultit = layerFillNodeArr.begin();
         resultit != itresultend; ++resultit) {
        MNODE *mresult = *resultit;
        if (mresult->subNodeArr.size() != 0) {
            std::vector<MNODE *>::iterator itresultend = mresult->subNodeArr.end();
            for (std::vector<MNODE *>::iterator resultit = mresult->subNodeArr.begin();
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
    
    layerFillNodeArr.clear();
    tempNodeArr.clear();
    std::vector<MNODE *>::iterator itopend = topNode.subNodeArr.end();
    for (std::vector<MNODE *>::iterator resultit = topNode.subNodeArr.begin();
         resultit != itopend; ++resultit) {
        MNODE *mresult = *resultit;
        layerFillNodeArr.push_back(mresult);
    }
}

void recordManager::fillLastLayer()
{
    tempNodeArr.clear();
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
        if (isSubNode(mresult, pNode)) {
            MNODE *subnode = new MNODE;
            subnode->topNode = pNode;
            subnode->iWeight = mresult->p;
            subnode->iEdge = mresult->m;
            subnode->iNode = mresult->c2;
            
            pNode->subNodeArr.push_back(subnode);
        }
    }
}

bool recordManager::isSubNode(MRECORD *record, MNODE *pNode)
{
    bool bSub = true;
    
    if (pNode->iNode == record->c1) {
        MNODE *top = pNode->topNode;
        while (top != NULL) {
            if (top->iNode == record->c2) {
                bSub = false;
                break;
            }
            
            top = top->topNode;
        }
    }
    else
    {
        bSub = false;
    }
    
    
    return bSub;
}

void recordManager::calculateMinRoad()
{
    MNODE *minNode = NULL;
    itotalp = 0;
    std::vector<MNODE *>::iterator itresultLayerEnd = layerFillNodeArr.end();
    for (std::vector<MNODE *>::iterator resultit = layerFillNodeArr.begin();
         resultit != itresultLayerEnd; ++resultit) {
        MNODE *mNodeResult = *resultit;
        int iTempTotalW = getNodeWeight(mNodeResult);
        if (minNode == NULL) {
            minNode = mNodeResult;
            itotalp = iTempTotalW;
        }
        else if (itotalp > iTempTotalW)
        {
            minNode = mNodeResult;
            itotalp = iTempTotalW;
        }
    }
    
    mArr.clear();
    MNODE *top = minNode;
    while (top) {
        if (top->iEdge != -1) {
            mArr.push_back(top->iEdge);
        }
        top = top->topNode;
    }
    
    std::sort(mArr.begin(), mArr.end(),Csort());
}

int recordManager::getNodeWeight(MNODE *pNode)
{
    int iTotal = 0;
    MNODE *top = pNode;
    while (top->topNode) {
        iTotal += top->iWeight;
        top = top->topNode;
    }
    
    return iTotal;
}