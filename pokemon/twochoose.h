#ifndef TWOCHOOSE_H
#define TWOCHOOSE_H

#include <QDialog>
#include"player.h"
#include"information.h"
#include"info.h"
#include"pokemonbox.h"
#include"theshare.h"
namespace Ui {
class TwoChoose;
}

class TwoChoose : public QDialog
{
    Q_OBJECT

public:
    explicit TwoChoose(player aplayer,QList<pokemon*> list,QWidget *parent = 0);
    ~TwoChoose();

signals:
    void gg();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::TwoChoose *ui;

    player _player;
    QList<pokemon*> pokelist;

};

#endif // TWOCHOOSE_H
