#ifndef AJOUTERFORMATION_FEN_H
#define AJOUTERFORMATION_FEN_H

#include <QDialog>

namespace Ui {
class ajouterformation_fen;
}

class ajouterformation_fen : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterformation_fen(QWidget *parent = 0);
    ~ajouterformation_fen();

private:
    Ui::ajouterformation_fen *ui;
};

#endif // AJOUTERFORMATION_FEN_H
