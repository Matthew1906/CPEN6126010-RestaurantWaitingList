#include "customer.h"
#include "tablehistorydialog.h"
#include "ui_tablehistorydialog.h"

TableHistoryDialog::TableHistoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableHistoryDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Table Occupancy History");
    this->setWindowIcon(QIcon(":/icons/historyIcon.png"));
}

TableHistoryDialog::~TableHistoryDialog()
{
    delete ui;
}

void TableHistoryDialog::initHistory()
{
    // Setup Headers
    QStringList headers;
    headers << "Name" << "Size"<< "Timestamp";
    ui->tableWidget->setColumnCount(headers.length());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setColumnWidth(1, 135);
    ui->tableWidget->setColumnWidth(2, 40);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    // Insert data into table
    for(int i=0; i < histories.length(); i++)
    {
        struct Customer cs = histories.value(i);
        int nRowCount = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(nRowCount+1);
        ui->tableWidget->setItem(nRowCount, 0, new QTableWidgetItem(cs.name));
        ui->tableWidget->setItem(nRowCount, 1, new QTableWidgetItem(QString::number(cs.numOfPeople)));
        ui->tableWidget->setItem(nRowCount, 2, new QTableWidgetItem(cs.timestamp));
        ui->tableWidget->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
        ui->tableWidget->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
        ui->tableWidget->item(nRowCount, 2)->setFlags(Qt::ItemIsEditable);
        ui->tableWidget->item(nRowCount, 0)->setTextAlignment( Qt::AlignCenter );
        ui->tableWidget->item(nRowCount, 1)->setTextAlignment( Qt::AlignCenter );
        ui->tableWidget->item(nRowCount, 2)->setTextAlignment( Qt::AlignCenter );
    }

}

void TableHistoryDialog::setHistory(const QList<struct Customer> list)
{
    // Initialize customer list
    histories = list;
    initHistory();
}
