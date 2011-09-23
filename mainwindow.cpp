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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasestuff.h"
#include "corules.h"
#include "randomcaracform.h"
#include "createcharacterform.h"
#include "charactersheetviewerform.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionNew_Character,SIGNAL(triggered()),this,SLOT(newCharacter()));
    connect(ui->actionNew_Character_free_input,SIGNAL(triggered()),this,SLOT(newCharacterFreeInput()));
    connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(quit()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(about()));

    connect(ui->deleteCharButton,SIGNAL(clicked()),this,SLOT(deleteCharacter()));
    connect(ui->viewSheetButton,SIGNAL(clicked()),this,SLOT(displayCharacterSheet()));


    databaseStuff db;
    dbModel=new QStandardItemModel(this);
    ui->dbCharListViewer->setModel(dbModel);
    connect(ui->dbCharListViewer->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(dbViewSelectionChanged(QItemSelection,QItemSelection)));

    ui->deleteCharButton->setEnabled(false);
    ui->viewSheetButton->setEnabled(false);

    ui->dbCharListViewer->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->dbCharListViewer->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->dbCharListViewer->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setWindowTitle(tr("Forgotten Chronicles"));

    refreshDbViewer();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete dbModel;
}

void MainWindow::quit(){
    this->close();
}

void MainWindow::about(){
    QMessageBox::about(this,tr("About CO"),
                       tr("<h2>Forgotten Chronicles Character Sheet Generator</h2>"
                          "<p>Copyright &copy; 2011 Pierre Amadio &lt;pierre.amadio@libertysurf.fr&gt;"
                          "<p>This application is released under the GPL Licence. This mean you have the right to "
                          "run it, access its source code, modify it, and redistribute it (as long as you "
                          "give the same right to whoever you redistribute the original, or a modified version)."
                          "<p>More details are available on http://www.gnu.org/licenses/"
                          "<p>The source code is available on https://gitorious.org/co-character-generator "
                          )
                       );
}

void MainWindow::newCharacter(){
    //qDebug()<<"New Character";
    randomCaracForm * form = new randomCaracForm;
    QVector<int> caracSet;

    if(form->exec()==QDialog::Accepted){
        //qDebug()<<"Accepted";
        caracSet=form->getSelectedCarac();

    } else {
        //qDebug()<<"Rejected";
        delete form;
        return;
    }
    delete form;

    CreateCharacterForm * cform=new CreateCharacterForm(caracSet,this);
    coCharacter *character=new coCharacter();
    if(cform->exec()==QDialog::Accepted){
        //qDebug()<<"Accepted";
        cform->fillCoCharacter(character);
    } else {
        //qDebug()<<"Not accepted";
        delete cform;
        delete character;
        return;
    }

    if(!insertNewCharacterInDb(character)){
        qDebug()<<"Problem inserting character in database";
    } else {
        refreshDbViewer();
    }
    delete cform;
    delete character;
}

void MainWindow::newCharacterFreeInput(){
    qDebug()<<"New Character Free Input";

    CreateCharacterForm * cform=new CreateCharacterForm(this);
    coCharacter *character=new coCharacter();
    if(cform->exec()==QDialog::Accepted){
        qDebug()<<"Accepted";
        cform->fillCoCharacter(character);
    } else {
        qDebug()<<"Not accepted";
        delete cform;
        delete character;
        return;
    }


    if(!insertNewCharacterInDb(character)){
        qDebug()<<"Problem inserting character in database";
    }else {
        refreshDbViewer();
    }

    delete cform;
    delete character;

}

void MainWindow::dbViewSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected){
    Q_UNUSED ( selected );
    Q_UNUSED ( deselected );
    ui->deleteCharButton->setEnabled(true);
    ui->viewSheetButton->setEnabled(true);
}

void MainWindow::deleteCharacter(){
QModelIndex item=ui->dbCharListViewer->currentIndex();
//qDebug()<<item.row();

QModelIndex nameIdx;
QModelIndex idIdx;
nameIdx=dbModel->index(item.row(),1);
idIdx=dbModel->index(item.row(),0);

QString charName=dbModel->data(nameIdx).toString();
int charId=dbModel->data(idIdx).toInt();
//qDebug()<<"name"<<charName<<" id="<<charId;

QString question=tr("Are you sure you want to delete %1 ?").arg(charName);

QMessageBox msgBox;
msgBox.setInformativeText(question);
msgBox.setText(tr("Deleting a user"));
msgBox.setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
if(msgBox.exec()==QMessageBox::Cancel){
    return;
 }
//qDebug()<<"Let s do it";

QSqlQuery query;
query.prepare("delete from characters where id=:charid");
query.bindValue(":charid",charId);
if(!query.exec()){
    qDebug()<<"Problem insterting data";
    QSqlError sqlError=query.lastError();
    qDebug()<<sqlError.databaseText();
    qDebug()<<sqlError.driverText();
    }

refreshDbViewer();
}

void MainWindow::displayCharacterSheet(){
    qDebug()<<"Displaying character sheet";
    QModelIndex item=ui->dbCharListViewer->currentIndex();
    QModelIndex idIdx;
    idIdx=dbModel->index(item.row(),0);
    int charId=dbModel->data(idIdx).toInt();
    qDebug()<<charId;

    characterSheetViewerForm shV(charId,this);
    shV.exec();


}

bool MainWindow::insertNewCharacterInDb(coCharacter *character){
    QSqlQuery query;
    query.prepare("insert into characters ("
                  "name,strenght,dex,constitution,intelligence,sag,"
                  "cha,at_contact,at_distance,"
                  "at_magic,health_point,defence,"
                  "life_dice,character_class,race,level) "
                  "values (:name,:strenght,:dex,:con,:intelligence,:sag,"
                  ":cha,:contact,:distance,"
                  ":magic,:pv,:def,"
                  ":dv,:cl,:race,:level)"
                  );

    query.bindValue(":name",character->name);
    query.bindValue(":strenght",character->strenght);
    query.bindValue(":dex",character->dex);
    query.bindValue(":con",character->con);
    query.bindValue(":intelligence",character->intelligence);
    query.bindValue(":sag",character->sag);
    query.bindValue(":cha",character->cha);
    query.bindValue(":contact",character->attackContact);
    query.bindValue(":distance",character->attackDistance);
    query.bindValue(":magic",character->attackMagical);
    query.bindValue(":pv",character->pv);
    query.bindValue(":def",character->def);
    query.bindValue(":dv",character->dv);
    query.bindValue(":cl",character->charClass);
    query.bindValue(":race",character->race);
    query.bindValue(":level",character->level);


    if(query.exec()) {
         //qDebug()<<"Insetions seems to have work";
     } else {
         qDebug()<<"Problem insterting data";
         QSqlError sqlError=query.lastError();
         qDebug()<<sqlError.databaseText();
         qDebug()<<sqlError.driverText();

         qDebug()<<"executed ="<<query.executedQuery();
         qDebug()<<"bounded values"<<query.boundValues();
         return false;
     }
    return true;
}

void MainWindow::refreshDbViewer(){
    coRules corules;
    dbModel->clear();

    QSqlQuery query;
    if(!query.exec("select id,name,character_class,race from characters")){
       QSqlError error;
       error=query.lastError();
       qDebug()<<"Problem with database:"<<error.databaseText();
    }
    while(query.next()){
            int id=query.value(0).toInt();
            QString name=query.value(1).toString();
            int id_class=query.value(2).toInt();
            int id_race=query.value(3).toInt();
            QString className=corules.getClassName(id_class);
            QString raceName=corules.getRaceName(id_race);
            //qDebug()<<id<<" "<<name<<" "<<className<<" "<<raceName;

            QList<QStandardItem*> newRow;
            newRow.append(new QStandardItem(QString::number(id)));
            newRow.append(new QStandardItem(name));
            newRow.append(new QStandardItem(className));
            newRow.append(new QStandardItem(raceName));

            dbModel->appendRow(newRow);



    }
    ui->dbCharListViewer->setColumnHidden(0,true);

    dbModel->setHeaderData( 1, Qt::Horizontal,tr("Name") );
    dbModel->setHeaderData( 2, Qt::Horizontal,tr("Class") );
    dbModel->setHeaderData( 3, Qt::Horizontal,tr("Race") );
    //ui->dbCharListViewer->update();

}
