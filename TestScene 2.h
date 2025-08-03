//
//  TestScene.h
//  testproj
//
//  Created by Anurag Khugshal on 21/07/25.
//


#pragma once

#include "axmol.h"
#include <vector>
#include "../GameDriver.h"

class TestScene : public ax::Scene
{
  
    
    
    
public:
    bool init() override;
    void update(float delta) override;
    CREATE_FUNC(TestScene);
    
    // touch
    void onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event);
    
    // a selector callback
    void menuCloseCallback(ax::Object* sender);
    void placeToken (int token, int col, int row);
    void setGameDriver(GameDriver* gd);
   
    TestScene();
    ~TestScene() override;
    
private:
    ax::EventListenerTouchAllAtOnce* _touchListener = nullptr;
    int _sceneID                                    = 0;
    std::vector<std:: vector<int>> gameboard;
    std:: vector <std::vector<ax::Sprite*>> gameboardgui;
    
    ax::Sprite* boardSprite = nullptr;
    ax::Size boardSize ;
    int leftoffset;
    
    int bottomoffset;
    int tokenBorderWidth ;
    int tokenwidth ;
    GameDriver* gd;
    
};


