//
//  PlayerLeft.cpp
//  testproj
//
//  Created by Anurag Khugshal on 02/08/25.
//


#include "axmol.h"
#include "PlayerLeft.h"
#include "Scenes/StartScene.h"
using  namespace ax;
PlayerLeftPopup* PlayerLeftPopup :: create (){
   
    
    PlayerLeftPopup* wp =  new (std::nothrow)  PlayerLeftPopup();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = Label::createWithSystemFont(
        "Player Left" ,
        "Arial", 60);
    label->setPosition(visibleSize.width/2, visibleSize.height*0.8f);
    label->setTextColor(Color4B::WHITE);
    wp->addChild(label);
    
    auto lens = Sprite::create("face.png");  // replace with your actual image
    lens->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.55f));
    wp->addChild(lens, 5);

    
    
    auto findingLabel = Label::createWithSystemFont("Player left the match :(", "Arial", 36);
    findingLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.45f));
    findingLabel->setTextColor(Color4B::WHITE);
    wp->addChild(findingLabel);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    wp->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, wp);

    auto backbtn = ui::Button:: create("replay.png");
    backbtn->addClickEventListener ([](Object* sender){
        auto dir = Director:: getInstance();
        auto ss = StartScene:: create();
        dir->replaceScene(ss);
    });
    backbtn->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.2f));
    backbtn->setScale(0.5f);
    wp->addChild(backbtn,4);
    
    if (wp && wp->initWithColor(Color4B(0, 0, 0, 180))) {
          wp->autorelease();
          return wp;
    }
    return NULL;

}
