#ifndef AIMODE_H
#define AIMODE_H

#include "gamemode.h"

class AIMode: public GameMode
{
public:
    AIMode();
    ~AIMode();
    void InitGame() override;
    void UpdateGame() override;
    void EndGame() override;
};

#endif // AIMODE_H
