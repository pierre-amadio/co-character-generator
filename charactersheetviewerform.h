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
#ifndef CHARACTERSHEETVIEWERFORM_H
#define CHARACTERSHEETVIEWERFORM_H

#include <QDialog>

namespace Ui {
    class characterSheetViewerForm;
}

class characterSheetViewerForm : public QDialog
{
    Q_OBJECT

public:
    explicit characterSheetViewerForm(int charId,QWidget *parent = 0);
    ~characterSheetViewerForm();

private:
    Ui::characterSheetViewerForm *ui;
    int characterId;

private slots:
    void closeWindow();
    void printIt();
};

#endif // CHARACTERSHEETVIEWERFORM_H
