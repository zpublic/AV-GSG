#pragma once

class GameScene
{
public:
    GameScene() {}
    virtual ~GameScene(){}

    virtual void Update() {};
    virtual void Output() {};
    virtual void Reset() {}

private:
    GameScene(const GameScene& other) {}
    GameScene& operator=(const GameScene& other) {}
};
