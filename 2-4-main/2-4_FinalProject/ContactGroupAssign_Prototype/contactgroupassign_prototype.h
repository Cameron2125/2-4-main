#ifndef CONTACTGROUPASSIGN_PROTOTYPE_H
#define CONTACTGROUPASSIGN_PROTOTYPE_H

#include <QMainWindow>

#include "../contact.h"
#include "groupnumsdialog.h"
#include <vector>
#include <time.h>
#include <random>

QT_BEGIN_NAMESPACE
namespace Ui { class ContactGroupAssign_Prototype; }
QT_END_NAMESPACE

class ContactGroupAssign_Prototype : public QMainWindow
{
    Q_OBJECT

public:
    ContactGroupAssign_Prototype(QWidget *parent = nullptr);
    ~ContactGroupAssign_Prototype();

    std::vector<Contact> assignGroups(std::vector<Contact> newContacts);

    Contact c1 = Contact("Decker", "Matthew");
    Contact c2 = Contact("Cena", "John");
    Contact c3 = Contact("Glover", "Donald");
    Contact c4 = Contact("Goldwater", "Barry");
    Contact c5 = Contact("Johnson", "Gary");
    Contact c6 = Contact("Jackson", "Michael");
    Contact c7 = Contact("Bush Sr", "George");
    Contact c8 = Contact("Tentacles", "Squidward");
    Contact c9 = Contact("Never Broke Again", "Youngboy");
    Contact c10 =Contact("Chan", "Jackie");
    Contact c11 =Contact("Black", "Jack");
    Contact c12 =Contact("Harvey", "Steve");
    Contact c13 =Contact("Schneider", "Rob");
    Contact c14 =Contact("Gloop", "Augustus");
    Contact c15 =Contact("Clinton", "Hillary");

    std::vector<Contact> newContacts = {c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15};

private slots:
    void on_beginDemo_clicked();

signals:
    void toGroupNumsWindow(std::vector<Contact> newContacts);

private:
    Ui::ContactGroupAssign_Prototype *ui;
    GroupNumsDialog * grpNums;

    void displayGroups(std::vector<Contact> newContacts);
};
#endif // CONTACTGROUPASSIGN_PROTOTYPE_H
