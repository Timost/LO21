#ifndef QTGRAPHTOOLS_H
#define QTGRAPHTOOLS_H

#include <QCheckBox>

class MyCheckBox : public QCheckBox
{
     Q_OBJECT

private:
    int numero;
public:
    MyCheckBox(int i): QCheckBox(),numero(i){}
    int getNumero(){return numero;}
public slots:
    void isChecked(int s)
    {
        if(s==2)
        {
            emit addMyNumber(numero);
        }
        else if(s==0)
        {
            emit removeMyNumber(numero);
        }
    }
signals:
    void addMyNumber(int i);
    void removeMyNumber(int i);
};

#endif // QTGRAPHTOOLS_H
