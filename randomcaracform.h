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
#ifndef RANDOMCARACFORM_H
#define RANDOMCARACFORM_H

#include <QDialog>
#include <QVector>
#include <QStandardItemModel>
#include <QStringListModel>
#define RCF_DICE_PER_ROLL 4
#define RCF_NBR_CARAC 6
#define RCF_MAX_ROLL 3

namespace Ui {
    class randomCaracForm;
}

class randomCaracForm : public QDialog
{
    Q_OBJECT

public:
    explicit randomCaracForm(QWidget *parent = 0);
    QVector<int> getSelectedCarac();
    ~randomCaracForm();

private:
    Ui::randomCaracForm *ui;
    //Store the results for the dice that are displayed.
    QVector<int> lastRollSet;
    //The model for the roll set on the left.
    QStandardItemModel * rollSetModel;
    //Number of roll the used performed since the form started:
    int nbrOfRoll;
    //The actual carac roll set selected by the user is stored in this vector
    QVector<int> selectedRollSet;

private slots:
    void rollDice();
    void caracSetSelectionChanged(const QItemSelection &selected,const QItemSelection &deselected);

signals:
    void displayResultSet(QVector<int>);

};

#endif // RANDOMCARACFORM_H
