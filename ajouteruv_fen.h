#ifndef AJOUTERUV_FEN_H
#define AJOUTERUV_FEN_H

#include <QDialog>

namespace Ui {
class AjouterUv_fen;
}

class AjouterUv_fen : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterUv_fen(QWidget *parent = 0);
    ~AjouterUv_fen();

private:
    Ui::AjouterUv_fen *ui;
};

#endif // AJOUTERUV_FEN_H
