#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QListWidget>
#include <QFileDialog>
#include "../dbControl/dbcontrol.h"
#include "../date.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Login_But_pressed();

    int validUser();

    void on_Enter_Contact_But_pressed();

    void on_Log_Recruitment_Attempt_But_pressed();

    void on_Change_Vol_Stat_But_pressed();

    void on_Add_Incentive_But_pressed();

    void on_Contact_But_pressed();

    void on_Contact_Relation_But_2_pressed();

    void on_View_Contact_But_pressed();

    void on_Data_Analysis_But_pressed();

    void on_Contact_Relation_But_1_pressed();

    void on_Set_Active_But_pressed();

    void on_Set_Not_Active_But_pressed();

    void on_Return_To_Portal_But_pressed();

    void on_Contact_List_itemPressed(QListWidgetItem *item);

    void on_FtoF_Contact_List_itemPressed(QListWidgetItem *item);

    void on_Add_Rec_Attempt_But_pressed();

    void on_Return_To_Portal_But_2_pressed();

    void on_Yes_Box_pressed();

    void on_No_Box_pressed();

    void on_Not_Sure_Box_pressed();

    void setContactGroups();

    void on_Input_Contacts_csv_But_pressed();

    void on_Return_To_Portal_But_3_pressed();

    void on_Add_Contact_But_pressed();

    void on_Input_Contacts_Man_But_pressed();

    void on_Return_to_Add_Contact_But_pressed();

    void on_Contact_Table_pressed(const QModelIndex &index);

    void on_Edit_Data_But_pressed();

    void on_Edit_Contact_But_pressed();

    void on_Delete_Contact_But_pressed();

    void on_Return_To_Portal_But_4_pressed();

    void on_Remove_DP_Inc_But_pressed();

    void on_DP_Table_pressed(const QModelIndex &index);

    void on_TB_Table_pressed(const QModelIndex &index);

    void on_Remove_TB_Inc_But_pressed();

    void on_Add_DP_Inc_But_2_pressed();

    void on_Add_TB_Incentive_But_pressed();

    void on_Add_TB_Inc_But_pressed();

    void on_Add_DP_Inc_But_pressed();

    void on_Return_To_Portal_But_5_pressed();

private:
    Ui::MainWindow *ui;
    dbControl db;

    std::string update;
    int success;
    QString user;
    QString contactDataChange;
    QString cidContactDataChange;
    QString typeData;
    QString userVID;

};
#endif // MAINWINDOW_H
