#ifndef UINAVIGATION_PROTOTYPE_H
#define UINAVIGATION_PROTOTYPE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QtSql>
#include <vector>
#include "adminportal.h"
#include "researcherportal.h"
#include "volunteerrecruiterportal.h"
#include "../dbControl/dbcontrol.h"


QT_BEGIN_NAMESPACE
namespace Ui { class UiNavigation_Prototype; }
QT_END_NAMESPACE

class UiNavigation_Prototype : public QMainWindow
{
    Q_OBJECT

public:
    UiNavigation_Prototype(QWidget *parent = nullptr);
    ~UiNavigation_Prototype();

    dbControl *db = new dbControl("../../2-4_FinalProject/UiNavigation_Prototype/databases/dbms.sqlite");

private slots:
    void on_login_button_clicked();

signals:
    void toAdminPortal(QString username, dbControl *dbcc);
    void toResearcherPortal(QString username);
    void toVolunteerRecruiterPortal(QString username);

private:
    Ui::UiNavigation_Prototype *ui;
    adminPortal * admPortal;
    researcherPortal * resPortal;
    volunteerRecruiterPortal * vrPortal;

    QString validUser();
};
#endif // UINAVIGATION_PROTOTYPE_H
