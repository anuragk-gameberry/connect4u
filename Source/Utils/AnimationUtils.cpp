//
//  AnimationUtils.cpp
//  testproj
//
//  Created by Anurag Khugshal on 14/07/25.
//

#include "AnimationUtils.h"

using namespace cocos2d;

ActionInterval* AnimationUtils::createGlowPulse(float scale, int repeat) {
    auto delay = DelayTime::create(0.4f);
    auto scaleUp = ScaleTo::create(0.2f, scale);
    
    auto scaleDown = ScaleTo::create(0.2f, 1.0f);
    auto brighten = TintTo::create(0.2f, 190, 190, 190);
    auto darken = TintTo::create(0.2f, 255, 255, 255);
    
    auto scaleUpandBrighten = Spawn::create(scaleUp, brighten, nullptr);
    auto scaleDownAndDarken = Spawn::create(scaleDown, darken, nullptr);
    auto glow = Sequence::create(scaleUpandBrighten,scaleDownAndDarken,nullptr);
    auto resultAnimation =  Repeat::create(glow,3);
    return Sequence:: create(delay,resultAnimation,nullptr);
}

void AnimationUtils::applyGlowEffect(Sprite* sprite, int repeat) {
    sprite->runAction(createGlowPulse(1.2f, repeat));
}
