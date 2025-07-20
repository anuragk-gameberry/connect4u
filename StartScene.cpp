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
        dir->replaceScene(ms);
    });
    
    startButton->addTouchEventListener([](Object* sender, ui::Widget::TouchEventType type){
        switch(type) {
            case ui::Widget::TouchEventType::BEGAN:
                 
                break;
            case ui::Widget::TouchEventType::MOVED:
            
                break;
            case ui::Widget::TouchEventType::ENDED:
                
                break;
            case ui::Widget::TouchEventType::CANCELED:
                
                break;
            default:
                break;
        }
    });


    this->addChild(startButton);
    return true;



    
//    button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
//            switch (type)
//            {
//                    case ui::Widget::TouchEventType::BEGAN:
//                            break;
//                    case ui::Widget::TouchEventType::ENDED:
//                            std::cout << "Button 1 clicked" << std::endl;
//                            break;
//                    default:
//                            break;
//            }
//    });

    this->addChild(startButton);
    
    
}

StartScene::StartScene() {
    // Your constructor code here (or empty)
}

StartScene::~StartScene() {
    // Cleanup if necessary
}


