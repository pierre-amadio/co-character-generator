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
#include "sheetviewer.h"
#include "corules.h"
#include <QDebug>
#include <QPainter>
#include <QString>
#include <QFont>
#include <QSize>
#include <QImage>

sheetViewer::sheetViewer(QWidget *parent) :
        QWidget(parent)
{
        qDebug()<<"A new viewer";

        sheetPixMap= new QPixmap(":/images/sheetTemplate.jpg");
        this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        //this->setMinimumSize(200,200);
        setMinimumSize(sheetPixMap->size());
        //update();
}

sheetViewer::~sheetViewer()
{
    delete sheetPixMap;
    delete character;
}

QSize sheetViewer::sizeHint() const{
    //QSize size(100,20);
    QSize size=sheetPixMap->size();
    qDebug()<<"Returning the following sizeHint"<<size;
    return size;
}

void sheetViewer::setCharacter(int charId){
    character=new coCharacter(charId);
}

void sheetViewer::drawStuff(QPainter *painter) {
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->setPen(QPen(Qt::black,12,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));
    painter->setBrush(QBrush(Qt::green,Qt::SolidPattern));

    QRectF target=sheetPixMap->rect();
    QRectF source=sheetPixMap->rect();
    painter->drawPixmap(target, *sheetPixMap, source);

    painter->setRenderHint(QPainter::Antialiasing,true);
    //painter.setPen(QPen(Qt::black,200));
    QFont boldf ("Helvetica", 12, QFont::Normal);
    QFont f ("Helvetica", 12, QFont::Normal);
    boldf.setBold(true);
    painter->setFont(boldf);
    painter->drawText(60,100,character->name);
    painter->setFont(f);

    painter->drawText(320,180,QString::number(character->strenght));
    painter->drawText(360,180,QString::number(character->modStrenght));

    painter->drawText(320,202,QString::number(character->dex));
    painter->drawText(360,202,QString::number(character->modDex));

    painter->drawText(320,224,QString::number(character->con));
    painter->drawText(360,224,QString::number(character->modCon));

    painter->drawText(320,246,QString::number(character->intelligence));
    painter->drawText(360,246,QString::number(character->modIntelligence));

    painter->drawText(320,268,QString::number(character->sag));
    painter->drawText(360,268,QString::number(character->modSag));

    painter->drawText(320,290,QString::number(character->cha));
    painter->drawText(360,290,QString::number(character->modCha));

    painter->drawText(520,180,QString::number(character->attackContact));
    painter->drawText(520,202,QString::number(character->attackDistance));
    if(character->charClass==ID_PRIEST | character->charClass==ID_WIZARD) {
        painter->drawText(520,224,QString::number(character->attackMagical));
    }

    painter->drawText(355,340,QString::number(character->pv));
    painter->drawText(515,340,QString::number(character->def));
    painter->drawText(375,407,QString::number(character->dv));


    coRules rules=coRules();
    QFont smallFont ("Helvetica", 8, QFont::Normal);
    painter->setFont(smallFont);
    QString className=rules.getClassName(character->charClass);
    QString raceName=rules.getRaceName(character->race);
    painter->drawText(68,439,className);
    painter->drawText(60,425,raceName);
    //painter.save();

}

void sheetViewer::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    drawStuff(&painter);
}

QImage sheetViewer::getImage(){
    QImage image(sheetPixMap->size(),QImage::Format_ARGB32_Premultiplied);
    QPainter imagePainter(&image);
    imagePainter.setRenderHint(QPainter::Antialiasing,true);
    imagePainter.eraseRect(rect());
    drawStuff(&imagePainter);
    return image;
}


