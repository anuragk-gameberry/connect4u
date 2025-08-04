//
//  Login.h
//  testproj
//
//  Created by Anurag Khugshal on 30/07/25.
//

#pragma once

#include "axmol.h"
#include "Drivers/GameDriver.h"
#include "ui/CocosGUI.h"

class LoginPopup : public ax::LayerColor, ax::ui::EditBoxDelegate  {
public:
    GameDriver* gd;
    static LoginPopup* createWithPlayer(int playerNumber);
    bool initWithPlayer(int playerNumber);
    void editBoxReturn(ax::ui::EditBox* editBox) ;
    std::function<void(std::string name)> onSubmitCallback;
};
