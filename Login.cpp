//
//  Login.cpp
//  testproj
//
//  Created by Anurag Khugshal on 30/07/25.
//


#include "../Login.h"
#include "ui/CocosGUI.h"


USING_NS_AX;

bool LoginPopup::initWithPlayer(int playerNumber) {

    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180))){
        return false;
    }
    
        
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    
    auto label = Label::createWithSystemFont(
        "Player Details" + std::to_string(playerNumber),
        "Arial", 60);
    label->setPosition(visibleSize.width/2, visibleSize.height*0.8f);
    label->setTextColor(Color4B::WHITE);
    this->addChild(label);
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
    
    auto editBox = ui::EditBox::create(Size(300,60), "button.png");
    editBox->setPosition(Vec2(visibleSize.width/2, visibleSize.height/4));
    editBox->setFontColor(Color3B::BLACK);
    editBox->setPlaceHolder("Enter your name");
    editBox->setPlaceholderFontColor(Color3B::GRAY);
    editBox->setMaxLength(20);
    editBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    editBox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
    editBox->setDelegate(this);

    // Add it to the scene/layer
   

    this->addChild(editBox);
    
    // Block touches from reaching layers below
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);  // This is the key line

    touchListener->onTouchBegan = [](Touch* touch, Event* event) {
        return true; // Consume all touches
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

LoginPopup* LoginPopup::createWithPlayer(int playerNumber) {
    LoginPopup* ret = new (std::nothrow) LoginPopup();
    if (ret && ret->initWithPlayer(playerNumber)) {
        ret->autorelease();
        return ret;
    }
    AX_SAFE_DELETE(ret);
    return nullptr;
}

void LoginPopup::editBoxReturn(ui::EditBox* editBox)  {
    std::string text = editBox->getText();
    AXLOG("User entered: %s", text.c_str());
    this->removeFromParentAndCleanup(true);
    this->onSubmitCallback(text);
   
    
}
