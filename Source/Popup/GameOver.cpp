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
    
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180))){// semi-transparent background
        return false;
    }
    
    
    
        
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    
 


    // Label
    auto label = Label::createWithSystemFont(
        "Player " + std::to_string(playerNumber) + " WON!!",
        "Arial", 60);
    label->setPosition(visibleSize.width/2, visibleSize.height*0.8f);
    label->setTextColor(Color4B::WHITE);
    this->addChild(label);

    // Close button (X)
    auto closeBtn = ui::Button::create("direction-sign.png");
    auto closeBtn1 = ui::Button::create("direction-sign.png");
    
    closeBtn->setScale(0.5f);
    closeBtn1->setScale(0.5f);
   
    
    
    auto trophy = Sprite::create("trophy.png");
    trophy->setPosition(visibleSize/2); // your target screen position
    trophy->setScale(0);              // start invisible
    this->addChild(trophy, 10);       // make sure it's on top

    auto appear = ScaleTo::create(0.3f, 1.2f);
    auto settle = ScaleTo::create(0.1f, 1.0f);
    auto shake = Sequence::create(
        MoveBy::create(0.05f, Vec2(5, 5)),
        MoveBy::create(0.05f, Vec2(-10, -10)),
        MoveBy::create(0.05f, Vec2(5, 5)),
        nullptr
    );
    this->runAction(shake);
    auto sequence = Sequence::create(appear, settle, nullptr);
    
    trophy->runAction(sequence);
    

    
    float margin = 10.0f;

    closeBtn->setPosition(Vec2(visibleSize.width * 0.25f, visibleSize.height*0.2f));
    closeBtn1->setPosition(Vec2(visibleSize.width * 0.75f, visibleSize.height*0.2f));
    
    closeBtn->setTitleText("Rematch");
    closeBtn->setTitleFontSize(60);
    closeBtn1->setTitleText("Stats");
    closeBtn1->setTitleFontSize(60);

    closeBtn->addClickEventListener([this,gd](Object*){
        gd->rematch();
        this->removeFromParent(); // Close the popup
    });
    
    closeBtn1->addClickEventListener([this,gd](Object*){
        gd->stats();
        this->removeFromParent(); // Close the popup
    });

    this->addChild(closeBtn);
    this->addChild(closeBtn1);

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
