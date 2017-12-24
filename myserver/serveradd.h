#ifndef SERVERADD_H
#define SERVERADD_H

#include <QDialog>

namespace Ui {
class serverAdd;
}

class serverAdd : public QDialog
{
    Q_OBJECT

public:
    explicit serverAdd(QWidget *parent = 0);
    ~serverAdd();
signals:
    void addServer(QString name,QString level);

private slots:
    void on_pushButton_clicked();

private:
    Ui::serverAdd *ui;
};

#endif // SERVERADD_H
