#ifndef GAMEMODE_H
#define GAMEMODE_H

enum Mode
{
    AI,
    LOCAL,
    ONLINE
};

// 这个应该作为不同模式的config？用来构建对应的gameWidget
class GameMode
{
public:
    GameMode() {}
    virtual ~GameMode() {}
    virtual void InitGame() = 0;
    virtual void UpdateGame() = 0;
    virtual void EndGame() = 0;
private:

};

#endif // GAMEMODE_H
