#include "player.h"

player::player()
{

}

player::player(QString _name, int _win, int _lose, int _win1, int _lose1, int _state, QString _numbadge, QString _highbadge)
{
    name=_name;
    win=_win;
    lose=_lose;
    win1=_win1;
    lose1=_lose1;
     state=_state;
    numbadge=_numbadge;
    highbadge=_highbadge;
}

