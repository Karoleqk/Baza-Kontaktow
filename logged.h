#ifndef LOGGED_H
#define LOGGED_H

#include <QMainWindow>

#include "user.h"

namespace Ui {
class Logged;
}

class Logged : public QMainWindow
{
    Q_OBJECT

public:
    explicit Logged(QWidget *parent = nullptr);
    ~Logged();

private:
    Ui::Logged *ui;
};

#endif // LOGGED_H
