//
//  GameLayer.cpp
//  HelloCpp
//
//  Created by Bimba on 2024-04-28.
//

#include "GameLayer.hpp"

USING_NS_CC;


void GameLayer::runWith(int rows, int cols, int colours){
    clear();
    prepare(rows, cols, colours);
    generateMap();
    fillMap();
}

void GameLayer::finish(){
    std::stringstream buffer;
    buffer
        << "На этом все!"
        << std::endl
        << "Осталось: " << _blocks_container->getChildrenCount()
    << " / " << _rows * _cols;
    Label *label = Label::createWithTTF(buffer.str().c_str(), "fonts/arial.ttf", 36);
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    label->setPosition(getContentSize()/2);
    label->setName("finish_view");
    
    this->addChild(label,999);
}
bool GameLayer::onTouchBegan(cocos2d::Touch*, cocos2d::Event*){
    CCLOG("WORK");
    
    return true;
};

void GameLayer::updateMap(){
    for(int col = 0; col < _cols; col++){
        for(int row = 1; row < _rows; row++){
            if(_map[row][col] != 0 && _map[row - 1][col] == 0){
                int k;
                for(k = row; k > 0 && _map[k - 1][col] == 0; k--);
                _map[k][col] = _map[row][col];
                _map[row][col] = 0;
               
            }
        }
    }
}

int GameLayer::getNeighborsByColor(int row, int col){
    int blocks_equals_by_color = 0;
    
    if(row && _map[row - 1][col] == _map[row][col]){
        blocks_equals_by_color |= 1 << 0; //BOTTOM
    }
    if(row < _rows - 1 && _map[row + 1][col] == _map[row][col]){
        blocks_equals_by_color |= 1 << 2; //TOP
    }
    if(col && _map[row][col - 1] == _map[row][col]){
        blocks_equals_by_color |= 1 << 3; //LEFT
    }
    if(col < _cols - 1 && _map[row][col + 1] == _map[row][col]){
        blocks_equals_by_color |= 1 << 1; //RIGHT
    }
    
    return blocks_equals_by_color;
}

void GameLayer::removeBlockAndNeighbors(int row, int col, int neighbors_blocks){
    BlockNode *block_node;
    if(neighbors_blocks & 0b00000001){
        block_node = getBlockByIndex(row - 1, col);
        if(block_node != nullptr){
//            block_node->disable();
//            scheduleOnce([this, block_node](float){_blocks_container->removeChild(block_node);}, 3, "removeChild");
            _blocks_container->removeChild(block_node);
        }
        _map[row - 1][col] = 0;
    }
    if(neighbors_blocks & 0b0000010){
        block_node = getBlockByIndex(row, col + 1);
        if(block_node != nullptr){
//            block_node->disable();
//            scheduleOnce([this, block_node](float){_blocks_container->removeChild(block_node);}, 3, "removeChild");
            _blocks_container->removeChild(block_node);
        }
        _map[row][col + 1] = 0;
    }
    if(neighbors_blocks & 0b0000100){
        block_node = getBlockByIndex(row + 1, col);
        if(block_node != nullptr){
//            block_node->disable();
//            scheduleOnce([this, block_node](float){_blocks_container->removeChild(block_node);}, 3, "removeChild");
            _blocks_container->removeChild(block_node);
        }
        _map[row + 1][col] = 0;
    }
    if(neighbors_blocks & 0b0001000){
        block_node = getBlockByIndex(row, col - 1);
        if(block_node != nullptr){
//            block_node->disable();
//            scheduleOnce([this, block_node](float){_blocks_container->removeChild(block_node);}, 3, "removeChild");
            _blocks_container->removeChild(block_node);
        }
        _map[row][col - 1] = 0;
    }

    block_node = getBlockByIndex(row,col);
    if(block_node != nullptr){
        if(block_node != nullptr){
//            block_node->disable();
//            scheduleOnce([this, block_node](float){_blocks_container->removeChild(block_node);}, 3, "removeChild");
            _blocks_container->removeChild(block_node);
        }
    }
    _map[row][col] = 0;
}
bool GameLayer::hasEnoughNeighbors(int neighbors_blocks){
    int equal_blocks = 0;
    for(int byte = 0; byte < 4; byte++) if((neighbors_blocks >> byte) & 0x01) equal_blocks++;
    return equal_blocks >= 3;
}
bool GameLayer::hasMoves(){
    for(int row = 0; row < _rows; row++){
        for(int col = 0; col < _cols; col++){
            if(_map[row][col] != 0 &&
               hasEnoughNeighbors(getNeighborsByColor(row, col)))
                return true;
        }
    }
    return false;
}
BlockNode *GameLayer::getBlockByIndex(int row, int col){
    for(Node *node : _blocks_container->getChildren()){
        try{
            BlockNode *block_node = dynamic_cast<BlockNode*>(node);
            if((int)std::round(block_node->getPositionX() / _edge_size) == col &&
               (int)std::round(block_node->getPositionY() / _edge_size) == row){
                return block_node;
            }
        }catch(std::bad_cast &err){
            break;
        }
    }
    return nullptr;
}

bool GameLayer::init(){
    if(!Node::init()){
        return false;
    }
    
    _background_color = LayerColor::create();
    _blocks_container = Node::create();
    _edge_node = Node::create();
        
    addChild(_background_color,1);
    addChild(_blocks_container,2);
    addChild(_edge_node,2);
    
    EventListenerMouse *mouse_listener = EventListenerMouse::create();
    mouse_listener->onMouseUp = [=](Event *event){
        
        try{
            EventMouse *mouseEvent = dynamic_cast<EventMouse*>(event);
            Point mousePos = mouseEvent->getLocationInView() - _blocks_container->getPosition();
            
            if(!getBoundingBox().containsPoint(mouseEvent->getLocationInView())) return;
            event->stopPropagation();
            
            int row = (int)std::floor((float)(mousePos.y - getPositionY()) / _edge_size),
                col = (int)std::floor((float)(mousePos.x - getPositionX()) / _edge_size);
            
            if(_map[row][col] == 0) return;
            
            int blocks_equals_by_color = getNeighborsByColor(row, col);
            if(!hasEnoughNeighbors(blocks_equals_by_color)) return;
            removeBlockAndNeighbors(row, col, blocks_equals_by_color);
            updateMap();
            if(!hasMoves()){
                finish();
            }
        }catch(std::bad_cast &err){
            
        }catch(std::out_of_range &err){
            
        }
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouse_listener, this);
    
    return true;
}


void GameLayer::generateMap(){
    srand((unsigned int)time(NULL));
    int i,j;
    
    std::vector<Color4B> colours_container;
    colours_container.resize(_colours);
    for(i = 0; i < _colours; i++){
        cocos2d::Color4B colour = cocos2d::Color4B(rand() % 256, rand() % 256, rand() % 256, 255);
        colours_container[i] = colour;
    }
    
    _map.resize(_rows);
    for(std::vector<GLuint> &l : _map) l.resize(_cols);
    
    for(i = 0; i < _rows; i++){
        for(j = 0; j < _cols; j++){
            cocos2d::Color4B colour = colours_container.at(rand() % _colours);
            
            _map[i][j] = (colour.r << 24) | (colour.g << 16) | (colour.b << 8) | (colour.a);
        }
    }
}

void GameLayer::clear(){
    _blocks_container->removeAllChildren();
    try{
        removeChild(getChildByName<Label*>("finish_view"));
    }catch(std::exception &exc){
        
    }
}

void GameLayer::fillMap(){
    Size avaliable_size = getContentSize();
    _edge_size = std::floor(MIN(avaliable_size.width / _cols, avaliable_size.height / _rows));
    Size block_size = Size(_edge_size, _edge_size);
    Size game_view_size = Size(_edge_size * _cols, _edge_size * _rows);
    
    for(int row = 0; row < _rows; row++){
        for(int col = 0; col < _cols; col++){
            GLuint gl_color = _map.at(row).at(col);
            
            Color4B cc_color = Color4B((gl_color >> 24) & 0xff,
                                       (gl_color >> 16) & 0xff,
                                       (gl_color >> 8) & 0xff,
                                       (gl_color >> 0) & 0xff);
            BlockNode *block_node = BlockNode::create(block_size, Color4F(cc_color));
            block_node->setPosition(Vec2(col * _edge_size, row * _edge_size));
            
            _blocks_container->addChild(block_node);
        }
    }
    PhysicsBody *edge_body = PhysicsBody::createEdgeBox(game_view_size , PhysicsMaterial(),0);
   
    _edge_node->setContentSize(game_view_size);
    _edge_node->setPhysicsBody(edge_body);
    
    _edge_node->setPosition((avaliable_size - game_view_size)/2);
    _blocks_container->setPosition((avaliable_size - game_view_size)/2);
}
void GameLayer::prepare(int rows, int cols, int colours){
    CCASSERT(rows != 0, "Game::update() 'rows' must be greater");
    CCASSERT(cols != 0, "Game::update() 'cols' must be greater");
    
    _rows = rows;
    _cols = cols;
    _colours = colours;
}

void GameLayer::setBackground(cocos2d::Color3B color){
    _background_color->setColor(color);
    _background_color->setOpacity(255);
}
