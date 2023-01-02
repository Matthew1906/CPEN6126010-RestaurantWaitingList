#include <QDebug>
#include <QPushButton>
#include "customer.h"
#include "filltabledialog.h"
#include "ui_filltabledialog.h"

fillTableDialog::fillTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fillTableDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Fill Table Dialog");
    this->setWindowIcon(QIcon(":/icons/eatIcon.png"));
}

fillTableDialog::~fillTableDialog()
{
    delete ui;
}

void fillTableDialog::initTableList()
{
    // Setup Headers
    QStringList headers;
    headers << "ID" << "Name" << "Number of People"<< "Action";
    ui->tableWidget->setColumnCount(headers.length());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setColumnWidth(1, 200);
    // Insert data into table
    for(int i=0; i < waitinglist.length(); i++)
    {
        struct Customer cs = waitinglist.value(i);
        int nRowCount = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(nRowCount+1);
        ui->tableWidget->setItem(nRowCount, 0, new QTableWidgetItem(QString::number(cs.id)));
        ui->tableWidget->setItem(nRowCount, 1, new QTableWidgetItem(cs.name));
        ui->tableWidget->setItem(nRowCount, 2, new QTableWidgetItem(QString::number(cs.numOfPeople)));
        ui->tableWidget->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
        ui->tableWidget->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
        ui->tableWidget->item(nRowCount, 2)->setFlags(Qt::ItemIsEditable);
        QPushButton *action_btn = new QPushButton();
        QObject::connect(action_btn, &QPushButton::clicked, this, &fillTableDialog::setChoice);
        action_btn->setIcon(QIcon(":/icons/fillTable.png"));
        ui->tableWidget->setCellWidget(nRowCount, 3, action_btn);
    }

}

void fillTableDialog::setWaitingList(const QList<struct Customer> list)
{
    // Initialize customer list
    waitinglist = list;
    initTableList();
}

void fillTableDialog::setChoice()
{
    // Set which customer gets the table
    int row = ui->tableWidget->currentRow();
    toAdd = ui->tableWidget->item(row, 0)->text().toInt();
    this->accept();
}
