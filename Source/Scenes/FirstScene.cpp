//
//  FirstScene.cpp
//  testproj
//
//  Created by Anurag Khugshal on 25/07/25.
//

#include "FirstScene.h"
#include "axmol.h"
#include "ui/UIButton.h"
#include "ui/CocosGUI.h"
#include "StartScene.h"
using namespace ax;

bool FirstScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
   
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto background = Sprite::create("FirstBg.png");
    if (background)
    {
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        // Scale the background to fit the screen
        float scaleX = visibleSize.width / background->getContentSize().width;
        float scaleY = visibleSize.height / background->getContentSize().height;
        background->setScale(scaleX, scaleY);
        this->addChild(background, -1);
    }

    auto playButton = ui::Button::create("play.png");
    
    playButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 ));
    
    playButton->addClickEventListener([](Object* sender) {
        printf("change event fired");
        auto dir = Director:: getInstance();
        auto ss = StartScene:: create();
//        BotAlgorithm* minimax =  new MiniMax(6,7);
//        ms->setGameDriver( new BotDriver(minimax));
        dir->pushScene(ss);
        
    });
    this->addChild(playButton,2);
    return true;
}
void FirstScene::update(float dt)
{}
FirstScene::FirstScene() {
    // Your constructor code here (or empty)
}

FirstScene::~FirstScene() {
    // Cleanup if necessary
}


