/*
    CO is a small character creation tool to be used with Chroniques Oubliées.
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
#include "diceview.h"
#include "ui_diceview.h"
#include <QDebug>
#include <QMessageBox>
#include <QString>

DiceView::DiceView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiceView)
{
    ui->setupUi(this);
    //picDir="/home/melmoth/dev/co/DiceView/DiceView/images";
    for(int i=1;i<=6;i++){
        QString fileName;
        QString format;
        //format="%1/%2-small.jpg";
        format=":/images/d6-%1";
        //fileName=format.arg(picDir).arg(i);
        fileName=format.arg(i);
        dicePicMap.insert(i,fileName);
    }

    /*
    QMapIterator<int,QString> i(dicePicMap);
    while(i.hasNext()){
        i.next();
        qDebug()<<i.key()<<i.value();
    }
    */

}

DiceView::~DiceView()
{
    delete ui;
}

void DiceView::setText(QString snt){
   //qDebug()<< "Why should i override setText() ?"<< snt;
}

void DiceView::showResult(int res){
    //qDebug()<<"Showing result"<<res;
    QImage image(dicePicMap.value(res));


    if (image.isNull()) {
                QMessageBox::information(this, tr("Image Viewer"),
                                         tr("Cannot load %1.").arg("plop"));
                return;
            }


    ui->DiceViewPixmap->setPixmap(QPixmap::fromImage(image));
    ui->DiceViewPixmap->setScaledContents(true);


}
