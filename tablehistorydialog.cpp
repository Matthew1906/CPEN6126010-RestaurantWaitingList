#include "tablehistorydialog.h"
#include "ui_tablehistorydialog.h"

TableHistoryDialog::TableHistoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableHistoryDialog)
{
    ui->setupUi(this);
}

TableHistoryDialog::~TableHistoryDialog()
{
    delete ui;
}
