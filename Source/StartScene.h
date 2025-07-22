//
//  StartScene.h
//  testproj
//
//  Created by Anurag Khugshal on 14/07/25.
//

#ifndef __START_SCENE_H__
#define __START_SCENE_H__


#include "axmol.h"
#include "../WebSocketManager.h"
class StartScene : public ax:: Scene {
    
    
public:
    bool init() override;
    WebSocketManager* wsm;
    CREATE_FUNC(StartScene);
//    void update(float delta) override;

    // touch
    void onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event);


    
    
//    void startGame ();
   

    StartScene();
    ~StartScene() override;
};

#endif

