#ifndef AJOUTERETUDIANT_FEN_H
#define AJOUTERETUDIANT_FEN_H

#include <QDialog>

namespace Ui {
class AjouterEtudiant_fen;
}

class AjouterEtudiant_fen : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterEtudiant_fen(QWidget *parent = 0);
    ~AjouterEtudiant_fen();

private:
    Ui::AjouterEtudiant_fen *ui;
};

#endif // AJOUTERETUDIANT_FEN_H
