

#include "MainScene.h"
#include <vector>
#include "../GameLogic/GameLogic.h"
#include "../AnimationUtils.h"
#include "GameDriver.h"
#include "../Popup/GameOver.h"
#include "audio/AudioEngine.h"

using namespace ax;
using namespace std;

static int s_sceneID = 1000;


bool MainScene::init()
{
    
    if (!Scene::init())
    {
        return false;
    }
    AXLOGD("MAINSCENE STARTING...");
    auto visibleSize = _director->getVisibleSize();
    auto origin      = _director->getVisibleOrigin();
    auto safeArea    = _director->getSafeAreaRect();
    auto safeOrigin  = safeArea.origin;
    
    
    
   
    
    EventListenerCustom* coinGlowListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener("coinGlow", [this](EventCustom* e){
        auto data = static_cast<pair<int,int>*>(e->getUserData());
        int col = data->first;
        int row = data->second;
        auto temptoken = gameboardgui[col][row];
        AnimationUtils::applyGlowEffect(temptoken,2);
        
        
    });
    EventListenerCustom* placeTokenListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener("placeToken", [this](EventCustom* e){
        auto data = static_cast<vector<int>*>(e->getUserData());
        MainScene:: placeToken((*data)[0], (*data)[1]);
        
        
    });
    
        EventListenerCustom* rematch = Director::getInstance()->getEventDispatcher()->addCustomEventListener("rematch", [this](EventCustom* e){
            for (auto& row : gameboardgui) {
                for (auto* sprite : row) {
                    if (sprite) {
                        sprite->removeFromParent(); // Detach from parent node
                    }
                }
            }
            gameboardgui = std::vector<std::vector<ax::Sprite*>> (7);
            this->gd->finished = false;
        
    });
    
   
    
    EventListenerCustom* gameFinished = Director::getInstance()->getEventDispatcher()->addCustomEventListener("gameFinished", [this](EventCustom* e) {
        this->scheduleOnce([this](float) {
            
            auto popup = PlayerPopup::createWithPlayer(1,gd);
            this->addChild(popup, 10); //
        }, 2.0f, "show_popup_key");
    });
    
    EventListenerCustom* switchTurn = Director::getInstance()->getEventDispatcher()->addCustomEventListener("switchTurn", [this, visibleSize](EventCustom* e){
        auto data = static_cast<int*>(e->getUserData());
        auto turnSprite = (*data)==0? Sprite:: create("button (2).png"):Sprite:: create("button (3).png");
        turnSprite->setScale(0.4f, 0.4f);
//        auto turnSprite = Sprite:: create("button(1).png");
        
        turnSprite->setPosition(visibleSize.width /2, 200);
        this->addChild(turnSprite);
    
});


    
    
    
    
    
  
    gameboardgui = std::vector<std::vector<ax::Sprite*>> (7);

  
    

    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           AX_CALLBACK_1(MainScene::menuCloseCallback, this));

    
        float x = safeOrigin.x + safeArea.size.width - closeItem->getContentSize().width / 2;
        float y = safeOrigin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    
    auto background = Sprite::create("mainbg.png");
    if (background)
    {
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        // Scale the background to fit the screen
        float scaleX = visibleSize.width / background->getContentSize().width;
        float scaleY = visibleSize.height / background->getContentSize().height;
        background->setScale(scaleX, scaleY);
        this->addChild(background, -1);
    }
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // Some templates (uncomment what you  need)
    _touchListener                 = EventListenerTouchAllAtOnce::create();
    _touchListener->onTouchesBegan = AX_CALLBACK_2(MainScene::onTouchesBegan, this);
    _touchListener->onTouchesMoved = AX_CALLBACK_2(MainScene::onTouchesMoved, this);
    _touchListener->onTouchesEnded = AX_CALLBACK_2(MainScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

    
    

    auto label = Label::createWithTTF("Connect4U", "fonts/Marker Felt.ttf", 24);
    label->setPosition(
        Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    
   
    auto board_front = Sprite::create("board_front.png"sv);
   
    auto board_back = Sprite::create("board_back.png"sv);
    boardSprite =  board_back;
    
        
    board_front->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    board_back->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y +30));
    
    
   
    this->addChild(board_front, 2);
    this->addChild(board_back, 0);
    auto drawNode = DrawNode::create();
    drawNode->setPosition(Vec2(0, 0));
    addChild(drawNode);

    drawNode->drawRect(safeArea.origin + Vec2(1, 1), safeArea.origin + safeArea.size, Color4F::BLUE);
    

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    boardSize = boardSprite->getContentSize();
    leftoffset = (boardSprite->getPositionX() - boardSize.width / 2) +82;
    
    bottomoffset = (boardSprite->getPositionY() - boardSize.height / 2) +56;
    tokenBorderWidth  = 13;
    tokenwidth = 79;
    
    scheduleUpdate();

    return true;
}


void MainScene:: placeToken(int token, int col){
    int row  =  gameboardgui[col].size();
    if (row >= 6) return;
    auto visibleSize = _director->getVisibleSize();
    auto visibleOrigin  = _director->getVisibleOrigin();
    Sprite* tokenSprite = nullptr;
    if (token){
        tokenSprite = Sprite::create("disc.png", Rect(0, 0, 79, 79));
    }
    else {
        tokenSprite = Sprite::create("disc.png", Rect(79, 0, 79, 79));
    }
    
    auto movetoken = MoveTo::create(0.5, Vec2(col*tokenwidth +leftoffset + tokenBorderWidth* col, row*tokenBorderWidth + row*tokenwidth + bottomoffset));
    auto easedrop = EaseBounceOut::create(movetoken);
    AudioEngine::play2d("drop.mp3");

    
    
    tokenSprite->setPosition(Vec2( col*tokenwidth +leftoffset + tokenBorderWidth*col , visibleSize.height+ visibleOrigin.y));
    tokenSprite->runAction(easedrop);
    this->addChild(tokenSprite,1);
    gameboardgui[col].push_back(tokenSprite);
   
}


void MainScene::onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        
        auto boardSize = boardSprite->getContentSize();
        int leftoffset = (boardSprite->getPositionX() - boardSize.width / 2) +82;
        
        int bottomoffset = (boardSprite->getPositionY() - boardSize.height / 2) +67;
        int tokenBorderWidth  = 13;
        int tokenwidth = 79;
        
        
        //get touch points
        auto targetx  = t->getLocation().x;
        auto targety =  t->getLocation().y;
        int targx =  (int) targetx;
        
        //col operations
        int col = (targx-leftoffset+18)/(tokenwidth+tokenBorderWidth);
        col = fmin(6,col);
        col = fmax(0,col);
        
        int row = (int)gameboardgui[col].size();
        if (row == 6) continue;
        row = fmin(5,row);
        
        gd->processMove(col,  row);
        
        
        
        
    
        
        AXLOGD("onTouchesBegan detected, X:{}  Y:{}", t->getLocation().x, t->getLocation().y);
        
    }
}


void MainScene::onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        // AXLOGD("onTouchesMoved detected, X:{}  Y:{}", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
    }
}




void MainScene::update(float delta)
{
   

}

void MainScene::menuCloseCallback(ax::Object* sender)
{
    // Close the axmol game scene and quit the application
    _director->end();

    
}

void MainScene:: setGameDriver(GameDriver* gd){
    this->gd = gd;
    auto visibleSize = _director->getVisibleSize();
    auto turnSprite = (this->gd->turn)==0? Sprite:: create("button (2).png"):Sprite:: create("button (3).png");

    turnSprite->setScale(0.4f, 0.4f);
    
    turnSprite->setPosition(visibleSize.width /2, 200);
    this->addChild(turnSprite);
}

MainScene::MainScene()
{
    _sceneID = ++s_sceneID;
    AXLOGD("Scene: ctor: #{}", _sceneID);
  
}

MainScene::~MainScene()
{
    AXLOGD("~Scene: dtor: #{}", _sceneID);

    if (_touchListener)
        _eventDispatcher->removeEventListener(_touchListener);

    _sceneID = -1;
}
