#include "contactedit.h"
#include "ui_contactedit.h"

ContactEdit::ContactEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContactEdit)
{
    ui->setupUi(this);
}

ContactEdit::~ContactEdit()
{
    delete ui;
}

// Method to set the data via QStringList
void ContactEdit::setData(QStringList data) {
    this->data = data;
    // Populate the line edit boxes with data
    ui->lineEdit_name->setText(data[3]);
    ui->lineEdit_age->setText(data[4]);
    ui->lineEdit_location->setText(data[5]);
    ui->lineEdit_gender->setText(data[6]);
    ui->lineEdit_ethnicity->setText(data[7]);
    ui->lineEdit_education->setText(data[8]);
    ui->lineEdit_occupation->setText(data[9]);
    ui->lineEdit_email->setText(data[10]);
    ui->lineEdit_phone->setText(data[11]);
    ui->plainTextEdit_info->setPlainText(data[13]);
}

// Method to get the data via QStringList
QStringList ContactEdit::getData() {
    return data;
}

// Sets UI to edit mode
void ContactEdit::setEditMode() {
    // Update the window title
    this->setWindowTitle("Edit Contact");
}

// Sets UI to add mode
void ContactEdit::setAddMode() {
    // Update the window title
    this->setWindowTitle("Add Contact");
}

void ContactEdit::on_buttonBox_accepted()
{
    // Save the contents of the line edit boxes to the data list
    data[3] = ui->lineEdit_name->text();
    data[4] = ui->lineEdit_age->text();
    data[5] = ui->lineEdit_location->text();
    data[6] = ui->lineEdit_gender->text();
    data[7] = ui->lineEdit_ethnicity->text();
    data[8] = ui->lineEdit_education->text();
    data[9] = ui->lineEdit_occupation->text();
    data[10] = ui->lineEdit_email->text();
    data[11] = ui->lineEdit_phone->text();
    data[13] = ui->plainTextEdit_info->toPlainText();
}


void ContactEdit::on_buttonBox_rejected()
{

}

