#ifndef MODIFIERFORM_H
#define MODIFIERFORM_H

#include <QDialog>

namespace Ui {
class modifierform;
}

class modifierform : public QDialog
{
    Q_OBJECT

public:
    explicit modifierform(QWidget *parent = 0);
    ~modifierform();

private:
    Ui::modifierform *ui;
};

#endif // MODIFIERFORM_H
