#ifndef CHOOSETOFIGHT_H
#define CHOOSETOFIGHT_H

#include <QDialog>
#include<pokemon/all_head.h>
namespace Ui {
class ChooseToFight;
}
//选择出站精灵的界面
class ChooseToFight : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseToFight(QList<pokemon*> list,QWidget *parent = 0);
    ~ChooseToFight();
signals:
    void thechose(int);
private slots:
    void on_a1_clicked();
    void on_a2_clicked();
    void on_a3_clicked();
    void on_a4_clicked();
    void on_a5_clicked();
    void on_a6_clicked();
    void on_a7_clicked();
    void on_a8_clicked();
    void on_a9_clicked();
    void on_a10_clicked();
    void on_a11_clicked();
    void on_a12_clicked();
    void on_a13_clicked();
    void on_a14_clicked();
    void on_a15_clicked();
    void on_a16_clicked();
    void on_a17_clicked();
    void on_a18_clicked();
    void on_a19_clicked();
    void on_a20_clicked();
    void on_a21_clicked();
    void on_a22_clicked();


private:
    Ui::ChooseToFight *ui;
    QList<pokemon*> thelist;
};

#endif // CHOOSETOFIGHT_H
