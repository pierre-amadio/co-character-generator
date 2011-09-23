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
#include "corules.h"
#include <QDebug>
#include <QString>
#include <QObject>

coRules::coRules()
{
}

coRules::~coRules(){

}

int coRules::getCaracModifier(int v) {
    if(v<=3)  {return -4;}
    if(v<=5)  {return -3;}
    if(v<=7)  {return -2;}
    if(v<=9)  {return -1;}
    if(v<=11) {return 0;}
    if(v<=13) {return 1;}
    if(v<=15) {return 2;}
    if(v<=17) {return 3;}
    if(v<=19) {return 4;}
    if(v<=21) {return 5;}
    qDebug()<<"No match found for caracModifier("<<v<<")";
    //just in case...
    return 5;
}

int coRules::getClassLifeDice(int classeId) {
    if(classeId==ID_WARRIOR) {return 10;}
    if(classeId==ID_WIZARD) {return 4;}
    if(classeId==ID_PRIEST) {return 8;}
    if(classeId==ID_RANGER) {return 8;}
    if(classeId==ID_THIEF) {return 6;}
    qDebug()<<"Unknown class Id in getClassLifeDice:"<<classeId;
    return 0;
}


QString coRules::getRaceName(int raceId){
    //see QT_TRANSLATE_NOOP

    if(raceId==ID_DWARF) {return QObject::tr("Dwarf");}
    if(raceId==ID_ELF) {return QObject::tr("Elf");}
    if(raceId==ID_HALFELF) {return QObject::tr("Half Elf");}
    if(raceId==ID_HUMAN) {return QObject::tr("Human");}
    if(raceId==ID_ORC) {return QObject::tr("Orc");}

    qDebug()<<"Unkown raceId in getRaceName: "<<raceId;
    return QObject::tr("Alien");

}

QString coRules::getClassName(int classId){
    if(classId==ID_WARRIOR) {return QObject::tr("Warrior");}
    if(classId==ID_WIZARD) {return QObject::tr("Wizard");}
    if(classId==ID_PRIEST) {return QObject::tr("Priest");}
    if(classId==ID_RANGER) {return QObject::tr("Ranger");}
    if(classId==ID_THIEF) {return QObject::tr("Thief");}
    qDebug()<<"Unknown classId in getClassName:"<<classId;
    return QObject::tr("None");

}

