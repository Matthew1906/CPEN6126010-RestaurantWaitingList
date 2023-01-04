#ifndef TABLEHISTORYDIALOG_H
#define TABLEHISTORYDIALOG_H

#include <QDialog>

namespace Ui {
class TableHistoryDialog;
}

class TableHistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableHistoryDialog(QWidget *parent = nullptr);
    ~TableHistoryDialog();
    void setHistory(const QList<struct Customer> list);

private:
    Ui::TableHistoryDialog *ui;
    QList<struct Customer> histories;
    void initHistory();
};

#endif // TABLEHISTORYDIALOG_H
