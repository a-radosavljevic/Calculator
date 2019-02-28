#include "calculatorlogic.h"

CalculatorLogic::CalculatorLogic(QObject *parent) : QObject(parent)
{
    first=second=operation="";
    isFloatFirst=false;
    isFloatSecond=false;
}

void CalculatorLogic::doCommand(QString string)
{
    if(string!="=")
    {
        bool ok;
        int value = string.toInt(&ok);
        if(ok && operation=="")
        {
            first = first+string;
            emit resultChanged(first);
        }
        else if(ok && operation!="")
        {
            second=second+string;
            emit resultChanged(second);
        }
        else if(string=="C")
        {
            first=second=operation="";
            emit resultChanged("0");
        }
        else if(string=="<-")
        {
            if(operation=="")
            {
                first=first.mid(0,first.length()-1);
                emit resultChanged(first);
            }
            else
            {
                second=second.mid(0,second.length()-1);
                emit resultChanged(second);
            }
        }
        else if (string=="±")
        {
            if(operation=="")
            {
                if(first.mid(0,1)=="-")
                    first=first.mid(1,first.length()-1);
                else
                    first="-" + first;
                emit resultChanged(first);
            }
            else
            {
                if(second.mid(0,1)=="-")
                    second=second.mid(1,second.length()-1);
                else
                    second="-" + second;
                emit resultChanged(second);
            }
        }
        else if(string=="√")
        {
            float result = sqrt(first.toFloat());
            emit resultChanged(QString::number(result));
            emit resultHistoryChanged("SQRT("+first+")="+QString::number(result));
            first=second=operation="";
            isFloatFirst=false;
            isFloatSecond=false;
            emit resultChanged("0");
        }
        else if(string==".")
        {
            if(isFloatFirst==false || isFloatSecond==false)
            {
                if(operation=="" && isFloatFirst==false)
                {
                    first=first+".";
                    emit resultChanged(first);
                    isFloatFirst=true;
                }
                else
                {
                    second=second+".";
                    emit resultChanged(second);
                    isFloatSecond=true;
                }
            }
        }
        else
        {
            operation=string;
            emit resultChanged("0");
        }
    }
    else
    {
        int result;
        float resultFloat;
        if(operation=='+')
        {
            if(isFloatFirst==false && isFloatSecond==false)
                result = first.toInt() + second.toInt();
            else
                resultFloat=first.toFloat() + second.toFloat();
        }
        else if (operation == '-')
        {
            if(isFloatFirst==false && isFloatSecond==false)
                result = first.toInt() - second.toInt();
            else
                resultFloat=first.toFloat() - second.toFloat();
        }
        else if (operation == '*')
        {
            if(isFloatFirst==false && isFloatSecond==false)
                result = first.toInt() * second.toInt();
            else
                resultFloat=first.toFloat() * second.toFloat();
        }
        else if (operation == '/')
        {
            if (second != "" && second != "0")
                resultFloat=first.toFloat() / second.toFloat();
            else
            {
                emit resultChanged("Unpossible expression");
                first=second=operation="";
                isFloatFirst=false;
                isFloatSecond=false;
            }
            isFloatFirst=true;
        }
        QString exspression;
        if(isFloatFirst==false && isFloatSecond==false)
        {
            emit resultChanged(QString::number(result));
            exspression = first + operation + second + string + QString::number(result);
        }
        else
        {
            emit resultChanged(QString::number(resultFloat));
            exspression = first + operation + second + string + QString::number(resultFloat);
        }
        emit resultHistoryChanged(exspression);
        isFloatFirst=false;
        isFloatSecond=false;
        first=second=operation="";
    }
}

