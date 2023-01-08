#ifndef CONTACTEDIT_H
#define CONTACTEDIT_H

#include <QDialog>

namespace Ui {
class ContactEdit;
}

/**
 * @brief allows user to manually input contact
 */
class ContactEdit : public QDialog
{
    Q_OBJECT

public:
    /** constructor */
    explicit ContactEdit(QWidget *parent = nullptr);
    ~ContactEdit();

    /**
     * @brief setData: Method to set the data via QStringList
     * @param data
     */
    void setData(QStringList data);

    /**
     * @brief getData: Method to get the data via QStringList
     * @return data
     */
    QStringList getData();
    
    /**
     * @brief setEditMode: Call this to set the UI for edit mode
     */
    void setEditMode();

    /**
     * @brief setAddMode: Call this to set the UI for add mode
     */
    void setAddMode();

private slots:
    /**
     * @brief on_buttonBox_accepted: Save the contents of the line edit boxes to the data list
     */
    void on_buttonBox_accepted();

    /**
     * @brief on_buttonBox_rejected: Do nothing
     */
    void on_buttonBox_rejected();

private:
    Ui::ContactEdit *ui;
    // Currently loaded data
    QStringList data = QStringList();
};

#endif // CONTACTEDIT_H
