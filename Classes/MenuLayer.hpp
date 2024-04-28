//
//  MenuLayer.hpp
//  HelloCpp
//
//  Created by Bimba on 2024-04-28.
//

#ifndef MenuLayer_hpp
#define MenuLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "NumericEditBox.hpp"
#include "Global.hpp"

USING_NS_CC;

class NumericEditBoxDelegate : public ui::EditBoxDelegate {
public:
    enum class EditBoxEndAction {
        UNKNOWN,
        TAB_TO_NEXT,
        TAB_TO_PREVIOUS,
        RETURN
    };
    NumericEditBoxDelegate(){
        
    }
    ~NumericEditBoxDelegate() {}

    /**
     * This method is called when an edit box gains focus after keyboard is shown.
     * @param editBox The edit box object that generated the event.
     */
    void editBoxEditingDidBegin(ui::EditBox* /*editBox*/);

    /**
     * This method is called when an edit box loses focus after keyboard is hidden.
     * @param editBox The edit box object that generated the event.
     * @deprecated Use editBoxEditingDidEndWithAction() instead to receive reason for end
     */
    CC_DEPRECATED_ATTRIBUTE  void editBoxEditingDidEnd(ui::EditBox* /*editBox*/);

    /**
     * This method is called when the edit box text was changed.
     * @param editBox The edit box object that generated the event.
     * @param text The new text.
     */
    void editBoxTextChanged(ui::EditBox* /*editBox*/, const std::string& /*text*/);

    /**
     * This method is called when the return button was pressed or the outside area of keyboard was touched.
     * @param editBox The edit box object that generated the event.
     */
    void editBoxReturn(ui::EditBox* editBox);

    /**
     * This method is called when an edit box loses focus after keyboard is hidden.
     * @param editBox The edit box object that generated the event.
     * @param type The reason why editing ended.
     */
    void editBoxEditingDidEndWithAction(ui::EditBox* /*editBox*/, EditBoxEndAction /*action*/);
};


class MenuLayer : public cocos2d::Layer{
public:
    virtual bool init();
    static MenuLayer *create(const cocos2d::Size &menu_size);
    void setStartEventCallback(std::function<void(int,int,int)> fun);
    std::function<void(int,int,int)> onStartCallback = NULL;

    
    CREATE_FUNC(MenuLayer);
private:
    void onStart();
    cocos2d::Menu *_menu;
    cocos2d::LayerColor *_background_color;
};

#endif /* MenuLayer_hpp */
