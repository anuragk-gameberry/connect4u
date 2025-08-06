//
//  StartScene.cpp
//  testproj
//
//  Created by Anurag Khugshal on 14/07/25.
//
#include "ui/UIButton.h"
#include "ui/CocosGUI.h"
#include "StartScene.h"
#include "Scenes/MainScene.h"
#include "Drivers/BotDriver.h"
#include "../BotAlgorithms/MiniMaxBot.h"
#include "Utils/WebSocketManager.h"
#include "Drivers/ServerDriver.h"
#include "Popup/Login.h"
#include "Popup/Waiting.h"


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
    
    auto friendGameBtn = ui::Button::create("direction-sign.png");
    
    friendGameBtn->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2+450));

    friendGameBtn->setTitleText("Play with Friend");
   
    friendGameBtn->setTitleFontSize(40);

    friendGameBtn->addClickEventListener([](Object* sender) {
        printf("change event fired");
        auto dir = Director:: getInstance();
        auto ms = MainScene:: create();
        GameDriver* gd = new GameDriver(7,6);
        ms->setGameDriver( gd);
        dir->pushScene(ms);
    });
    
    auto botgameBtn = ui::Button::create("direction-sign.png");
    
    botgameBtn->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 +150));

    botgameBtn->setTitleText("Play with Bot");
   
    botgameBtn->setTitleFontSize(40);

    botgameBtn->addClickEventListener([](Object* sender) {
        printf("change event fired");
        auto dir = Director:: getInstance();
        auto ms = MainScene:: create();
//        ms->gameboardgui = std::vector<std::vector<ax::Sprite*>>(7);
        BotAlgorithm* minimax =  new MiniMax(6,7);
        GameDriver* gd  = new BotDriver(minimax,7,6);
        ms->setGameDriver( gd);
        dir->pushScene(ms);
        
    });
    
    auto playServerBtn = ui::Button::create("direction-sign.png");
    
    playServerBtn->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 -150));

    playServerBtn->setTitleText("Play with Server");
   
    playServerBtn->setTitleFontSize(40);

    playServerBtn->addClickEventListener([this](Object* sender) {
        printf("change event fired");
        if (this->gd){
            auto dir = Director:: getInstance();
            Player* p = gd->p;
            auto ms = MainScene:: create();
            GameDriver* sd = new ServerDriver(true, p,7,6);
            this->gd = sd;
            ms->setGameDriver(sd);
            dir->pushScene(ms);
        }
        else {
            auto loginpopup = LoginPopup::createWithPlayer(0);
            loginpopup->setName("LoginPopup"); 
            loginpopup->onSubmitCallback = [this] (std::string name){
                auto dir = Director:: getInstance();
                auto ms = MainScene:: create();
                Player* p = new Player(name, name, 0);
                GameDriver* sd = new ServerDriver(true, p,7,6);
                this->gd = sd;
                ms->setGameDriver(sd);
                dir->pushScene(ms);
                
            };
            this->addChild(loginpopup,3);
        }
        
    });
    
    auto multiplayerBtn = ui::Button::create("direction-sign.png");
    multiplayerBtn->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 450));
    multiplayerBtn->setTitleText("Multiplayer Game");
    multiplayerBtn->setTitleFontSize(40);
    multiplayerBtn->addClickEventListener([this](Object* sender) {
        printf("change event fired");
        if (this->gd){
            Player* p = this->gd->p;
            auto sd = new ServerDriver(false,p,7,6);
            this->gd = sd;
            WaitingPopup * waitingPopup = WaitingPopup:: create();
            waitingPopup->setName("waitingPopup");
            this->addChild(waitingPopup, 4 );
        }
        else {
            auto loginpopup = LoginPopup::createWithPlayer(0);
            loginpopup->setName("LoginPopup");
            loginpopup->onSubmitCallback = [this] (std::string name){
                Player* p = new Player(name, name, 0);
                auto sd = new ServerDriver(false,p,7,6);
                this->gd = sd;
                WaitingPopup * waitingPopup = WaitingPopup:: create();
                waitingPopup->setName("waitingPopup");
                this->addChild(waitingPopup, 4 );
            };
            this->addChild(loginpopup,3);
        }
       
      
    });
    
    EventListenerCustom* startMatch = Director::getInstance()->getEventDispatcher()->addCustomEventListener("startMatch", [this](EventCustom* e){
        
        this->removeChildByName("waitingPopup");
        
        auto data =  *(static_cast<vector<int>*>(e->getUserData()));
        int start = data[0];
        int turn  = data[1];
        auto dir = Director:: getInstance();
        auto ms = MainScene:: create();
        this->gd->turn = start;
        ms->setGameDriver(this->gd);
        dir->pushScene(ms);
 
    });


    this->addChild(friendGameBtn);

    this->addChild(botgameBtn);
    this->addChild(playServerBtn);
    this->addChild(multiplayerBtn);
    
    return true;
}

void StartScene::onExit(){
     Scene::onExit();
//    _eventDispatcher->removeCustomEventListeners("startMatch");
}
StartScene::StartScene() {
    // Your constructor code here (or empty)
}

StartScene::~StartScene() {
    // Cleanup if necessary
}


