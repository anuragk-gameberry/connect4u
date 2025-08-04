//
//  Waiting.cpp
//  testproj
//
//  Created by Anurag Khugshal on 02/08/25.
//
#include "Waiting.h"
#include "axmol.h"

using namespace ax;

WaitingPopup* WaitingPopup::create() {
    WaitingPopup* wp = new (std::nothrow) WaitingPopup();

    if (wp && wp->initWithColor(Color4B(0, 0, 0, 180))) { // use LayerColor init
        wp->autorelease();

        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

        // Lens/trophy sprite
        auto lens = Sprite::create("loupe.png");  // Use actual lens if available
        lens->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.55f));
        wp->addChild(lens, 5);

        // Loading label
        auto findingLabel = Label::createWithSystemFont("Finding a match.", "Arial", 45);
        findingLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.25f));
        findingLabel->setTextColor(Color4B::WHITE);
        wp->addChild(findingLabel);

        // Animate dots
        std::vector<std::string> dotStates = {
            "Finding a match.",
            "Finding a match..",
            "Finding a match..."
        };
        int dotIndex = 0;

        wp->schedule([findingLabel, dotStates, dotIndex](float dt) mutable {
            findingLabel->setString(dotStates[dotIndex]);
            dotIndex = (dotIndex + 1) % dotStates.size();
        }, 0.33f, "update_finding_label");

        // Block touches from leaking through (optional but recommended)
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = [](Touch* touch, Event* event) {
            return true;
        };
        wp->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, wp);

        return wp;
    }

    AX_SAFE_DELETE(wp);
    return nullptr;
}
