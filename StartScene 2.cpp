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
#include "../BotDriver.h"
#include "../BotAlgorithms/MiniMaxBot.h"
#include "../WebSocketManager.h"
#include "../ServerDriver.h"
#include "../Login.h"
#include "Waiting.h"


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
        GameDriver* gd = new GameDriver();
        ms->setGameDriver( gd);
        dir->replaceScene(ms);
//        auto dir = Director:: getInstance();
//        auto ms = MainScene:: create();
//        BotAlgorithm* minimax =  new MiniMax(6,7);
//        GameDriver* gd  = new BotDriver(minimax);
//        ms->setGameDriver( gd);
//        dir->replaceScene(ms);
        
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
        GameDriver* gd  = new BotDriver(minimax);
        ms->setGameDriver( gd);
        dir->replaceScene(ms);
        
    });
    
    auto startButton2 = ui::Button::create("direction-sign.png");
    
    startButton2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 -150));

    startButton2->setTitleText("Play with Server");
   
    startButton2->setTitleFontSize(40);

    startButton2->addClickEventListener([this](Object* sender) {
        printf("change event fired");
      
        auto loginpopup = LoginPopup::createWithPlayer(0);
        loginpopup->onSubmitCallback = [this] (std::string name){
            auto dir = Director:: getInstance();
            auto ms = MainScene:: create();
            Player* p = new Player(name, name, 0);
            GameDriver* sd = new ServerDriver(true, p);
            this->gd = sd;
            ms->setGameDriver(this->gd);
            
            dir->replaceScene(ms);
        };
        this->addChild(loginpopup,3);
        vector<int> data = {0,0};
        
       
        
    });
  auto startButton3 = ui::Button::create("direction-sign.png");
    
    startButton3->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 450));

    startButton3->setTitleText("Multiplayer Game");
   
    startButton3->setTitleFontSize(40);

    startButton3->addClickEventListener([this](Object* sender) {
        printf("change event fired");
      
        auto loginpopup = LoginPopup::createWithPlayer(0);
        loginpopup->onSubmitCallback = [this] (std::string name){
            Player* p = new Player(name, name, 0);
            auto sd = new ServerDriver(false,p);
            this->gd = sd;
            WaitingPopup * wp = WaitingPopup:: create();
            this->addChild(wp, 4 );
        };
        this->addChild(loginpopup,3);
          
//
        
    });
    EventListenerCustom* startMatch = Director::getInstance()->getEventDispatcher()->addCustomEventListener("startMatch", [this](EventCustom* e){
        auto data =  *(static_cast<vector<int>*>(e->getUserData()));
        int start = data[0];
        int turn  = data[1];
        auto dir = Director:: getInstance();
        auto ms = MainScene:: create();
        this->gd->turn = start;
        ms->setGameDriver(this->gd);
        dir->replaceScene(ms);
//        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("switchTurn", &start);
        
        
      
        
        
        
           
        
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


