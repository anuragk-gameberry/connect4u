//
//  FirstScene.cpp
//  testproj
//
//  Created by Anurag Khugshal on 25/07/25.
//


using namespace ax;

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
   


    auto startButton1 = ui::Button::create('but');
    
    startButton1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 300));

    startButton1->setTitleText("Play with Bot");
   
    startButton1->setTitleFontSize(40);
    
    return true;
}

StartScene::StartScene() {
    // Your constructor code here (or empty)
}

StartScene::~StartScene() {
    // Cleanup if necessary
}


