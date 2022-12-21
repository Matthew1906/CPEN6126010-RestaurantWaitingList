#include <QDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addcustomerdialog.h"
#include "ui_addcustomerdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initTableList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTableList()
{
    QStringList headers;
    headers << "Capacity" << "Status"<< "Action";
    ui->tableList->setColumnCount(headers.length());
    ui->tableList->setHorizontalHeaderLabels(headers);
    ui->tableList->horizontalHeader()->setStretchLastSection(true);

    int nRowCount = ui->tableList->rowCount();
    ui->tableList->setRowCount(nRowCount+1);
    ui->tableList->setItem(nRowCount, 0, new QTableWidgetItem("10"));
    ui->tableList->setItem(nRowCount, 1, new QTableWidgetItem("Full"));
    QPushButton* action_btn = new QPushButton();
    action_btn->setIcon(QIcon(":/icons/emptyTable.png"));
    ui->tableList->setCellWidget(nRowCount, 2, action_btn);
}

void MainWindow::on_addCustomer_clicked()
{
    AddCustomerDialog add;
    if(add.exec()==QDialog::Accepted){
        QString name = add.ui->name_input->text();
        int numPeople = add.ui->numPeople_input->value();
        if(name.trimmed()!="" && numPeople>0){
            qDebug()<<name<<": "<<numPeople;
        }
    }
}

