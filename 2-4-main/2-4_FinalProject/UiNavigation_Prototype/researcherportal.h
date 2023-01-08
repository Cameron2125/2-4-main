#ifndef RESEARCHERPORTAL_H
#define RESEARCHERPORTAL_H

#include <QDialog>

namespace Ui {
class researcherPortal;
}

class researcherPortal : public QDialog
{
    Q_OBJECT

public:
    explicit researcherPortal(QWidget *parent = nullptr);
    ~researcherPortal();

public slots:
    void load(QString username);

private:
    Ui::researcherPortal *ui;
};

#endif // RESEARCHERPORTAL_H
