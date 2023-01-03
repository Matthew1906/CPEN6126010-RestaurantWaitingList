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
    void on_actionExit_triggered();
    void on_actionTable_History_triggered();
    void on_actionAbout_Us_triggered();

private:
    QSqlDatabase m_db;
    bool openDatabase();
    void closeDatabase();
    void initTableList();
    bool loadTableList();
    void tableListClick();
    void waitingList();
    void addCustomer();
};

#endif // MAINWINDOW_H
