#include "addcustomerdialog.h"
#include "ui_addcustomerdialog.h"

AddCustomerDialog::AddCustomerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCustomerDialog)
{
    ui->setupUi(this);
}

AddCustomerDialog::~AddCustomerDialog()
{
    delete ui;
}
