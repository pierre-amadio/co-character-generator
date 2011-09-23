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
#include "cocharacter.h"
#include <corules.h>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

coCharacter::coCharacter()
{
}

coCharacter::coCharacter(int charId){
    qDebug()<<"Creating character for id="<<charId;
    QSqlQuery query;

    query.prepare("select id,name,strenght,dex,constitution,intelligence,sag,"
                  "cha,at_contact,at_distance,at_magic,"
                  "health_point,defence,life_dice,character_class,"
                  "race,level from characters where id=:idc"
                  );



    query.bindValue(":idc",charId);
    if(!query.exec()) {
        QSqlError error;
        error=query.lastError();
        qDebug()<<"Problem with database:"<<error.databaseText();
        qDebug()<<error.driverText();
    }



    if(! query.next()){
    qDebug()<<"No character with this id in database:"<<charId;
    return;
    }

    name=query.value(1).toString();
    strenght=query.value(2).toInt();
    dex=query.value(3).toInt();
    con=query.value(4).toInt();
    intelligence=query.value(5).toInt();
    sag=query.value(6).toInt();
    cha=query.value(7).toInt();
    attackContact=query.value(8).toInt();
    attackDistance=query.value(9).toInt();
    attackMagical=query.value(10).toInt();
    pv=query.value(11).toInt();
    def=query.value(12).toInt();
    dv=query.value(13).toInt();
    charClass=query.value(14).toInt();
    race=query.value(15).toInt();
    level=query.value(16).toInt();


    coRules rules=coRules();
    modStrenght=rules.getCaracModifier(strenght);
    modDex=rules.getCaracModifier(dex);
    modCon=rules.getCaracModifier(con);
    modIntelligence=rules.getCaracModifier(intelligence);
    modSag=rules.getCaracModifier(sag);
    modCha=rules.getCaracModifier(cha);


}
