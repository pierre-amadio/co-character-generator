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
#include "createcharactercaraclineedit.h"
#include <QLineEdit>
#include <QDebug>
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>



createcharacterCaracLineEdit::createcharacterCaracLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    setAcceptDrops(true);
}

createcharacterCaracLineEdit::~createcharacterCaracLineEdit()
{

}


void createcharacterCaracLineEdit::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton) {
         mouseStartPos=event->pos();
     }
     QLineEdit::mousePressEvent(event);
}

void createcharacterCaracLineEdit::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton) {
        int distance=(event->pos()-mouseStartPos).manhattanLength();
        if(distance>= QApplication::startDragDistance()){
            startDrag();
        }
    }
    QLineEdit::mouseMoveEvent(event);
}

void createcharacterCaracLineEdit::dragEnterEvent(QDragEnterEvent *event){
createcharacterCaracLineEdit * sourceLineEdit = qobject_cast<createcharacterCaracLineEdit *>(event->source());
if(sourceLineEdit && sourceLineEdit!=this) {
    event->setDropAction(Qt::MoveAction);
    event->accept();
    }
}

void createcharacterCaracLineEdit::dragMoveEvent(QDragMoveEvent *event){
    createcharacterCaracLineEdit * sourceLineEdit = qobject_cast<createcharacterCaracLineEdit *>(event->source());
    if(sourceLineEdit && sourceLineEdit!=this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
        }

}


void createcharacterCaracLineEdit::dropEvent(QDropEvent *event){
    //qDebug()<<"Droping stuff";
    createcharacterCaracLineEdit * sourceLineEdit = qobject_cast<createcharacterCaracLineEdit *>(event->source());

    if(sourceLineEdit && sourceLineEdit!=this) {
        QString origSourceText=sourceLineEdit->text();
        QString origTargetText=this->text();
        //qDebug()<<"From "<<origSourceText<<" To "<<origTargetText;
        sourceLineEdit->setText(origTargetText);
        this->setText(origSourceText);
        event->setDropAction(Qt::MoveAction);
        event->accept();

    }
}


void createcharacterCaracLineEdit::startDrag(){
    //qDebug()<<"Starting a drag";
    if(this->text().length()){
        QMimeData *mimeData = new QMimeData;
        mimeData->setText(this->text());

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);

        if(drag->start(Qt::MoveAction)==Qt::MoveAction){
            //qDebug()<<"Drag Accepted";
        } //else {qDebug()<<"Drag refused";}


    } //else {qDebug()<<"No text to drag !";}


}
