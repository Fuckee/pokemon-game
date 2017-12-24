#ifndef POKEMONBOX_H
#define POKEMONBOX_H
#include<information.h>
#include <QDialog>
#include"pokemon/all_head.h"
namespace Ui {
class PokemonBox;
}
//精灵箱子
class PokemonBox : public QDialog
{
    Q_OBJECT

public:
    explicit PokemonBox(QList<pokemon*>list, QWidget *parent = 0);
    ~PokemonBox();
signals:
    void clickN(int i);

private slots:


    void on_a2_clicked();

    void on_a1_clicked();

    void on_a3_clicked();

    void on_a4_clicked();

    void on_a5_clicked();

    void on_a6_clicked();

    void on_a7_clicked();

    void on_a9_clicked();

    void on_a8_clicked();

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

    void on_a23_clicked();

    void on_a24_clicked();

    void on_a25_clicked();

    void on_a26_clicked();

    void on_a27_clicked();

    void on_a28_clicked();

    void on_a29_clicked();

    void on_a30_clicked();
    void showPoke(int);

    void on_pushButton_clicked();

private:
    Ui::PokemonBox *ui;
    QList<pokemon*> pokelist;
};

#endif // POKEMONBOX_H
