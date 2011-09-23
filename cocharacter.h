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
#ifndef COCHARACTER_H
#define COCHARACTER_H
#include <QString>

class coCharacter
{
public:
    coCharacter();
    coCharacter(int charId);
    QString name;
    int strenght;
    int dex;
    int con;
    int intelligence;
    int sag;
    int cha;
    int modStrenght;
    int modDex;
    int modCon;
    int modIntelligence;
    int modSag;
    int modCha;
    int attackContact;
    int attackDistance;
    int attackMagical;
    int def;
    int pv;
    int dv;
    int race;
    int charClass;
    int level;
};

#endif // COCHARACTER_H
