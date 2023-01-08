#ifndef VIEWCONTACTS_H
#define VIEWCONTACTS_H

#include <QMainWindow>

namespace Ui {
class ViewContacts;
}

class ViewContacts : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief ViewContacts Constructors for ViewContacts
     * \param parent the parent widget
     */
    explicit ViewContacts(QWidget *parent = nullptr);
    ~ViewContacts();

private:
    //the ui for system
    Ui::ViewContacts *ui;
};

#endif // VIEWCONTACTS_H
