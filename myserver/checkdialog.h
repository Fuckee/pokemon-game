#ifndef CHECKDIALOG_H
#define CHECKDIALOG_H

#include <QDialog>

namespace Ui {
class CheckDialog;
}

class CheckDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckDialog(QWidget *parent = 0);
    ~CheckDialog();

private slots:
    void on_returnBtn_clicked();

    void on_checkBtn_clicked();
    void show_result(QString);

private:
    Ui::CheckDialog *ui;
signals:
    void askFor(QString);
};

#endif // CHECKDIALOG_H
