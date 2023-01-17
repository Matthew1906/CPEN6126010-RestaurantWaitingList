#include <QDateTime>
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include "customer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addcustomerdialog.h"
#include "ui_addcustomerdialog.h"
#include "filltabledialog.h"
#include "tablehistorydialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Restaurant Waiting List");
    this->setWindowIcon(QIcon(":/icons/reservationIcon.png"));
    initTableList();
    openDatabase();
    connect(ui->actionAdd_Customer, &QAction::triggered, this, &MainWindow::addCustomer);
    connect(ui->addCustomer, &QPushButton::clicked, this, &MainWindow::addCustomer);
}

MainWindow::~MainWindow()
{
    closeDatabase();
    delete ui;
}

bool MainWindow::openDatabase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("../CPEN6126010-RestaurantWaitingList/FinalProject.db");
    bool fResult = m_db.open();
    if (fResult)
    {
        qDebug() << "Database: connection ok";
        loadTableList();
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

void MainWindow::closeDatabase()
{
    m_db.close();
}

bool MainWindow::loadTableList()
{
    // Load and reload table data
    ui->tableList->clearContents();
    ui->tableList->setRowCount(0);
    QSqlQuery qry("SELECT ID, capacity, status FROM [Table]", m_db);
    while (qry.next())
    {
        int id = qry.value("ID").toInt();
        int cap  = qry.value("capacity").toInt();
        int stat = qry.value("status").toInt();
        QString status = stat ? "Full" : "Empty";
        // Add to table widget
        int nRowCount = ui->tableList->rowCount();
        ui->tableList->setRowCount(nRowCount+1);
        ui->tableList->setItem(nRowCount, 0, new QTableWidgetItem(QString::number(id)));
        ui->tableList->setItem(nRowCount, 1, new QTableWidgetItem(QString::number(cap)));
        ui->tableList->setItem(nRowCount, 2, new QTableWidgetItem(status));
        ui->tableList->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
        ui->tableList->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
        ui->tableList->item(nRowCount, 2)->setFlags(Qt::ItemIsEditable);
        ui->tableList->item(nRowCount, 0)->setTextAlignment(Qt::AlignCenter);
        ui->tableList->item(nRowCount, 1)->setTextAlignment(Qt::AlignCenter);
        ui->tableList->item(nRowCount, 2)->setTextAlignment(Qt::AlignCenter);
        QPushButton* action_btn = new QPushButton();
        QObject::connect(action_btn, &QPushButton::clicked, this, [this]{tableListClick();});
        action_btn->setIcon(QIcon(stat ? ":/icons/emptyTable.png" : ":/icons/fillTable.png"));
        ui->tableList->setCellWidget(nRowCount, 3, action_btn);
    }
    return true;
}

void MainWindow::initTableList()
{
    // Initialize table headers
    QStringList headers;
    headers << "No." << "Capacity" << "Status"<< "Action";
    ui->tableList->setColumnCount(headers.length());
    ui->tableList->setHorizontalHeaderLabels(headers);
    ui->tableList->horizontalHeader()->setStretchLastSection(true);
    ui->tableList->verticalHeader()->setVisible(false);
    ui->tableList->setColumnWidth(0, 20);
}

void MainWindow::waitingList()
{
    // Load and reload waiting list
    ui->waitingList->clear();
    QSqlQuery qry("SELECT name, numOfPeople, Table_ID FROM Customer WHERE Table_ID IS NULL", m_db);
    while (qry.next())
    {
        QString name  = qry.value("name").toString();
        int numOfPeople = qry.value("numOfPeople").toInt();
        ui->waitingList->addItem("Reservation Name: " + name + "\nNumber of People: " + QString::number(numOfPeople)+"\n");
    }
}

void MainWindow::addCustomer()
{
    // Add new customer to the list
    AddCustomerDialog add;
    if(add.exec()==QDialog::Accepted)
    {
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
        {
            qDebug() << "Insert Data Error: " << qry.lastError().text();
        }
    }
}

void MainWindow::tableListClick()
{
    QString status =  ui->tableList->item(ui->tableList->currentRow(),2)->text();
    if(status=="Empty"){
        // Find customer for empty table
        fillTableDialog ft;
        QList <struct Customer> cust;
        int capacity = ui->tableList->item(ui->tableList->currentRow(),1)->text().toInt();
        QSqlQuery qry("SELECT ID, name, numOfPeople, timestamp FROM Customer WHERE Table_ID IS NULL AND numOfPeople <= " + QString::number(capacity),m_db);
        while (qry.next())
        {
            int id = qry.value("id").toInt();
            QString name  = qry.value("name").toString();
            int numOfPeople = qry.value("numOfPeople").toInt();
            QString timestamp = qry.value("timestamp").toString();
            struct Customer cs = {id,numOfPeople,name, timestamp};
            cust.append(cs);
        }
        ft.setWaitingList(cust);
        if(ft.exec()==QDialog::Accepted)
        {
            int customerId = ft.toAdd;
            QSqlQuery qry(m_db);
            qry.prepare("UPDATE Customer SET Table_ID=:tableId, timestamp=:timestamp WHERE ID=:customerId");
            qry.bindValue(":tableId", ui->tableList->item(ui->tableList->currentRow(), 0)->text().toInt());
            qry.bindValue(":timestamp", QDateTime::currentDateTime().toString());
            qry.bindValue(":customerId", customerId);
            bool fResult = qry.exec();
            if (!fResult)
            {
                qDebug() << "Update Waiting List Data Error: " << qry.lastError().text();
            }
            qry.prepare("UPDATE [Table] SET status=1 WHERE ID=:tableId");
            qry.bindValue(":tableId", ui->tableList->item(ui->tableList->currentRow(), 0)->text().toInt());
            fResult = qry.exec();
            if (!fResult)
            {
                qDebug() << "Update Table Data Error: " << qry.lastError().text();
            }
            loadTableList();
            waitingList();
        }
    }
    else
    {
        // Empty the table after customer has left the premises
        QSqlQuery qry(m_db);
        qry.prepare("UPDATE [Table] SET status=0 WHERE ID=:tableId");
        qry.bindValue(":tableId", ui->tableList->item(ui->tableList->currentRow(), 0)->text().toInt());
        bool fResult = qry.exec();
        if (!fResult)
        {
            qDebug() << "Update Table Data Error: " << qry.lastError().text();
        }
        loadTableList();
    }
}

void MainWindow::on_actionExit_triggered()
{
    closeDatabase();
    close();
}

void MainWindow::on_actionTable_History_triggered()
{
    TableHistoryDialog ft;
    QList <struct Customer> cust;
    QSqlQuery qry("SELECT ID, name, numOfPeople, timestamp FROM Customer WHERE Table_ID IS NOT NULL ORDER BY Timestamp DESC", m_db);
    while (qry.next())
    {
        int id = qry.value("id").toInt();
        QString name  = qry.value("name").toString();
        int numOfPeople = qry.value("numOfPeople").toInt();
        QString timestamp = qry.value("timestamp").toString();
        struct Customer cs = {id,numOfPeople,name, timestamp};
        cust.append(cs);
    }
    ft.setHistory(cust);
    ft.exec();
}

void MainWindow::on_actionAbout_Us_triggered()
{
    QMessageBox messageBox;
    messageBox.setWindowTitle("About this app");
    messageBox.setWindowIcon(QIcon(":/icons/aboutIcon.png"));
    messageBox.setIcon(QMessageBox::Information);
    messageBox.setText("<strong>CPEN6126010 - Cross Platform Application Development Final Project</strong>");
    messageBox.setInformativeText(
        "A Restaurant Waiting List Desktop Application to assist the receptionist "
        "in assigning tables and keeping track of customers.\n"
        "\nMade by:\n"
        "• 2440007062 - Gian Reinfred Athevan\n"
        "• 2440009162 - Matthew Adrianus Mulyono\n"
        "• 2440016262 - Valencia Vananda\n"
    );
    messageBox.exec();
}
