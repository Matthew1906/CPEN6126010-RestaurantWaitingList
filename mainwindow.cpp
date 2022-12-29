#include <QDialog>
#include "filltabledialog.h"
#include "ui_filltabledialog.h"
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
    ui->tableList->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
    ui->tableList->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
    QPushButton* action_btn = new QPushButton();
    QObject::connect(action_btn, &QPushButton::clicked, this, [this]{tableListClick(0);});

    action_btn->setIcon(QIcon(":/icons/emptyTable.png"));
    ui->tableList->setCellWidget(nRowCount, 2, action_btn);

    nRowCount = ui->tableList->rowCount();
    ui->tableList->setRowCount(nRowCount+1);
    ui->tableList->setItem(nRowCount, 0, new QTableWidgetItem("10"));
    ui->tableList->setItem(nRowCount, 1, new QTableWidgetItem("Empty"));
    ui->tableList->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
    ui->tableList->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
    action_btn = new QPushButton();
    QObject::connect(action_btn, &QPushButton::clicked, this, [this]{tableListClick(1);});
    action_btn->setIcon(QIcon(":/icons/fillTable.png"));
    ui->tableList->setCellWidget(nRowCount, 2, action_btn);

    nRowCount = ui->tableList->rowCount();
    ui->tableList->setRowCount(nRowCount+1);
    ui->tableList->setItem(nRowCount, 0, new QTableWidgetItem("8"));
    ui->tableList->setItem(nRowCount, 1, new QTableWidgetItem("Empty"));
    ui->tableList->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
    ui->tableList->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
    action_btn = new QPushButton();
    QObject::connect(action_btn, &QPushButton::clicked, this, [this]{tableListClick(2);});
    action_btn->setIcon(QIcon(":/icons/fillTable.png"));
    ui->tableList->setCellWidget(nRowCount, 2, action_btn);

    nRowCount = ui->tableList->rowCount();
    ui->tableList->setRowCount(nRowCount+1);
    ui->tableList->setItem(nRowCount, 0, new QTableWidgetItem("8"));
    ui->tableList->setItem(nRowCount, 1, new QTableWidgetItem("Empty"));
    ui->tableList->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
    ui->tableList->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
    action_btn = new QPushButton();
    QObject::connect(action_btn, &QPushButton::clicked, this, [this]{tableListClick(3);});
    action_btn->setIcon(QIcon(":/icons/fillTable.png"));
    ui->tableList->setCellWidget(nRowCount, 2, action_btn);

    nRowCount = ui->tableList->rowCount();
    ui->tableList->setRowCount(nRowCount+1);
    ui->tableList->setItem(nRowCount, 0, new QTableWidgetItem("7"));
    ui->tableList->setItem(nRowCount, 1, new QTableWidgetItem("Empty"));
    ui->tableList->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
    ui->tableList->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
    action_btn = new QPushButton();
    QObject::connect(action_btn, &QPushButton::clicked, this, [this]{tableListClick(4);});
    action_btn->setIcon(QIcon(":/icons/fillTable.png"));
    ui->tableList->setCellWidget(nRowCount, 2, action_btn);

    nRowCount = ui->tableList->rowCount();
    ui->tableList->setRowCount(nRowCount+1);
    ui->tableList->setItem(nRowCount, 0, new QTableWidgetItem("6"));
    ui->tableList->setItem(nRowCount, 1, new QTableWidgetItem("Empty"));
    ui->tableList->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
    ui->tableList->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
    action_btn = new QPushButton();
    QObject::connect(action_btn, &QPushButton::clicked, this, [this]{tableListClick(5);});
    action_btn->setIcon(QIcon(":/icons/fillTable.png"));
    ui->tableList->setCellWidget(nRowCount, 2, action_btn);

    nRowCount = ui->tableList->rowCount();
    ui->tableList->setRowCount(nRowCount+1);
    ui->tableList->setItem(nRowCount, 0, new QTableWidgetItem("5"));
    ui->tableList->setItem(nRowCount, 1, new QTableWidgetItem("Empty"));
    ui->tableList->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
    ui->tableList->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
    action_btn = new QPushButton();
    QObject::connect(action_btn, &QPushButton::clicked, this, [this]{tableListClick(6);});
    action_btn->setIcon(QIcon(":/icons/emptyTable.png"));
    ui->tableList->setCellWidget(nRowCount, 2, action_btn);

    nRowCount = ui->tableList->rowCount();
    ui->tableList->setRowCount(nRowCount+1);
    ui->tableList->setItem(nRowCount, 0, new QTableWidgetItem("4"));
    ui->tableList->setItem(nRowCount, 1, new QTableWidgetItem("Empty"));
    ui->tableList->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
    ui->tableList->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
    action_btn = new QPushButton();
    QObject::connect(action_btn, &QPushButton::clicked, this, [this]{tableListClick(7);});
    action_btn->setIcon(QIcon(":/icons/fillTable.png"));
    ui->tableList->setCellWidget(nRowCount, 2, action_btn);

    nRowCount = ui->tableList->rowCount();
    ui->tableList->setRowCount(nRowCount+1);
    ui->tableList->setItem(nRowCount, 0, new QTableWidgetItem("3"));
    ui->tableList->setItem(nRowCount, 1, new QTableWidgetItem("Empty"));
    ui->tableList->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
    ui->tableList->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
    action_btn = new QPushButton();
    QObject::connect(action_btn, &QPushButton::clicked, this, [this]{tableListClick(8);});
    action_btn->setIcon(QIcon(":/icons/fillTable.png"));
    ui->tableList->setCellWidget(nRowCount, 2, action_btn);

    nRowCount = ui->tableList->rowCount();
    ui->tableList->setRowCount(nRowCount+1);
    ui->tableList->setItem(nRowCount, 0, new QTableWidgetItem("2"));
    ui->tableList->setItem(nRowCount, 1, new QTableWidgetItem("Empty"));
    ui->tableList->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
    ui->tableList->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
    action_btn = new QPushButton();
    QObject::connect(action_btn, &QPushButton::clicked, this, [this]{tableListClick(9);});
    action_btn->setIcon(QIcon(":/icons/fillTable.png"));
    ui->tableList->setCellWidget(nRowCount, 2, action_btn);

}

void MainWindow::on_addCustomer_clicked()
{
    AddCustomerDialog add;
    if(add.exec()==QDialog::Accepted){
        QString name = add.ui->name_input->text();
        int numPeople = add.ui->numPeople_input->value();
        QString waiting = QString("Reservation Name: ") + name +"\nNumber of People: "+ QString::number(numPeople)+'\n';
        ui->waitingList->addItem(waiting);

    }
}

void MainWindow::tableListClick(int row){
    fillTableDialog ft;
    QStringList list;

    int numOfPeople = ui->tableList->item(row,0)->text().toInt();

    int len = ui->waitingList->count();
    for(int i=0; i < len; i++){
        QString str = ui->waitingList->item(i)->text();

        QStringList values = str.split("\n");
        QString name = values.value(0).split(":").value(1).trimmed();
        int num = values.value(1).split(":").value(1).trimmed().toInt();
        qDebug() << numOfPeople << 'test';

        if(num<=numOfPeople){
            list.append(ui->waitingList->item(i)->text());
        }

    }



    ft.setWaitingList(list);
//    ft.setRequestedNum(ui->waitingList)
    if(ft.exec()==QDialog::Accepted){

    }
}




