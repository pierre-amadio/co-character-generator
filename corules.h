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
#ifndef CORULES_H
#define CORULES_H
#include <QString>


#define ID_HALFELF 1
#define ID_ELF 2
#define ID_HUMAN 3
#define ID_DWARF 4
#define ID_ORC 5
#define ID_HALFORC 6
#define ID_HALFELIN 7
#define ID_HIGHELF 8



#define ID_WARRIOR 1
#define ID_WIZARD 2
#define ID_PRIEST 3
#define ID_RANGER 4
#define ID_THIEF 5
#define ID_BARD 6
#define ID_MONK 7

class coRules
{


public:
    explicit coRules();
    ~coRules();
    int getCaracModifier(int caracValue);
    int getClassLifeDice(int classeId);
    QString getRaceName(int raceId);
    QString getClassName(int classId);

};

#endif // CORULES_H
