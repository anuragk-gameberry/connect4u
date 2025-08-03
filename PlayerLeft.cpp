//
//  PlayerLeft.cpp
//  testproj
//
//  Created by Anurag Khugshal on 02/08/25.
//


#include "axmol.h"
#include "PlayerLeft.h"
using  namespace ax;
PlayerLeftPopup* PlayerLeftPopup :: create (){
    
    PlayerLeftPopup* wp =  new (std::nothrow)  PlayerLeftPopup();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto lens = Sprite::create("searching.png");  // replace with your actual image
    lens->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.55f));
    wp->addChild(lens, 5);

    
    
    auto findingLabel = Label::createWithSystemFont("Finding a match.", "Arial", 36);
    findingLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.45f));
    findingLabel->setTextColor(Color4B::WHITE);
    wp->addChild(findingLabel);

    // Variables for cycling dots
    std::vector<std::string> dotStates = {
        "Finding a match.",
        "Finding a match..",
        "Finding a match..."
    };
    int dotIndex = 0;

    // Schedule text update every 1 second
    wp->schedule([findingLabel, dotStates, dotIndex](float dt) mutable {
        findingLabel->setString(dotStates[dotIndex]);
        dotIndex = (dotIndex + 1) % dotStates.size();
    }, 1.0f, "update_finding_label");

}
