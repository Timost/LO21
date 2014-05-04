#ifndef PROFILER_H
#define PROFILER_H
#include <QString>
#include <QMainWindow>
#include <QMenuBar>
#include "UTProfiler.h"

class Profiler : public QMainWindow
{
    Q_OBJECT

    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;
    QString path;

public:
    explicit Profiler(QWidget *parent = 0);

signals:

    void UvsChargee(bool);

public slots:
    void chargeUVs();
    void editUV();
};

#endif // PROFILER_H
