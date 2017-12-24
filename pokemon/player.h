#ifndef PLAYER_H
#define PLAYER_H
#include"pokemon/all_head.h"
//用户类
class player
{
public:
    player(QString name,int win,int lose,int win1,int lose1,int state,QString numbadge="null",QString highbadge="null");
    player();
    int win,win1,lose,lose1;
    QString name,numbadge,highbadge;
    int state;
};

#endif // PLAYER_H
