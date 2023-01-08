#ifndef RESEARCHERPORTAL_H
#define RESEARCHERPORTAL_H

#include <QMainWindow>

//remove this inclusion when done
#include <iostream>

#include "./dbControl/dbcontrol.h"
#include "./DataRetrievalDemo/dataretrieval.h"
#include "datagui.h"
#include "viewcontacts.h"
#include "contactviewer.h"

namespace Ui {
class ResearcherPortal;
}

class ResearcherPortal : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief ResearcherPortal the constructor for teh ResearcherPortal
     * \param parent the parent widget
     */
    explicit ResearcherPortal(QWidget *parent = nullptr);
    ~ResearcherPortal();

    QString user;

public slots:
    /*!
     * \brief load loads in the window from another window
     * \param username the username of the researcher
     * \param dbcc the database passed along
     */
    void load(QString username, dbControl *dbcc);

private slots:
    /*!
     * \brief on_viewContactButton_pressed button that opens ContactViewer
     */
    void on_viewContactButton_pressed();

    /*!
     * \brief on_dataAnalysisButton_pressed button that opens datagui
     */
    void on_dataAnalysisButton_pressed();

signals:
    /*!
     * \brief toDR signal to help go to datagui window
     * \param dbcc database passed along
     */
    void toDR(dbControl *dbcc);
    /*!
     * \brief toCV signal to go to contactviewer
     * \param username username of user
     * \param dbcc database passed along
     */
    void toCV(QString username, dbControl *dbcc);

private:
    Ui::ResearcherPortal *ui;
    DataGui *dr;
    dbControl *db;
    ContactViewer *cv;
};

#endif // RESEARCHERPORTAL_H
