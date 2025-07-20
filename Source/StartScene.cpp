//
//  StartScene.cpp
//  testproj
//
//  Created by Anurag Khugshal on 14/07/25.
//
#include "ui/UIButton.h"
#include "ui/CocosGUI.h"
#include "StartScene.h"
#include "MainScene.h"
#include "BotDriver.h"


using namespace ax;

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    
    auto startButton = ui::Button::create();
    
    startButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    startButton->setTitleText("Play with Friend");
   
    startButton->setTitleFontSize(40);

    startButton->addClickEventListener([](Object* sender) {
        printf("change event fired");
        auto dir = Director:: getInstance();
        auto ms = MainScene:: create();
        ms->setGameDriver( new GameDriver());
        dir->replaceScene(ms);
        
    });
    
    auto startButton1 = ui::Button::create();
    
    startButton1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 300));

    startButton1->setTitleText("Play with Bot");
   
    startButton1->setTitleFontSize(40);

    startButton1->addClickEventListener([](Object* sender) {
        printf("change event fired");
        auto dir = Director:: getInstance();
        auto ms = MainScene:: create();
        ms->setGameDriver( new BotDriver());
        dir->replaceScene(ms);
        
    });
    
//    startButton->addTouchEventListener([](Object* sender, ui::Widget::TouchEventType type){
//        switch(type) {
//            case ui::Widget::TouchEventType::BEGAN:
//                 
//                break;
//            case ui::Widget::TouchEventType::MOVED:
//            
//                break;
//            case ui::Widget::TouchEventType::ENDED:
//                
//                break;
//            case ui::Widget::TouchEventType::CANCELED:
//                
//                break;
//            default:
//                break;
//        }
//    });


    this->addChild(startButton);
   


    


    this->addChild(startButton1);
    
    return true;
}

StartScene::StartScene() {
    // Your constructor code here (or empty)
}

StartScene::~StartScene() {
    // Cleanup if necessary
}


