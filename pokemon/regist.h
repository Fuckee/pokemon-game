#ifndef REGIST_H
#define REGIST_H

#include <QDialog>

namespace Ui {
class Regist;
}
//注册界面
class Regist : public QDialog
{
    Q_OBJECT

public:
    explicit Regist(QWidget *parent = 0);
    ~Regist();

private slots:
    void on_sure_clicked();
signals:
    void registNew(QString,QString);

private:
    Ui::Regist *ui;
};

#endif // REGIST_H
