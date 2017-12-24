#ifndef INFORMATION_H
#define INFORMATION_H

#include <QDialog>
#include<pokemon/all_head.h>
#include<theshare.h>
namespace Ui {
class Information;
}
//精灵信息介绍界面
class Information : public QDialog
{
    Q_OBJECT

public:
    explicit Information(pokemon* poke,QWidget *parent = 0);
    ~Information();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Information *ui;
};

#endif // INFORMATION_H
