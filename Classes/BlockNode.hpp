//
//  BlockNode.hpp
//  HelloCpp
//
//  Created by Bimba on 2024-04-28.
//

#ifndef BlockNode_hpp
#define BlockNode_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Global.hpp"

class BlockNode : public cocos2d::DrawNode{
public:
    static BlockNode *create(const cocos2d::Size &node_size, const cocos2d::Color4F &color);
    
    virtual bool init();
    
    void disable();
    
    CREATE_FUNC(BlockNode);
};

#endif /* BlockNode_hpp */
