#include "contactgroupassign_prototype.h"
#include "ui_contactgroupassign_prototype.h"

ContactGroupAssign_Prototype::ContactGroupAssign_Prototype(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ContactGroupAssign_Prototype)
{
    ui->setupUi(this);
}

ContactGroupAssign_Prototype::~ContactGroupAssign_Prototype()
{
    delete ui;
}

std::vector<Contact> ContactGroupAssign_Prototype::assignGroups(std::vector<Contact> newContacts) {
    srand(time(NULL));
    for (int i = 0; i < newContacts.size(); i++) {
        int groupNum = rand() % 3;
        newContacts[i].setAssignmentGroup(groupNum);
    }
    return newContacts;
}

void ContactGroupAssign_Prototype::on_beginDemo_clicked()
{
    newContacts = assignGroups(newContacts);

    grpNums = new GroupNumsDialog(this);

    QObject::connect(this, &ContactGroupAssign_Prototype::toGroupNumsWindow,
                     grpNums, &GroupNumsDialog::getNewContacts);

    emit toGroupNumsWindow(newContacts);

    hide();
    grpNums->show();
}

