//
//  NumericEditBox.hpp
//  HelloCpp
//
//  Created by Bimba on 2024-04-28.
//

#ifndef NumericEditBox_hpp
#define NumericEditBox_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Global.hpp"

class NumericEditBox : public cocos2d::ui::EditBox{
public:
    class Delegate : public cocos2d::ui::EditBoxDelegate{
    public:
        inline Delegate(int,int);
        ~Delegate();
        
        void editBoxEditingDidBegin(cocos2d::ui::EditBox* /*editBox*/);

        CC_DEPRECATED_ATTRIBUTE  void editBoxEditingDidEnd(cocos2d::ui::EditBox* /*editBox*/);

        void editBoxTextChanged(cocos2d::ui::EditBox* /*editBox*/, const std::string& /*text*/);

        void editBoxReturn(cocos2d::ui::EditBox* editBox);

        void editBoxEditingDidEndWithAction(cocos2d::ui::EditBox* /*editBox*/, EditBoxEndAction /*action*/);
        
    private:
        int _max_clamp_value;
        int _min_clamp_value;
    };
    
    NumericEditBox(int,int);
    
    
    static NumericEditBox *create(const cocos2d::Size&,int,int,int);
    
//    CREATE_FUNC(NumericEditBox);
private:
    Delegate *p_delegate;
    
};


#endif /* NumericEditBox_hpp */
