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
#ifndef SHEETVIEWER_H
#define SHEETVIEWER_H

#include "cocharacter.h"
#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QImage>

class sheetViewer : public QWidget
{
    Q_OBJECT

public:
    explicit sheetViewer(QWidget *parent = 0);
    ~sheetViewer();
    QSize sizeHint() const;
    void setCharacter(int charId);
    QImage getImage();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap * sheetPixMap;
    coCharacter * character;
    void drawStuff(QPainter * painter);
};


#endif // SHEETVIEWER_H
