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
    void setWaitingList(const QStringList list);
    void setRequestedNum(int num);

private slots:
    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::fillTableDialog *ui;
    QStringList waitinglist;
    int requestNum;
    void initTableList();
};

#endif // FILLTABLEDIALOG_H
