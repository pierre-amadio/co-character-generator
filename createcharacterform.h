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
#ifndef CREATECHARACTERFORM_H
#define CREATECHARACTERFORM_H

#include <QDialog>
#include <QVector>
#include "createcharactercaraclineedit.h"
#include "corules.h"
#include "cocharacter.h"

namespace Ui {
    class CreateCharacterForm;
}

class CreateCharacterForm : public QDialog
{
    Q_OBJECT

public:
    explicit CreateCharacterForm(QWidget *parent = 0);
    CreateCharacterForm(QVector<int> caracSet,QWidget *parent = 0);
    void fillCoCharacter(coCharacter * character);
    ~CreateCharacterForm();

private:
    Ui::CreateCharacterForm *ui;
    void init_stuff();

    void updateAttackContact();
    void updateAttackDistance();
    void updateAttackMagical();

    void setForModifier();
    void setDexModifier();
    void setConModifier();
    void setIntModifier();
    void setSagModifier();
    void setChaModifier();

    coRules rules;

private slots:
    void forLineEditChanged(QString str);
    void dexLineEditChanged(QString str);
    void conLineEditChanged(QString str);
    void intLineEditChanged(QString str);
    void sagLineEditChanged(QString str);
    void chaLineEditChanged(QString str);

    void forModChanged(QString str);
    void dexModChanged(QString str);
    void conModChanged(QString str);
    void intModChanged(QString str);
    void sagModChanged(QString str);
    void chaModChanged(QString str);

    void forRaceChanged(QString str);
    void dexRaceChanged(QString str);
    void conRaceChanged(QString str);
    void intRaceChanged(QString str);
    void sagRaceChanged(QString str);
    void chaRaceChanged(QString str);


    void classComboBoxChanged(int idx);
    void raceComboBoxChanged(int idx);

    void updateHP();
    void updateDef();

    void check_validity(QString str);
};

#endif // CREATECHARACTERFORM_H
