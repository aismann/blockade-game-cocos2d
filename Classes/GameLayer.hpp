//
//  GameLayer.hpp
//  HelloCpp
//
//  Created by Bimba on 2024-04-28.
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BlockNode.hpp"


class GameLayer :  public cocos2d::Layer{
public:
    //Events
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    
    //Creation
    static GameLayer *create(cocos2d::Size visibleSize, int rows = 8, int cols = 8, int colours = 3);
    virtual bool init();
    //Style
    void setBackground(cocos2d::Color3B color);
    
    //Block
    BlockNode *getBlockByIndex(int row, int col);
    void removeBlockAndNeighbors(int row, int col, int neighbors);
    
    //Checking
    bool hasMoves();
    
    
    
    
    //Logic
    void clear();
    void prepare(int rows, int cols, int colours);
    void generateMap();
    void fillMap();
    void resizeToFitAvaliableSpace();
    
    void runWith(int rows, int cols, int colours);
    void finish();
    
    CREATE_FUNC(GameLayer);
private:
    int _rows;
    int _cols;
    int _colours;
    int _edge_size;
    
    cocos2d::LayerColor *_background_color = nullptr;
    cocos2d::Node *_blocks_container = nullptr;
    cocos2d::Node *_edge_node = nullptr;
    
    std::vector<std::vector<GLuint>> _map;
    
    void updateMap();
    
    
    
    int getNeighborsByColor(int row, int col);
    bool hasEnoughNeighbors(int neighbors);
    
    
};

#endif /* GameLayer_hpp */
