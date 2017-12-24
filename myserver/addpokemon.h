#ifndef ADDPOKEMON_H
#define ADDPOKEMON_H

#include <QDialog>

namespace Ui {
class AddPokemon;
}

class AddPokemon : public QDialog
{
    Q_OBJECT

public:
    explicit AddPokemon(QWidget* parent,QStringList list);
    ~AddPokemon();

private slots:
    void on_level_currentIndexChanged(int index);


    void on_backBtn_clicked();

    void on_sureBtn_clicked();
signals:
    void add(QString ,QString,int,int,QString,QString,QString,QString,QString);

private:
    Ui::AddPokemon *ui;
    QStringList namelist;
};

#endif // ADDPOKEMON_H
