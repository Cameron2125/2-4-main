#ifndef PURCHASEDBADGE_H
#define PURCHASEDBADGE_H

#include <QMainWindow>

namespace Ui {
class PurchasedBadge;
}

class PurchasedBadge : public QMainWindow
{
    Q_OBJECT

public:
    explicit PurchasedBadge(QWidget *parent = nullptr);
    ~PurchasedBadge();
    void load(QString image);

private slots:
    void closeEvent(QCloseEvent *event);

signals:
    void editClosed(QString image);

private:
    Ui::PurchasedBadge *ui;
    QString pic;
};

#endif // PURCHASEDBADGE_H
