//
//  GameOver.cpp
//  testproj
//
//  Created by Anurag Khugshal on 18/07/25.
//

#include "../Popup/GameOver.h"
#include "ui/CocosGUI.h"

USING_NS_AX;

bool PlayerPopup::initWithPlayer(int playerNumber) {
    if (!LayerColor::initWithColor(Color4B(224,43,126,150))){// semi-transparent background
        return false;
    }
        
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    Vec2 center = visibleSize / 2;

    // Popup background
    auto bg = LayerColor::create(Color4B(224,43,126, 255), 400, 150);
    
    bg->setPosition(center - bg->getContentSize() / 2);
    this->addChild(bg);


    // Label
    auto label = Label::createWithSystemFont(
        "Player " + std::to_string(playerNumber) + "WON!!",
        "Arial", 28);
    label->setPosition(center);
    label->setTextColor(Color4B::WHITE);
    this->addChild(label);

    // Close button (X)
    auto closeBtn = ui::Button::create("CloseNormal.png", "CloseSelected.png"); // Use your close icons
   
    closeBtn->setPosition(bg->getPosition() + Vec2(bg->getContentSize().width / 2 + 200,
                                                   bg->getContentSize().height / 2 + 75));
    closeBtn->addClickEventListener([this](Object*){
        this->removeFromParent(); // Close the popup
    });
    this->addChild(closeBtn);

    return true;
}

PlayerPopup* PlayerPopup::createWithPlayer(int playerNumber) {
    PlayerPopup* ret = new (std::nothrow) PlayerPopup();
    if (ret && ret->initWithPlayer(playerNumber)) {
        ret->autorelease();
        return ret;
    }
    AX_SAFE_DELETE(ret);
    return nullptr;
}
