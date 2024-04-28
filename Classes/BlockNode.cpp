//
//  BlockNode.cpp
//  HelloCpp
//
//  Created by Bimba on 2024-04-28.
//

#include "BlockNode.hpp"

USING_NS_CC;

bool BlockNode::init(){
    if(!DrawNode::init()){
        return false;
    }
    
    return true;
}
BlockNode *BlockNode::create(const cocos2d::Size &node_size, const cocos2d::Color4F &color){
    BlockNode *node = BlockNode::create();
    PhysicsBody *body = PhysicsBody::createBox(node_size,
                                               PhysicsMaterial(1,0,0));
    body->setRotationEnable(false);
    body->setVelocity(Vec2(0,variables::SPEED));
    
    node->setContentSize(node_size);
    node->setPhysicsBody(body);
    node->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    node->drawSolidRect(Vec2::ZERO, node_size, Color4F(color));
    node->drawRect(Vec2::ZERO, node_size, Color4F::BLACK);
    
    return node;
}
void BlockNode::disable(){
    getPhysicsBody()->setEnabled(false);
//    setOpacity(0);
}
