#ifndef CALCULATORLOGIC_H
#define CALCULATORLOGIC_H

#include <QObject>

class CalculatorLogic : public QObject
{
    Q_OBJECT

    QString first;
    QString second;
    QString operation;
    bool isFloatFirst;
    bool isFloatSecond;
public:
    explicit CalculatorLogic(QObject *parent = nullptr);

    void doCommand(QString);
signals:
    void resultChanged(QString);
    void resultHistoryChanged(QString);

public slots:
};


#endif // CALCULATORLOGIC_H
