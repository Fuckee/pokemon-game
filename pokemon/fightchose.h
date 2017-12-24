#ifndef FIGHTCHOSE_H
#define FIGHTCHOSE_H

#include <QDialog>
#include"choosetofight.h"
#include"preparefight.h"
namespace Ui {
class FightChose;
}
//战斗模式选择界面
class FightChose : public QDialog
{
    Q_OBJECT

public:
    explicit FightChose(QWidget *parent = 0);
    ~FightChose();
signals:
    void gg();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::FightChose *ui;
};

#endif // FIGHTCHOSE_H
