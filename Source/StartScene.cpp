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
#include "../TestScene.h"
#include "BotDriver.h"
#include "../BotAlgorithms/MiniMaxBot.h"
#include "../WebSocketManager.h"
#include "../ServerDriver.h"


using namespace ax;

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
//    auto bgColor = LayerColor::create(Color4B(224,43,126,255)); // RGBA
//    this->addChild(bgColor, -1);
    auto background = Sprite::create("menubg.png");
    if (background)
    {
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        // Scale the background to fit the screen
        float scaleX = visibleSize.width / background->getContentSize().width;
        float scaleY = visibleSize.height / background->getContentSize().height;
        background->setScale(scaleX, scaleY);
        this->addChild(background, -1);
    }
    
    auto startButton = ui::Button::create("direction-sign.png");
    
    startButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2+450));

    startButton->setTitleText("Play with Friend");
   
    startButton->setTitleFontSize(40);

    startButton->addClickEventListener([](Object* sender) {
        printf("change event fired");
        auto dir = Director:: getInstance();
        auto ms = MainScene:: create();
        
        ms->setGameDriver( new GameDriver());
        dir->replaceScene(ms);
        
    });
    
    auto startButton1 = ui::Button::create("direction-sign.png");
    
    startButton1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 +150));

    startButton1->setTitleText("Play with Bot");
   
    startButton1->setTitleFontSize(40);

    startButton1->addClickEventListener([](Object* sender) {
        printf("change event fired");
        auto dir = Director:: getInstance();
        auto ms = MainScene:: create();
        BotAlgorithm* minimax =  new MiniMax(6,7);
        ms->setGameDriver( new BotDriver(minimax));
        dir->replaceScene(ms);
        
    });
    
    auto startButton2 = ui::Button::create("direction-sign.png");
    
    startButton2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 -150));

    startButton2->setTitleText("Play with Server");
   
    startButton2->setTitleFontSize(40);

    startButton2->addClickEventListener([this](Object* sender) {
        printf("change event fired");
        auto dir = Director:: getInstance();
        auto ms = MainScene:: create();
//        BotAlgorithm* minimax =  new MiniMax(6,7);
//        ms->setGameDriver( new BotDriver(minimax));
        auto sd = new ServerDriver(true);
        ms->setGameDriver(sd);
        dir->replaceScene(ms);
        
    });
  auto startButton3 = ui::Button::create("direction-sign.png");
    
    startButton3->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 450));

    startButton3->setTitleText("Multiplayer Game");
   
    startButton3->setTitleFontSize(40);

    startButton3->addClickEventListener([this](Object* sender) {
        printf("change event fired");
      
//        BotAlgorithm* minimax =  new MiniMax(6,7);
//        auto ms = MainScene:: create();
//        ms->setGameDriver( new BotDriver(minimax));
        auto sd = new ServerDriver(false);
        this->gd = sd;
//        ms->setGameDriver(sd);
//        dir->replaceScene(ms);
        
    });
    EventListenerCustom* startMatch = Director::getInstance()->getEventDispatcher()->addCustomEventListener("startMatch", [this](EventCustom* e){
        auto data =  *(static_cast<vector<int>*>(e->getUserData()));
        int turn = data[0];
        auto dir = Director:: getInstance();
        auto ms = MainScene:: create();
        this->gd->turn = turn;
        ms->setGameDriver(this->gd);
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
    this->addChild(startButton2);
    this->addChild(startButton3);
    
    return true;
}

StartScene::StartScene() {
    // Your constructor code here (or empty)
}

StartScene::~StartScene() {
    // Cleanup if necessary
}


