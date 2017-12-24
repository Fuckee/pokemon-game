#include "widget.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setStyle(new NorwegianWoodStyle);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    Widget w;
    w.show();
    QPixmap map(":/images/ball2.png");
    QIcon icon(map);
    a.setWindowIcon(icon);
    a.setApplicationName("Pokemon");


    return a.exec();
}

