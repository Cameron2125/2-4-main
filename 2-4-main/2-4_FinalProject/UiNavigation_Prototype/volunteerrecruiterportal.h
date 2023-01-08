#ifndef VOLUNTEERRECRUITERPORTAL_H
#define VOLUNTEERRECRUITERPORTAL_H

#include <QDialog>

namespace Ui {
class volunteerRecruiterPortal;
}

class volunteerRecruiterPortal : public QDialog
{
    Q_OBJECT

public:
    explicit volunteerRecruiterPortal(QWidget *parent = nullptr);
    ~volunteerRecruiterPortal();

public slots:
    void load(QString username);

private:
    Ui::volunteerRecruiterPortal *ui;

};

#endif // VOLUNTEERRECRUITERPORTAL_H
