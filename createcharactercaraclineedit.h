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
#ifndef CREATECHARACTERCARACLINEEDIT_H
#define CREATECHARACTERCARACLINEEDIT_H

#include <QWidget>
#include <QLineEdit>



class createcharacterCaracLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit createcharacterCaracLineEdit(QWidget *parent = 0);
    ~createcharacterCaracLineEdit();


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

private:
    void startDrag();
    QPoint mouseStartPos;

};

#endif // CREATECHARACTERCARACLINEEDIT_H
