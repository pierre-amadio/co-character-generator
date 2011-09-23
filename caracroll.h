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
#ifndef CARACROLL_H
#define CARACROLL_H

#include <QWidget>

namespace Ui {
    class caracRoll;
}

class caracRoll : public QWidget
{
    Q_OBJECT

public:
    explicit caracRoll(QWidget *parent = 0);
    ~caracRoll();

private:
    Ui::caracRoll *ui;

signals:
    void showDice1(int res);
    void showDice2(int res);
    void showDice3(int res);
    void showDice4(int res);

private slots:
    void showResult(QVector<int>);

};

#endif // CARACROLL_H
