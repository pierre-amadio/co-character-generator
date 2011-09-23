/*
    CO is a small character creation tool to be used with Croniques Oubliées.
    Copyright (C) 2011 Pierre Amadio <pierre.amadio@libertysurf.fr>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "caracroll.h"
#include "ui_caracroll.h"
#include <QDebug>
caracRoll::caracRoll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::caracRoll)
{
    ui->setupUi(this);
    //connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(needToRoll()));
    //connect(this,SIGNAL(letsRoll(QVector<int>)),ui->caracRollView,SLOT(showResult(QVector<int>)));
    connect(this,SIGNAL(showDice1(int)),ui->dv1,SLOT(showResult(int)));
    connect(this,SIGNAL(showDice2(int)),ui->dv2,SLOT(showResult(int)));
    connect(this,SIGNAL(showDice3(int)),ui->dv3,SLOT(showResult(int)));
    connect(this,SIGNAL(showDice4(int)),ui->dv4,SLOT(showResult(int)));

    }

caracRoll::~caracRoll()
{
    delete ui;
}

void caracRoll::showResult(QVector<int> resSet){
    //qDebug()<<"Let s show result for a caracRoll";

    /*
    for(int i=0;i<6;i++){
        qDebug()<<"i="<<i<<" value="<< resSet[i];
    }
    */

    emit(showDice1(resSet[0]));
    emit(showDice2(resSet[1]));
    emit(showDice3(resSet[2]));
    emit(showDice4(resSet[3]));


}
