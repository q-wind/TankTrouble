#ifndef GAME_H
#define GAME_H

enum Mode
{
    AI,
    LOCAL,
    ONLINE,
    UNKNOW
};


class Game
{
public:
    Game() {}
    virtual ~Game() {}
    virtual void InitGame() = 0;
    virtual void UpdateGame() = 0;
    virtual void EndGame() = 0;

    Mode m_mode = Mode::UNKNOW;
};

#endif // GAME_H
