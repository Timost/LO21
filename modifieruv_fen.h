#ifndef MODIFIERUV_FEN_H
#define MODIFIERUV_FEN_H
#include <QObject>
#include <QDialog>
#include "uv.h"
#include "Categorie.h"

namespace Ui {
class Modifieruv_fen;
}

class Modifieruv_fen : public QDialog
{
    Q_OBJECT

private slots:
    void ok();
    void cancel();
    void updateCredits();
    void afficheCredits(QString q);

public:
    explicit Modifieruv_fen(QWidget *parent = 0);
    explicit Modifieruv_fen(UV&, QWidget *parent = 0);
    ~Modifieruv_fen();

private:
    Ui::Modifieruv_fen *ui;
    UV* uv;
    bool b;
    std::map<Categorie, unsigned int> cat;
};

#endif // MODIFIERUV_FEN_H
