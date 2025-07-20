//
//  GameOver.h
//  testproj
//
//  Created by Anurag Khugshal on 18/07/25.
//

#pragma once

#include "axmol.h"

class PlayerPopup : public ax::LayerColor {
public:
    static PlayerPopup* createWithPlayer(int playerNumber);
    bool initWithPlayer(int playerNumber);
};
