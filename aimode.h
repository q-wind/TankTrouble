#ifndef AIMODE_H
#define AIMODE_H

#include "game.h"

class AIMode: public Game
{
public:
    AIMode();
    ~AIMode();
    void InitGame() override;
    void UpdateGame() override;
    void EndGame() override;
};

#endif // AIMODE_H
