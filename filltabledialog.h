#ifndef FILLTABLEDIALOG_H
#define FILLTABLEDIALOG_H

#include <QDialog>

namespace Ui {
class fillTableDialog;
}

class fillTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit fillTableDialog(QWidget *parent = nullptr);
    ~fillTableDialog();
    void setWaitingList(const QList<struct Customer> list);
    int toAdd;

private slots:

private:
    Ui::fillTableDialog *ui;
    QList<struct Customer> waitinglist;
    void initTableList();
    void setChoice();
};

#endif // FILLTABLEDIALOG_H
