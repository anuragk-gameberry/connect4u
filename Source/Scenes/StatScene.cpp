//
//  StatScene.cpp
//  testproj
//
//  Created by Anurag Khugshal on 31/07/25.
//

#include "StatScene.h"
#include "ui/UIListView.h"
#include "ui/UIButton.h"
#include "ui/CocosGUI.h"
#include "StartScene.h"
using namespace ax;
bool StatScene::init() {
    if (!Scene::init()) {
        return false;
    }

//    if (!this->initiateStats()) {
//        return false;
//    }

    return true;
}

bool StatScene::initiateStats() {
    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();

    auto background = Sprite::create("menubg.png");
    if (background) {
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        float scaleX = visibleSize.width / background->getContentSize().width;
        float scaleY = visibleSize.height / background->getContentSize().height;
        background->setScale(scaleX, scaleY);
        this->addChild(background, -1);
    }

    auto scroll = Sprite::create("scroll.png");
    scroll->setPosition(visibleSize / 2);
    scroll->setScale(1.5f);
    this->addChild(scroll, 0);

    if (this->getChildByName("StatListView")) {
        return true; // Already added
    }

    auto listView = ui::ListView::create();
    listView->setName("StatListView");
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    listView->setBounceEnabled(true);
    listView->setClippingEnabled(true);
    listView->setContentSize(Size(500, 400));
    listView->setAnchorPoint(Vec2(0.5f, 0.5f));
    listView->setBackGroundImageScale9Enabled(true);
    listView->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    listView->setGravity(ui::ListView::Gravity::CENTER_HORIZONTAL);
    listView->setItemsMargin(30.0f);

    auto headerLabel = Label::createWithSystemFont("  Date     Winner", "Arial", 40);
    headerLabel->setTextColor(Color4B::BLACK);
    auto headerLayout = ui::Layout::create();
    headerLayout->setContentSize(Size(300, 60));
    headerLabel->setPosition(Vec2(150, 30));
    headerLayout->addChild(headerLabel);
    listView->pushBackCustomItem(headerLayout);

    for (int i = 0; i < this->stats.size(); ++i) {
        auto st = this->stats[i];
        auto label = Label::createWithSystemFont(std::to_string(i) +" "+  st->Date+ "  "+st->Winner , "Arial", 40);
        label->setTextColor(Color4B::BLACK);
        auto layout = ui::Layout::create();
        layout->setContentSize(Size(300, 60));
        label->setPosition(Vec2(150, 30));
        layout->addChild(label);
        listView->pushBackCustomItem(layout);
    }

    this->addChild(listView, 1);
    auto backbtn = ui::Button:: create("replay.png");
    backbtn->addClickEventListener ([](Object* sender){
        auto dir = Director:: getInstance();
        auto ss = StartScene:: create();
        dir->replaceScene(ss);
    });
    backbtn->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.2f));
    backbtn->setScale(0.5f);
    this->addChild(backbtn,4);

    return true;
}
