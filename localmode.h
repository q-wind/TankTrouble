#ifndef LOCALMODE_H
#define LOCALMODE_H

#include "game.h"

// 本地双人对战
class LocalMode: public Game
{
public:
    LocalMode();
    ~LocalMode();
    void InitGame() override;
    void UpdateGame() override;
    void EndGame() override;
};

#endif // LOCALMODE_H
