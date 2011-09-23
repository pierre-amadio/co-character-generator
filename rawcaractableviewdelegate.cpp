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
#include "rawcaractableviewdelegate.h"
#include <QDebug>
#include <QStyledItemDelegate>
#include <QPainter>
#include "corules.h"
#include <QColor>


rawCaracTableViewDelegate::rawCaracTableViewDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    //qDebug()<<"Creating a delegate";
}


void rawCaracTableViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    int modifier;
    coRules gamesRules=coRules();
    modifier=gamesRules.getCaracModifier(index.data( Qt::DisplayRole ).toInt());
    QColor color;
    if(modifier<0){
        color=QColor(255, 0, 0, 255);
    }
    if(modifier==0){
        color=QColor(100,100,100,255);
    }
    if(modifier>0){
        color=QColor(100,100,255,255);
    }

    painter->setPen(color);
    painter->drawText(option.rect,Qt::AlignCenter, index.data( Qt::DisplayRole ).toString());


}

