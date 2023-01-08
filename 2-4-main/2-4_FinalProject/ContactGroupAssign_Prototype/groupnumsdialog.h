#ifndef GROUPNUMSDIALOG_H
#define GROUPNUMSDIALOG_H

#include <QDialog>
#include "../contact.h"

namespace Ui {
class GroupNumsDialog;
}

class GroupNumsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GroupNumsDialog(QWidget *parent = nullptr);
    ~GroupNumsDialog();

    std::vector<Contact> newContacts;

public slots:
    void getNewContacts(std::vector<Contact> newContacts);

private:
    Ui::GroupNumsDialog *ui;
    void displayGroups();
};

#endif // GROUPNUMSDIALOG_H
