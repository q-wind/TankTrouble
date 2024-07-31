#ifndef ONLINEMODE_H
#define ONLINEMODE_H

#include "gamemode.h"

class OnlineMode: public GameMode
{
public:
    OnlineMode();
    ~OnlineMode();
    void InitGame() override;
    void UpdateGame() override;
    void EndGame() override;
};

#endif // ONLINEMODE_H
