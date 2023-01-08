#include "groupnumsdialog.h"
#include "ui_groupnumsdialog.h"

GroupNumsDialog::GroupNumsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupNumsDialog)
{
    ui->setupUi(this);
}

GroupNumsDialog::~GroupNumsDialog()
{
    delete ui;
}

void GroupNumsDialog::getNewContacts(std::vector<Contact> newContacts) {
    this->newContacts = newContacts;
    displayGroups();
}

void GroupNumsDialog::displayGroups() {
    QListWidget *friendToFriend_list = ui->friendToFriend_list;
    QListWidget *generic_list = ui->generic_list;
    QListWidget *noContact_list = ui->noContact_list;

    for (int i = 0; i < newContacts.size(); i++) {
        Contact contact = newContacts[i];
        QString fullName = QString::fromStdString(contact.lastName + ", " + contact.firstName);

        if (contact.getAssignmentGroup() == 0) {
            new QListWidgetItem(fullName, friendToFriend_list);
        }
        else if (contact.getAssignmentGroup() == 1) {
            new QListWidgetItem(fullName, generic_list);
        }
        else if (contact.getAssignmentGroup() == 2) {
            new QListWidgetItem(fullName, noContact_list);
        }
    }

    QString totalFriend = QString::fromStdString("Total:" + std::to_string(friendToFriend_list->count()));
    QString totalGeneric = QString::fromStdString("Total:" + std::to_string(generic_list->count()));
    QString totalNoContact = QString::fromStdString("Total:" + std::to_string(noContact_list->count()));

    ui->friendTotal_label->setText(totalFriend);
    ui->genericTotal_label->setText(totalGeneric);
    ui->noContactTotal_label->setText(totalNoContact);
}
