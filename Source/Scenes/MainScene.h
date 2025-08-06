/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

 https://axmol.dev/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "axmol.h"
#include <vector>
#include "Drivers/GameDriver.h"

class MainScene : public ax::Scene
{
  
    
    
    
public:
    bool init() override;
    void update(float delta) override;
    CREATE_FUNC(MainScene);
    
    // touch
    void onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event);
    
    // a selector callback
    void menuCloseCallback(ax::Object* sender);
    void placeToken (int token, int col);
    void setGameDriver(GameDriver* gd);
    void onExit() override;
    void addEventListeners();
    MainScene();
    ~MainScene() override;
    
private:
    ax::EventListenerTouchAllAtOnce* _touchListener = nullptr;
    ax::EventListenerCustom* coinGlowListener = nullptr;
    ax::EventListenerCustom* placeTokenListener = nullptr;
    ax::EventListenerCustom* gameFinished = nullptr;
    ax::EventListenerCustom* switchTurn = nullptr;
    ax::EventListenerCustom* rematch = nullptr;
    ax::EventListenerCustom* switchPlayerName = nullptr;
    ax::EventListenerCustom* statsReceived = nullptr;
    ax::EventListenerCustom* playerLeft = nullptr;
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
    ax::Label* currentplayer;
    
};

#endif  // __MAIN_SCENE_H__
