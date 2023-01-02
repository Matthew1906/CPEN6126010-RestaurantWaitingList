#include "addcustomerdialog.h"
#include "ui_addcustomerdialog.h"

AddCustomerDialog::AddCustomerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCustomerDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Add New Customer");
    this->setWindowIcon(QIcon(":/icons/customerIcon.png"));
}

AddCustomerDialog::~AddCustomerDialog()
{
    delete ui;
}
