#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;

private slots:
    void on_addCustomer_clicked();


private:
    void initTableList();
    void tableListClick();
    bool openDatabase();
    void closeDatabase();
    bool loadTableList();
    void waitingList();
    QSqlDatabase m_db;
};

#endif // MAINWINDOW_H
