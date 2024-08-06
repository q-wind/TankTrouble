#ifndef ONLINEMODE_H
#define ONLINEMODE_H

#include "game.h"

class OnlineMode: public Game
{
public:
    OnlineMode();
    ~OnlineMode();
    void InitGame() override;
    void UpdateGame() override;
    void EndGame() override;
};

#endif // ONLINEMODE_H
