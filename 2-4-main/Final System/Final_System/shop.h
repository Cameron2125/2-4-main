#ifndef SHOP_H
#define SHOP_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QPixmap>
#include "purchasedbadge.h"
#include "dbControl/dbcontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Shop; }
QT_END_NAMESPACE

class Shop : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Shop Constructor for shop class
     * \param parent the parent widget
     */
    Shop(QWidget *parent = nullptr);
    /*!
     * \brief Shop Constructor for unit testing
     * \param i random integer value
     */
    Shop(int i);
    ~Shop();
    /*!
     * \brief load loads the shop from another window
     * \param i the id of the user
     * \param dbc
     */
    void load(int i, dbControl *dbc);
    /*!
     * \brief load2 the second load method
     * \param pic the picture bought
     */
    void load2(QString pic);

private slots:


    /*!
     * \brief on_pushButton_clicked the pushbutton to purchase badge1
     */
    void on_pushButton_clicked();
    /*!
     * \brief on_pushButton_clicked2 the pushbutton to purchase badge2
     */
    void on_pushButton_2_clicked();
    /*!
     * \brief on_pushButton_clicked3 the pushbutton to purchase badge3
     */
    void on_pushButton_3_clicked();
    /*!
     * \brief on_pushButton_clicked4 the pushbutton to purchase badge4
     */
    void on_pushButton_4_clicked();
    /*!
     * \brief on_pushButton_clicked5 the pushbutton to purchase badge5
     */
    void on_pushButton_5_clicked();
    /*!
     * \brief on_pushButton_clicked6 the pushbutton to purchase badge6
     */
    void on_pushButton_6_clicked();
    /*!
     * \brief on_pushButton_clicked7 the pushbutton to purchase badge7
     */
    void on_pushButton_7_clicked();
    /*!
     * \brief on_pushButton_clicked8 the pushbutton to purchase badge8
     */
    void on_pushButton_8_clicked();
    /*!
     * \brief on_pushButton_clicked9 the pushbutton to purchase badge9
     */
    void on_pushButton_9_clicked();
    /*!
     * \brief on_pushButton_clicked10 the pushbutton to purchase badge10
     */
    void on_pushButton_10_clicked();
    /*!
     * \brief on_pushButton_clicked11 the pushbutton to purchase badge11
     */
    void on_pushButton_11_clicked();
    /*!
     * \brief on_pushButton_clicked12 the pushbutton to purchase badge12
     */
    void on_pushButton_12_clicked();
    /*!
     * \brief on_pushButton_clicked13 the pushbutton to purchase badge13
     */
    void on_pushButton_13_clicked();
    /*!
     * \brief on_pushButton_clicked14 the pushbutton to purchase badge14
     */
    void on_pushButton_14_clicked();
    /*!
     * \brief on_pushButton_clicked15 the pushbutton to purchase badge15
     */
    void on_pushButton_15_clicked();
    /*!
     * \brief on_pushButton_clicked16 the pushbutton to purchase badge16
     */
    void on_pushButton_16_clicked();
    void closeEvent(QCloseEvent *event);

signals:
    void editClosed(int vid, dbControl *db);
    void toPurchasedBadge(QString pic);

private:
    void notEnoughPoints(int points, int price);

    void purchased(QString pic);
    bool UI;
    Ui::Shop *ui;
    dbControl *db;
    int id;
    PurchasedBadge *pb;
};
#endif // SHOP_H
