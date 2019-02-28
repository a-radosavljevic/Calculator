#include "widget.h"
#include "ui_widget.h"
#include<qmessagebox.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    calculator(new CalculatorLogic(this))
{
    ui->setupUi(this);

//    foreach (QPushButton v, ui->buttonGroup) {
//        connect(v,SIGNAL(clicked(bool)),this,SLOT(onBtnClicked()));
//    }

    QList<QPushButton*> bList = this->findChildren<QPushButton*>();
    foreach (QPushButton *b, bList) {
        connect(b,SIGNAL(clicked(bool)),this,SLOT(onBtnClicked()));
    }

    connect(calculator,SIGNAL(resultChanged(QString)),this,SLOT(onResultChanged(QString)));
    connect(calculator,SIGNAL(resultHistoryChanged(QString)),this,SLOT(onResultHistoryChanged(QString)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onBtnClicked()
{
    QPushButton *button = (QPushButton *)sender();
    this->calculator->doCommand(button->text());
}

void Widget::onResultChanged(QString string)
{
    ui->leResult->setText(string);
}

void Widget::onResultHistoryChanged(QString string)
{
    ui->pteHistory->insertPlainText("\n" + string);
}
