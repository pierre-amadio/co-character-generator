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
#include "charactersheetviewerform.h"
#include "ui_charactersheetviewerform.h"
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QRect>
#include <QSize>

characterSheetViewerForm::characterSheetViewerForm(int charId,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::characterSheetViewerForm)
{
    ui->setupUi(this);
    characterId=charId;
    ui->sheetViewerWidget->setCharacter(charId);
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(closeWindow()));
    connect(ui->printButton,SIGNAL(clicked()),this,SLOT(printIt()));
}

characterSheetViewerForm::~characterSheetViewerForm()
{
    delete ui;
}

void characterSheetViewerForm::closeWindow(){
    this->done(1);
}

void characterSheetViewerForm::printIt(){
    qDebug()<<"Let s print";

    QImage image=ui->sheetViewerWidget->getImage();

    QPrinter printer;
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec()){
        qDebug()<<"Let s print it ";
        QPainter painter(&printer);
        QRect rect= painter.viewport();
        QSize size=image.size();
        size.scale(rect.size(),Qt::KeepAspectRatio);
        painter.setViewport(rect.x(),rect.y(),size.width(),size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0,0,image);
    }

}

