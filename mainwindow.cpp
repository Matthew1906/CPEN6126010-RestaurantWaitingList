#include <QDialog>
#include "filltabledialog.h"
#include "ui_filltabledialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addcustomerdialog.h"
#include "ui_addcustomerdialog.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initTableList();
    OpenDatabase();
}

struct Customer{
    int id;
    int numOfPeople;
    QString name;
};

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::OpenDatabase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("../CPEN6126010-RestaurantWaitingList/FinalProject.db");
    bool fResult = m_db.open();
    if (fResult)
    {
        qDebug() << "Database: connection ok";
        LoadTableList();
        waitingList();
        return true;
    }
    else
    {
        qDebug() << "Error: connection with database failed";
        return false;
    }
    return true;
}

void MainWindow::CloseDatabase()
{
    m_db.close();
}

bool MainWindow::LoadTableList(){
    QSqlQuery qry("SELECT ID,capacity,status FROM [Table]",
                     m_db);
        while (qry.next())
        {
            int id = qry.value("ID").toInt();
            int cap  = qry.value("capacity").toInt();
            int stat = qry.value("status").toInt();
            QString status = stat ? "Full" : "Empty";
            qDebug() << id << ", " << cap << ", " << status;

            int nRowCount = ui->tableList->rowCount();

            ui->tableList->setRowCount(nRowCount+1);
            ui->tableList->setItem(nRowCount, 0, new QTableWidgetItem(QString::number(id)));
            ui->tableList->setItem(nRowCount, 1, new QTableWidgetItem(QString::number(cap)));
            ui->tableList->setItem(nRowCount, 2, new QTableWidgetItem(status));
            ui->tableList->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
            ui->tableList->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
            ui->tableList->item(nRowCount, 2)->setFlags(Qt::ItemIsEditable);
            ui->tableList->item(nRowCount, 0)->setTextAlignment( Qt::AlignCenter );
            ui->tableList->item(nRowCount, 1)->setTextAlignment( Qt::AlignCenter );
            ui->tableList->item(nRowCount, 2)->setTextAlignment( Qt::AlignCenter );
            QPushButton* action_btn = new QPushButton();
            QObject::connect(action_btn, &QPushButton::clicked, this, [this,id]{tableListClick(id);});
            action_btn->setIcon(QIcon(stat ? ":/icons/fillTable.png" : ":/icons/emptyTable.png"));
            ui->tableList->setCellWidget(nRowCount, 3, action_btn);
        }
        return true;
}

void MainWindow::initTableList()
{
    QStringList headers;
    headers << "No." << "Capacity" << "Status"<< "Action";
    ui->tableList->setColumnCount(headers.length());
    ui->tableList->setHorizontalHeaderLabels(headers);
    ui->tableList->horizontalHeader()->setStretchLastSection(true);
    ui->tableList->verticalHeader()->setVisible(false);
    ui->tableList->setColumnWidth(0, 20);
}

void MainWindow::waitingList(){
    QSqlQuery qry("SELECT name,numOfPeople FROM Customer",
                     m_db);

        while (qry.next())
        {
            QString name  = qry.value("name").toString();
            int numOfPeople = qry.value("numOfPeople").toInt();
            ui->waitingList->addItem("Reservation Name: " + name + "\nNumber of People: " + QString::number(numOfPeople));
        }
}

void MainWindow::on_addCustomer_clicked()
{
    AddCustomerDialog add;
    if(add.exec()==QDialog::Accepted){
        QString name = add.ui->name_input->text();
        int numPeople = add.ui->numPeople_input->value();
        QString waiting = QString("Reservation Name: ") + name +"\nNumber of People: "+ QString::number(numPeople)+'\n';
        ui->waitingList->addItem(waiting);

        QSqlQuery qry(m_db);
          qry.prepare("INSERT INTO Customer (name, numOfPeople, timestamp) VALUES(:name, :numOfPeople, :timestamp)");
          qry.bindValue(":name", name);
          qry.bindValue(":numOfPeople", numPeople);
          qry.bindValue(":timestamp", QDateTime::currentDateTime().toString());
          bool fResult = qry.exec();
          if (!fResult)
              qDebug() << "Insert Data Error: " <<
                          qry.lastError().text();
    }
}

void MainWindow::tableListClick(int row){
    fillTableDialog ft;
    QList <struct Customer> cust;
    int capacity = ui->tableList->item(row,1)->text().toInt();
    QSqlQuery qry("SELECT ID,name,numOfPeople FROM Customer WHERE numOfPeople <= " + QString::number(capacity),
                     m_db);

        while (qry.next())
        {
            int id = qry.value("id").toInt();
            QString name  = qry.value("name").toString();
            int numOfPeople = qry.value("numOfPeople").toInt();
            struct Customer cs = {id,numOfPeople,name};
            cust.append(cs);
        }
    ft.setWaitingList(cust);
    if(ft.exec()==QDialog::Accepted){

    }
}




