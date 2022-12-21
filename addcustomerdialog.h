#ifndef ADDCUSTOMERDIALOG_H
#define ADDCUSTOMERDIALOG_H

#include <QDialog>

namespace Ui {
class AddCustomerDialog;
}

class AddCustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCustomerDialog(QWidget *parent = nullptr);
    ~AddCustomerDialog();
    Ui::AddCustomerDialog *ui;
};

#endif // ADDCUSTOMERDIALOG_H
