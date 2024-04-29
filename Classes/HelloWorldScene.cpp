/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


Scene* HelloWorld::createScene()
{
    Scene *scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,variables::GRAVITY));
    auto layer = HelloWorld::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    
    scene->addChild(layer);
    
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
   
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Size menu_layer_size = Size(visibleSize.width, 100);
    MenuLayer *menu = MenuLayer::create(menu_layer_size);
    menu->setPositionY(visibleSize.height - menu->getContentSize().height);
   
    this->addChild(menu);
    
    Size game_layer_size = Size(visibleSize.width, visibleSize.height - menu->getContentSize().height);
    GameLayer *game = GameLayer::create();
    game->setContentSize(game_layer_size);
    game->runWith(variables::INIT_HEIGHT, variables::INIT_WIDTH,variables::INIT_COLOR);

    
    this->addChild(game);

    menu->setStartEventCallback(std::bind(&GameLayer::runWith, game, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    EventListenerCustom *screen_listener = EventListenerCustom::create(GLViewImpl::EVENT_WINDOW_RESIZED, [game](EventCustom *event){
        Size window_size = Director::getInstance()->getOpenGLView()->getFrameSize();
        Size resolution_size = Director::getInstance()->getVisibleSize();

    });
    
    _eventDispatcher->addEventListenerWithFixedPriority(screen_listener, 1);
#endif


    return true;
}

void HelloWorld::play(Ref *pSender){
    
}
void HelloWorld::setColours(int c){
    this->colours = c;
}
void HelloWorld::setWidth(int w){
    this->width = w;
}
void HelloWorld::setHeight(int h){
    this->height = h;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
