#ifndef MODIFIERNOTE_H
#define MODIFIERNOTE_H

#include <QDialog>
#include "Note.h"

namespace Ui {
class ModifierNote;
}

class ModifierNote : public QDialog
{
    Q_OBJECT

    void connect();
private slots:
    void ok();
    void cancel();

public:
    explicit ModifierNote(QWidget *parent = 0);
    explicit ModifierNote(Note& n, QWidget *parent = 0);
    ~ModifierNote();

private:
    Ui::ModifierNote *ui;
    bool b;
    Note* note;
};

#endif // MODIFIERNOTE_H
