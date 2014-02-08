//
//  millionNode.h
//  million
//
//  Created by lazybone on 2/8/14.
//
//

#ifndef million_millionNode_h
#define million_millionNode_h

typedef struct millionNode
{
    millionNode                 *topNode;//顶点
    int                         iWeight;//权
    int                         iEdge;//边
    std::vector<millionNode*>   subNodeArr;//子结点数组
}MNODE;

#endif
