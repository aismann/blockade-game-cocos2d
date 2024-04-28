//
//  MenuLayer.cpp
//  HelloCpp
//
//  Created by Bimba on 2024-04-28.
//

#include "MenuLayer.hpp"

USING_NS_CC;


void NumericEditBoxDelegate::editBoxTextChanged(ui::EditBox *edit_box, const std::string &text){
    
}
void NumericEditBoxDelegate::editBoxEditingDidBegin(ui::EditBox *edit_box){
    
}
void NumericEditBoxDelegate::editBoxEditingDidEndWithAction(ui::EditBox *edit_box, EditBoxEndAction action){
    
}
void NumericEditBoxDelegate::editBoxReturn(ui::EditBox *edit_box){
    
}
void NumericEditBoxDelegate::editBoxEditingDidEnd(ui::EditBox *edit_box){
    
}
void MenuLayer::setStartEventCallback(std::function<void(int,int,int)> fun){
    onStartCallback = fun;
}

void MenuLayer::onStart(){
    if(onStartCallback == NULL) return;
    
    try{
        MenuItem *width_item = _menu->getChildByName<MenuItem*>("width_item");
        MenuItem *height_item = _menu->getChildByName<MenuItem*>("height_item");
        MenuItem *color_item = _menu->getChildByName<MenuItem*>("color_item");
        
        NumericEditBox* width_edit_box = dynamic_cast<NumericEditBox*>(width_item->getChildren().at(0));
        NumericEditBox* height_edit_box = dynamic_cast<NumericEditBox*>(height_item->getChildren().at(0));
        NumericEditBox* color_edit_box = dynamic_cast<NumericEditBox*>(color_item->getChildren().at(0));
        
        onStartCallback(std::stoi(height_edit_box->getText()),
                        std::stoi(width_edit_box->getText()),
                        std::stoi(color_edit_box->getText()));
        
    }catch(const std::exception &exc){
        
    }
}
bool MenuLayer::init(){
    if(!Layer::init()){
        return false;
    }
    return true;
}

MenuItemLabel *createMenuItemLabel(const char *title, const ccMenuCallback &callback){
    MenuItemLabel *item = MenuItemLabel::create(Label::createWithTTF(title, variables::FONT_FILE, variables::FONT_SIZE), callback);
   
    if(callback == NULL){
        item->setDisabledColor(item->getColor());
        item->setEnabled(false);
    }
    
    return item;
}

MenuLayer *MenuLayer::create(const cocos2d::Size &menu_size){
    MenuLayer *layer = MenuLayer::create();
    
    Size edit_box_size = Size(100,40);
    
    layer->_background_color = cocos2d::LayerColor::create(Color4B(100,0,100,100));

    MenuItemLabel *height_label_item = createMenuItemLabel(u8"Высота", NULL);
    MenuItemLabel *width_label_item = createMenuItemLabel(u8"Ширина", NULL);
    MenuItemLabel *color_label_item = createMenuItemLabel(u8"Цвета", NULL);

    NumericEditBox *ui_height_edit_box = NumericEditBox::create(
                                                    edit_box_size,
                                                    variables::MIN_HEIGHT,
                                                    variables::MAX_HEIGHT,
                                                    variables::INIT_HEIGHT);
    ui_height_edit_box->setPosition(edit_box_size/2);
    
    MenuItem *edit_height_item = MenuItem::create();
    edit_height_item->setContentSize(edit_box_size);
    edit_height_item->addChild(ui_height_edit_box);
    edit_height_item->setName("height_item");
    
   
    NumericEditBox *ui_width_edit_box = NumericEditBox::create(
                                                   edit_box_size,
                                                   variables::MIN_WIDTH,
                                                   variables::MAX_WIDTH,
                                                   variables::INIT_WIDTH);
    ui_width_edit_box->setPosition(edit_box_size/2);
    MenuItem *edit_width_item = MenuItem::create();
    edit_width_item->setContentSize(edit_box_size);
    edit_width_item->addChild(ui_width_edit_box);
    edit_width_item->setName("width_item");

    
    NumericEditBox *ui_color_edit_box = NumericEditBox::create(edit_box_size,variables::MIN_COLOR,variables::MAX_COLOR,variables::INIT_COLOR);
    ui_color_edit_box->setPosition(edit_box_size/2);
    
    MenuItem *edit_color_item = MenuItem::create();
    edit_color_item->setContentSize(edit_box_size);
    edit_color_item->addChild(ui_color_edit_box);
    edit_color_item->setName("color_item");
    
    MenuItemLabel *start_button_item = createMenuItemLabel(u8"Cтарт", CC_CALLBACK_0(MenuLayer::onStart, layer));
    start_button_item->setName("start_item");

    
    layer->_menu = Menu::create(
                              height_label_item, edit_height_item,
                              width_label_item,edit_width_item,
                              color_label_item,edit_color_item,
                              start_button_item,NULL);
    layer->_menu->alignItemsHorizontally();
    
    layer->addChild(layer->_background_color, 1);
    layer->addChild(layer->_menu ,2);
    layer->setContentSize(menu_size);


    layer->_background_color->setContentSize(menu_size);
    layer->_menu->setPositionY(menu_size.height/2);
    
    return layer;
}
