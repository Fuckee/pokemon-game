#ifndef ADDSERVERPOKE_H
#define ADDSERVERPOKE_H

#include <QDialog>

namespace Ui {
class addServerPoke;
}

class addServerPoke : public QDialog
{
    Q_OBJECT

public:
    explicit addServerPoke(QStringList list,QWidget *parent = 0);
    ~addServerPoke();
signals:
    void add(QString,QString,int,QString,QString,QString,QString,QString);

private slots:
    void on_sureBtn_clicked();

private:
    Ui::addServerPoke *ui;
};

#endif // ADDSERVERPOKE_H
