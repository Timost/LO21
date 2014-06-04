#ifndef AJOUTERUVFORMATION_FEN_H
#define AJOUTERUVFORMATION_FEN_H

#include <QDialog>

namespace Ui {
class Ajouteruvformation_fen;
}

class Ajouteruvformation_fen : public QDialog
{
    Q_OBJECT

public:
    explicit Ajouteruvformation_fen(QWidget *parent = 0);
    ~Ajouteruvformation_fen();

private:
    Ui::Ajouteruvformation_fen *ui;
};

#endif // AJOUTERUVFORMATION_FEN_H
