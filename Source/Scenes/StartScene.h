//
//  StartScene.h
//  testproj
//
//  Created by Anurag Khugshal on 14/07/25.
//

#ifndef __START_SCENE_H__
#define __START_SCENE_H__


#include "axmol.h"
#include "Utils/WebSocketManager.h"
#include "Drivers/GameDriver.h"
#include "Entities/Stat.h"
class StartScene : public ax:: Scene {
    
    
public:
    bool init() override;
    WebSocketManager* wsm;
    std::vector<Stat*> stats;
    GameDriver* gd;


    CREATE_FUNC(StartScene);
    void onExit() override;
    
    void onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event);
    

    StartScene();
    ~StartScene() override;
};

#endif

