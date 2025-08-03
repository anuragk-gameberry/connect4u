//
//  AnimationUtils.h
//  testproj
//
//  Created by Anurag Khugshal on 14/07/25.
//

#pragma once
#include "cocos2d.h"

class AnimationUtils {
public:
    static cocos2d::ActionInterval* createGlowPulse(float scale = 1.2f, int repeat = 3);
    static void applyGlowEffect(cocos2d::Sprite* sprite, int repeat = 3);
};
