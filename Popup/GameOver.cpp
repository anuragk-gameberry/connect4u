//
//  GameOver.cpp
//  testproj
//
//  Created by Anurag Khugshal on 18/07/25.
//

#include "../Popup/GameOver.h"
#include "ui/CocosGUI.h"


USING_NS_AX;

bool PlayerPopup::initWithPlayer(int playerNumber, GameDriver* gd) {
    
    if (!LayerColor::initWithColor(Color4B(224,43,126,150))){// semi-transparent background
        return false;
    }
    
        
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    Vec2 center = visibleSize / 2;

    // Popup background
    auto bg = LayerColor::create(Color4B(224,43,126, 255), 500, 400);
    
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
    auto closeBtn = ui::Button::create("but.png");
    
    closeBtn->setScale9Enabled(true); // Required for resizing via content size
    closeBtn->setContentSize(Size(visibleSize.width / 3, visibleSize.height / 5));
   
    auto bgSize = bg->getContentSize();
    auto bgOrigin = bg->getPosition();

    float margin = 10.0f;

    closeBtn->setPosition(Vec2(
        bgOrigin.x + bgSize.width - closeBtn->getContentSize().width / 2 - margin,
        bgOrigin.y  + 35 + margin
    ));
    
    closeBtn->setTitleText("Rematch");
    closeBtn->setTitleFontSize(24);

    closeBtn->addClickEventListener([this,gd](Object*){
        gd->rematch();
        this->removeFromParent(); // Close the popup
    });
    this->addChild(closeBtn);

    return true;
}

PlayerPopup* PlayerPopup::createWithPlayer(int playerNumber,GameDriver* gd ) {
    PlayerPopup* ret = new (std::nothrow) PlayerPopup();
    if (ret && ret->initWithPlayer(playerNumber,gd)) {
        ret->autorelease();
        return ret;
    }
    AX_SAFE_DELETE(ret);
    return nullptr;
}
