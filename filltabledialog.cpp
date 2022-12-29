#include "filltabledialog.h"
#include "qpushbutton.h"
#include "ui_filltabledialog.h"

fillTableDialog::fillTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fillTableDialog)
{
    ui->setupUi(this);

}

fillTableDialog::~fillTableDialog()
{
    delete ui;
}

void fillTableDialog::initTableList(){
    QStringList headers;
    headers << "Name" << "Capacity"<< "Action";
    ui->tableWidget->setColumnCount(headers.length());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);


    for(int i=0; i < waitinglist.length(); i++){

        QString str = waitinglist.value(i);


        QStringList values = str.split("\n");
        QString name = values.value(0).split(":").value(1).trimmed();
        QString num = values.value(1).split(":").value(1).trimmed();

        int nRowCount = ui->tableWidget->rowCount();

        ui->tableWidget->setRowCount(nRowCount+1);
        ui->tableWidget->setItem(nRowCount, 0, new QTableWidgetItem(name));
        ui->tableWidget->setItem(nRowCount, 1, new QTableWidgetItem(num));
        ui->tableWidget->item(nRowCount, 0)->setFlags(Qt::ItemIsEditable);
        ui->tableWidget->item(nRowCount, 1)->setFlags(Qt::ItemIsEditable);
        QPushButton *action_btn = new QPushButton();
//        QObject::connect(action_btn, &QPushButton::clicked, this, [this]{tableListClick(9);});
        action_btn->setIcon(QIcon(":/icons/fillTable.png"));
        ui->tableWidget->setCellWidget(nRowCount, 2, action_btn);
    }

}

void fillTableDialog::setWaitingList(const QStringList list){
    qDebug() << list.length();
    waitinglist = list;
    initTableList();
}

void fillTableDialog::on_tableWidget_cellClicked(int row, int column)
{

}

