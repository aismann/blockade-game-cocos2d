//
//  NumericEditBox.cpp
//  HelloCpp
//
//  Created by Bimba on 2024-04-28.
//

#include "NumericEditBox.hpp"

NumericEditBox::Delegate::Delegate(int min_clamp_value, int max_clamp_value):
    _max_clamp_value(max_clamp_value),_min_clamp_value(min_clamp_value){
    
}
NumericEditBox::Delegate::~Delegate(){
    
}
void NumericEditBox::Delegate::editBoxEditingDidBegin(EditBox *edit_box){
    
}
void NumericEditBox::Delegate::editBoxTextChanged(EditBox *edit_box, const std::string &text){
    
}
void NumericEditBox::Delegate::editBoxEditingDidEndWithAction(EditBox *edit_box, EditBoxEndAction action){
    try{
        edit_box->setText(std::to_string(
             (int)cocos2d::clampf(
                  std::stoi(edit_box->getText()),
                  _min_clamp_value,
                  _max_clamp_value))
                .c_str());
    }catch(std::invalid_argument &e){
        edit_box->setText(std::to_string((_max_clamp_value + _min_clamp_value)/2).c_str());
    }
    
}
void NumericEditBox::Delegate::editBoxReturn(EditBox *edit_box){
    
}
void NumericEditBox::Delegate::editBoxEditingDidEnd(EditBox *edit_box){
    
}

NumericEditBox::NumericEditBox(int min_clamp_value, int max_clamp_value):
        p_delegate{new Delegate(min_clamp_value, max_clamp_value)}{
            setDelegate(p_delegate);
}

NumericEditBox *NumericEditBox::create(const cocos2d::Size &size, int min_clamp_value, int max_clamp_value, int init_value){
    NumericEditBox *edit_box = new (std::nothrow) NumericEditBox(min_clamp_value, max_clamp_value);

    if(edit_box != nullptr && edit_box->initWithSizeAndTexture(size, "EditBox.png")){
        edit_box->autorelease();
        edit_box->setText(std::to_string(init_value).c_str());
        edit_box->setInputMode(InputMode::DECIMAL);
        edit_box->setFontSize(variables::FONT_SIZE);
    }else{
        CC_SAFE_DELETE(edit_box);
    }
    
    return edit_box;
}
