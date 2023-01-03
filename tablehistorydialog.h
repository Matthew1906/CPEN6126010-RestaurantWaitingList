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

private:
    Ui::TableHistoryDialog *ui;
};

#endif // TABLEHISTORYDIALOG_H
