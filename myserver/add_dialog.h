#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>

namespace Ui {
class add_Dialog;
}

class add_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit add_Dialog(QWidget *parent = 0);
    ~add_Dialog();

private slots:
    void on_sureBtn_clicked();

    void on_quitBtn_clicked();

private:
    Ui::add_Dialog *ui;
signals:
    void add_new(QString,QString);
};

#endif // ADD_DIALOG_H
