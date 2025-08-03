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
using namespace ax;

bool StatScene:: init(){
    if (!Scene::init())
    {
        return false;
    }
    return true;

    
        
}
bool StatScene:: initiateStats(){
    auto visibleSize = _director->getVisibleSize();
    auto listView = ui::ListView::create();
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    listView->setBounceEnabled(true);
    listView->setContentSize(Size(500, 400));
    listView->setPosition(Vec2(visibleSize.width / 2 - 150, visibleSize.height / 2 - 200));
    this->addChild(listView);

    // Add items
    for (int i = 0; i < this->stats.size(); ++i) {
        // Create a label instead of a button
        auto label = Label::createWithSystemFont("Item " + this->stats[i]->Winner, "Arial", 24);
        label->setTextColor(Color4B::WHITE);
    

        // Create a layout container
        auto layout = ui::Layout::create();
        layout->setContentSize(Size(300, 60));

        // Position the label in the center of the layout
        label->setPosition(Vec2(150, 30)); // (width/2, height/2)
        layout->addChild(label);

        // Add layout to the list view
        listView->pushBackCustomItem(layout);
    }


        
      
}
