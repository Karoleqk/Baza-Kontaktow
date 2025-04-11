#ifndef CREATECONTACT_H
#define CREATECONTACT_H

#include <QDialog>

namespace Ui {
class CreateContact;
}

class CreateContact : public QDialog
{
    Q_OBJECT

public:
    explicit CreateContact(QWidget *parent = nullptr);
    ~CreateContact();

private:
    Ui::CreateContact *ui;
};

#endif // CREATECONTACT_H
