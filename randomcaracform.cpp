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
#include "randomcaracform.h"
#include "ui_randomcaracform.h"
#include <QDebug>
#include <QVector>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QtCore>
#include <QAbstractItemView>
#include "rawcaractableviewdelegate.h"

randomCaracForm::randomCaracForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::randomCaracForm)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(ui->rollDicesButton,SIGNAL(clicked()),this,SLOT(rollDice()));
    connect(this,SIGNAL(displayResultSet(QVector<int>)),this->ui->carDiceView,SLOT(showResult(QVector<int>)));




    qsrand(QTime::currentTime().msec());

    nbrOfRoll=0;
    lastRollSet.resize(RCF_DICE_PER_ROLL);
    selectedRollSet.resize(RCF_NBR_CARAC);

    rollSetModel=new QStandardItemModel;


    for(int line=0;line<RCF_MAX_ROLL;line++)  {
        for(int col=0;col<RCF_NBR_CARAC;col++){
             QStandardItem *item = new QStandardItem(" ");
             rollSetModel->setItem(line,col,item);
        }
    }

    ui->rawCaracTableView->setItemDelegate(new rawCaracTableViewDelegate());
    ui->rawCaracTableView->setModel(rollSetModel);
    ui->rawCaracTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->rawCaracTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->rawCaracTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->rawCaracTableView->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(caracSetSelectionChanged(QItemSelection,QItemSelection)));


    for(int i=0;i<RCF_DICE_PER_ROLL;i++){
        this->lastRollSet[i]=i+1;
    }
    emit(displayResultSet(lastRollSet));


}

randomCaracForm::~randomCaracForm()
{
    delete ui;
    delete rollSetModel;

}

void randomCaracForm::rollDice(){


    if(nbrOfRoll>=RCF_MAX_ROLL*RCF_NBR_CARAC) {
        return;
    }

    int low=1;
    int high=6;
    for(int i=0;i<RCF_DICE_PER_ROLL;i++){
        lastRollSet[i]=qrand() % ((high + 1) - low) + low;
    }
    qSort(lastRollSet);
    emit(displayResultSet(lastRollSet));


    int sum=lastRollSet[RCF_DICE_PER_ROLL-1]+lastRollSet[RCF_DICE_PER_ROLL-2]+lastRollSet[RCF_DICE_PER_ROLL-3];
    //qDebug()<<"sum="<<sum;

    nbrOfRoll++;
    /*
      c is the column index of the next element to store.
      l is the line index of the next element to store.

      There are RCF_MAX_ROLL*RCF_NBR_CARAC rollset to perform.
      We just did the nbrOfRollth roll.

    */
    int c,l;
    int modulo_col=nbrOfRoll%RCF_NBR_CARAC;
    if(modulo_col==0) {c=RCF_NBR_CARAC-1;} else {c=modulo_col-1;}
    l=qFloor((nbrOfRoll-1)/RCF_NBR_CARAC);


    QModelIndex modelIndex;
    modelIndex=rollSetModel->index(l,c);
    rollSetModel->setData(modelIndex,sum,Qt::DisplayRole);

    if(nbrOfRoll==RCF_MAX_ROLL*RCF_NBR_CARAC){
        //qDebug()<<"No we can select stuff";
        ui->rawCaracTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->rollDicesButton->setEnabled(false);
    }
};


void randomCaracForm::caracSetSelectionChanged(const QItemSelection &selected,const QItemSelection &deselected){
    //qDebug()<<"Selection changed";
    QModelIndexList items = selected.indexes();
    //QModelIndex index;
    QListIterator<QModelIndex> iter(items);

    int cnt=0;
    while(iter.hasNext()){
        QModelIndex curInd;
        curInd=iter.next();
        selectedRollSet[cnt++]=curInd.data().toInt();
        //qDebug()<<curInd<<curInd.data().toInt();
    }
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

QVector<int> randomCaracForm::getSelectedCarac(){
    return selectedRollSet;
}
