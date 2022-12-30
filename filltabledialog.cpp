#include "filltabledialog.h"
#include "qpushbutton.h"
#include "ui_filltabledialog.h"
#include <QDebug>

fillTableDialog::fillTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fillTableDialog)
{
    ui->setupUi(this);

}

struct Customer{
    int id;
    int numOfPeople;
    QString name;
};

fillTableDialog::~fillTableDialog()
{
    delete ui;
}

void fillTableDialog::initTableList(){
    QStringList headers;
    headers << "Name" << "Number of People"<< "Action";
    ui->tableWidget->setColumnCount(headers.length());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setColumnWidth(1, 200);


    for(int i=0; i < waitinglist.length(); i++){

        struct Customer cs = waitinglist.value(i);

        int nRowCount = ui->tableWidget->rowCount();

        ui->tableWidget->setRowCount(nRowCount+1);
        ui->tableWidget->setItem(nRowCount, 0, new QTableWidgetItem(cs.name));
        ui->tableWidget->setItem(nRowCount, 1, new QTableWidgetItem(QString::number(cs.numOfPeople)));
        ui->tableWidget->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
        ui->tableWidget->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
        QPushButton *action_btn = new QPushButton();
//        QObject::connect(action_btn, &QPushButton::clicked, this, [this]{tableListClick(9);});
        action_btn->setIcon(QIcon(":/icons/fillTable.png"));
        ui->tableWidget->setCellWidget(nRowCount, 2, action_btn);
    }

}

void fillTableDialog::setWaitingList(const QList<struct Customer> list){
    qDebug() << list.length();
    waitinglist = list;
    initTableList();
}

void fillTableDialog::on_tableWidget_cellClicked(int row, int column)
{

}

