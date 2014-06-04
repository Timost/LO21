#ifndef MODIFIERUV_FEN_H
#define MODIFIERUV_FEN_H

#include <QDialog>

namespace Ui {
class Modifieruv_fen;
}

class Modifieruv_fen : public QDialog
{
    Q_OBJECT

public:
    explicit Modifieruv_fen(QWidget *parent = 0);
    ~Modifieruv_fen();

private:
    Ui::Modifieruv_fen *ui;
};

#endif // MODIFIERUV_FEN_H
