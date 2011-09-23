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
#include "databasestuff.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>

databaseStuff::databaseStuff()
{
    QString dirName=QString("%1/.co").arg(QDir::homePath());
    QDir dir;
    if(! dir.mkpath(dirName)){
        qDebug()<<"Cannot create "<<dirName;
    }



    QString dbName=QString("%1/db.sqlite").arg(dirName);
    //qDebug()<<dbName;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if(!db.open()){
        qDebug()<<"Problem accessing the database:"<<db.lastError().text();
    }

    if(! this->databaseExist()) {
        QSqlError *error=new QSqlError();
        if(!this->createDatabase(error)){
                qDebug()<<QString("Problem creating the database:\n'%1' : '%2'").arg(error->driverText()).arg(error->databaseText());

        }
        delete error;
    }



}

bool databaseStuff::databaseExist(){
    QString snt="select * from sqlite_master where type='table' and name='characters'";
    QSqlQuery query;
    query.exec(snt);
    if(query.next()){return true;} else {return false;}
}

bool databaseStuff::createDatabase(QSqlError *error){
    //qDebug()<<"Let s create database";
    QString create_snt="create table characters ("
                       "id integer primary key asc,"
                       "name text,"
                       "strenght integer,"
                       "dex integer,"
                       "constitution integer,"
                       "intelligence integer,"
                       "sag integer,"
                       "cha integer,"
                       "at_contact integer,"
                       "at_distance integer,"
                       "at_magic integer,"
                       "health_point integer,"
                       "defence integer,"
                       "life_dice integer,"
                       "character_class integer,"
                       "race integer,"
                       "level integer"
                       ")";
     //qDebug()<<create_snt;

    QSqlQuery query;
    if(query.exec(create_snt)){
        return true;
    } else {
        *error=query.lastError();
        return false;
    }


}
