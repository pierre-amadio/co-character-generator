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
#include "createcharacterform.h"
#include "ui_createcharacterform.h"
#include "cocharacter.h"
#include "corules.h"
#include <QDebug>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QRegExp>
#include <QRegExpValidator>
#include <QString>

CreateCharacterForm::CreateCharacterForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateCharacterForm)
{
    ui->setupUi(this);
    //qDebug()<<"New character without pre defined roll set";

    QRegExp regExp("[0-9]{0,2}");
    ui->forEdit->setValidator(new QRegExpValidator(regExp,this));
    ui->dexEdit->setValidator(new QRegExpValidator(regExp,this));
    ui->conEdit->setValidator(new QRegExpValidator(regExp,this));
    ui->intEdit->setValidator(new QRegExpValidator(regExp,this));
    ui->sagEdit->setValidator(new QRegExpValidator(regExp,this));
    ui->chaEdit->setValidator(new QRegExpValidator(regExp,this));


    this->init_stuff();
}


CreateCharacterForm::CreateCharacterForm(QVector<int> caracSet,QWidget *parent):
        QDialog(parent),
        ui(new Ui::CreateCharacterForm)
{
    ui->setupUi(this);
    //qDebug()<<"New character with a predefined roll set";
    ui->forEdit->setReadOnly(true);
    ui->dexEdit->setReadOnly(true);
    ui->conEdit->setReadOnly(true);
    ui->intEdit->setReadOnly(true);
    ui->sagEdit->setReadOnly(true);
    ui->chaEdit->setReadOnly(true);

    ui->forEdit->setText(QString::number(caracSet[0]));
    forLineEditChanged(QString::number(caracSet[0]));

    ui->dexEdit->setText(QString::number(caracSet[1]));
    dexLineEditChanged(QString::number(caracSet[1]));

    ui->conEdit->setText(QString::number(caracSet[2]));
    conLineEditChanged(QString::number(caracSet[2]));

    ui->intEdit->setText(QString::number(caracSet[3]));
    intLineEditChanged(QString::number(caracSet[3]));

    ui->sagEdit->setText(QString::number(caracSet[4]));
    sagLineEditChanged(QString::number(caracSet[4]));

    ui->chaEdit->setText(QString::number(caracSet[5]));
    chaLineEditChanged(QString::number(caracSet[5]));



    this->init_stuff();
}



CreateCharacterForm::~CreateCharacterForm()
{
    delete ui;
}

void CreateCharacterForm::init_stuff(){
    //qDebug()<<"Init stuff()";
    coRules rules= coRules();
    this->setWindowTitle(tr("Character Creation Form."));
    ui->forModEdit->setReadOnly(true);
    ui->dexModEdit->setReadOnly(true);
    ui->conModEdit->setReadOnly(true);
    ui->intModEdit->setReadOnly(true);
    ui->sagModEdit->setReadOnly(true);
    ui->chaModEdit->setReadOnly(true);

    ui->forRaceEdit->setReadOnly(true);
    ui->dexRaceEdit->setReadOnly(true);
    ui->conRaceEdit->setReadOnly(true);
    ui->intRaceEdit->setReadOnly(true);
    ui->sagRaceEdit->setReadOnly(true);
    ui->chaRaceEdit->setReadOnly(true);


    ui->dvEdit->setReadOnly(true);
    ui->healthPointEdit->setReadOnly(true);
    ui->defEdit->setReadOnly(true);

    ui->attackContactEdit->setReadOnly(true);
    ui->attackDistanceEdit->setReadOnly(true);
    ui->attackMagicalEdit->setReadOnly(true);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);


    ui->classComboBox->addItem(rules.getClassName(ID_WARRIOR),ID_WARRIOR);
    ui->classComboBox->addItem(rules.getClassName(ID_WIZARD),ID_WIZARD);
    ui->classComboBox->addItem(rules.getClassName(ID_PRIEST),ID_PRIEST);
    ui->classComboBox->addItem(rules.getClassName(ID_RANGER),ID_RANGER);
    ui->classComboBox->addItem(rules.getClassName(ID_THIEF),ID_THIEF);

    ui->raceComboBox->addItem(rules.getRaceName(ID_HALFELF),ID_HALFELF);
    ui->raceComboBox->addItem(rules.getRaceName(ID_ELF),ID_ELF);
    ui->raceComboBox->addItem(rules.getRaceName(ID_HUMAN),ID_HUMAN);
    ui->raceComboBox->addItem(rules.getRaceName(ID_DWARF),ID_DWARF);
    ui->raceComboBox->addItem(rules.getRaceName(ID_ORC),ID_ORC);



    connect(ui->forEdit,SIGNAL(textChanged(QString)),this,SLOT(forLineEditChanged(QString)));
    connect(ui->dexEdit,SIGNAL(textChanged(QString)),this,SLOT(dexLineEditChanged(QString)));
    connect(ui->conEdit,SIGNAL(textChanged(QString)),this,SLOT(conLineEditChanged(QString)));
    connect(ui->intEdit,SIGNAL(textChanged(QString)),this,SLOT(intLineEditChanged(QString)));
    connect(ui->sagEdit,SIGNAL(textChanged(QString)),this,SLOT(sagLineEditChanged(QString)));
    connect(ui->chaEdit,SIGNAL(textChanged(QString)),this,SLOT(chaLineEditChanged(QString)));

    connect(ui->forModEdit,SIGNAL(textChanged(QString)),this,SLOT(forModChanged(QString)));
    connect(ui->dexModEdit,SIGNAL(textChanged(QString)),this,SLOT(dexModChanged(QString)));
    connect(ui->conModEdit,SIGNAL(textChanged(QString)),this,SLOT(conModChanged(QString)));
    connect(ui->intModEdit,SIGNAL(textChanged(QString)),this,SLOT(intModChanged(QString)));
    connect(ui->sagModEdit,SIGNAL(textChanged(QString)),this,SLOT(sagModChanged(QString)));
    connect(ui->chaModEdit,SIGNAL(textChanged(QString)),this,SLOT(chaModChanged(QString)));


    connect(ui->forRaceEdit,SIGNAL(textChanged(QString)),this,SLOT(forRaceChanged(QString)));
    connect(ui->dexRaceEdit,SIGNAL(textChanged(QString)),this,SLOT(dexRaceChanged(QString)));
    connect(ui->conRaceEdit,SIGNAL(textChanged(QString)),this,SLOT(conRaceChanged(QString)));
    connect(ui->intRaceEdit,SIGNAL(textChanged(QString)),this,SLOT(intRaceChanged(QString)));
    connect(ui->sagRaceEdit,SIGNAL(textChanged(QString)),this,SLOT(sagRaceChanged(QString)));
    connect(ui->chaRaceEdit,SIGNAL(textChanged(QString)),this,SLOT(chaRaceChanged(QString)));



    connect(ui->classComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(classComboBoxChanged(int)));
    connect(ui->raceComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(raceComboBoxChanged(int)));

    connect(ui->nameEdit,SIGNAL(textChanged(QString)),this,SLOT(check_validity(QString)));
    connect(ui->forEdit,SIGNAL(textChanged(QString)),this,SLOT(check_validity(QString)));
    connect(ui->dexEdit,SIGNAL(textChanged(QString)),this,SLOT(check_validity(QString)));
    connect(ui->conEdit,SIGNAL(textChanged(QString)),this,SLOT(check_validity(QString)));
    connect(ui->intEdit,SIGNAL(textChanged(QString)),this,SLOT(check_validity(QString)));
    connect(ui->sagEdit,SIGNAL(textChanged(QString)),this,SLOT(check_validity(QString)));
    connect(ui->chaEdit,SIGNAL(textChanged(QString)),this,SLOT(check_validity(QString)));


    ui->classComboBox->setCurrentIndex(1);
    ui->raceComboBox->setCurrentIndex(1);
    updateDef();
    updateAttackContact();
    updateAttackDistance();
    updateAttackMagical();


}


void CreateCharacterForm::forLineEditChanged(QString str) {
    Q_UNUSED ( str );
    setForModifier();
}

void CreateCharacterForm::dexLineEditChanged(QString str) {
    Q_UNUSED ( str );

    setDexModifier();
}

void CreateCharacterForm::conLineEditChanged(QString str) {
    Q_UNUSED ( str );
    setConModifier();
}

void CreateCharacterForm::intLineEditChanged(QString str) {
    Q_UNUSED ( str );
    setIntModifier();
}

void CreateCharacterForm::sagLineEditChanged(QString str) {
    Q_UNUSED ( str );
    setSagModifier();
}

void CreateCharacterForm::chaLineEditChanged(QString str) {
    Q_UNUSED ( str );
    setChaModifier();
}


void CreateCharacterForm::forModChanged(QString str){
    Q_UNUSED ( str );
    updateAttackContact();
}

void CreateCharacterForm::dexModChanged(QString str){
    Q_UNUSED ( str );
    updateDef();
    updateAttackDistance();
}
void CreateCharacterForm::conModChanged(QString str){
    Q_UNUSED ( str );
    updateHP();
}
void CreateCharacterForm::intModChanged(QString str){
    Q_UNUSED ( str );
    updateAttackMagical();
}
void CreateCharacterForm::sagModChanged(QString str){
    Q_UNUSED ( str );
    updateAttackMagical();
}
void CreateCharacterForm::chaModChanged(QString str){
    Q_UNUSED ( str );
}


void CreateCharacterForm::forRaceChanged(QString str){
    Q_UNUSED ( str );
    setForModifier();
}

void CreateCharacterForm::dexRaceChanged(QString str){
    Q_UNUSED ( str );
    setDexModifier();
}
void CreateCharacterForm::conRaceChanged(QString str){
    Q_UNUSED ( str );
    setConModifier();
}
void CreateCharacterForm::intRaceChanged(QString str){
    Q_UNUSED ( str );
    setIntModifier();
}
void CreateCharacterForm::sagRaceChanged(QString str){
    Q_UNUSED ( str );
    setSagModifier();
}
void CreateCharacterForm::chaRaceChanged(QString str){
    Q_UNUSED ( str );
    setChaModifier();
}



void CreateCharacterForm::classComboBoxChanged(int idx){
    int id_class=ui->classComboBox->itemData(idx).toInt();
    //qDebug()<<"New class:"<<rules.getClassName(id_class);
    int dv=rules.getClassLifeDice(id_class);
    ui->dvEdit->setText(QString::number(dv));
    updateHP();
    updateAttackMagical();

}
void CreateCharacterForm::raceComboBoxChanged(int idx){
    int id_race=ui->raceComboBox->itemData(idx).toInt();
    //qDebug()<<"New race:"<<rules.getRaceName(id_race);

    ui->forRaceEdit->setText("0");
    ui->dexRaceEdit->setText("0");
    ui->conRaceEdit->setText("0");
    ui->intRaceEdit->setText("0");
    ui->sagRaceEdit->setText("0");
    ui->chaRaceEdit->setText("0");


    if(id_race==ID_ELF){
        ui->conRaceEdit->setText("-2");
        ui->dexRaceEdit->setText("2");
    }


    if(id_race==ID_DWARF){
        ui->dexRaceEdit->setText("-2");
        ui->conRaceEdit->setText("2");
    }

    if(id_race==ID_ORC){
        ui->forRaceEdit->setText("2");
        ui->intRaceEdit->setText("-2");
        ui->dexRaceEdit->setText("-2");

    }

}


void CreateCharacterForm::setForModifier(){
    int origCarac=ui->forEdit->text().toInt();
    int raceCarac=origCarac+ui->forRaceEdit->text().toInt();
    int newMod=rules.getCaracModifier(raceCarac);
    ui->forModEdit->setText(QString::number(newMod));
}

void CreateCharacterForm::setDexModifier(){
    int origCarac=ui->dexEdit->text().toInt();
    int raceCarac=origCarac+ui->dexRaceEdit->text().toInt();
    int newMod=rules.getCaracModifier(raceCarac);
    ui->dexModEdit->setText(QString::number(newMod));
}

void CreateCharacterForm::setConModifier(){
    int origCarac=ui->conEdit->text().toInt();
    int raceCarac=origCarac+ui->conRaceEdit->text().toInt();
    int newMod=rules.getCaracModifier(raceCarac);
    ui->conModEdit->setText(QString::number(newMod));

}

void CreateCharacterForm::setIntModifier(){
    int origCarac=ui->intEdit->text().toInt();
    int raceCarac=origCarac+ui->intRaceEdit->text().toInt();
    int newMod=rules.getCaracModifier(raceCarac);
    ui->intModEdit->setText(QString::number(newMod));

}

void CreateCharacterForm::setSagModifier(){
    int origCarac=ui->sagEdit->text().toInt();
    int raceCarac=origCarac+ui->sagRaceEdit->text().toInt();
    int newMod=rules.getCaracModifier(raceCarac);
    ui->sagModEdit->setText(QString::number(newMod));

}

void CreateCharacterForm::setChaModifier(){
    int origCarac=ui->chaEdit->text().toInt();
    int raceCarac=origCarac+ui->chaRaceEdit->text().toInt();
    int newMod=rules.getCaracModifier(raceCarac);
    ui->chaModEdit->setText(QString::number(newMod));

}






void CreateCharacterForm::updateHP(){
    //qDebug()<<"Need to update HP";
    int hp=ui->dvEdit->text().toInt()+ui->conModEdit->text().toInt();
    ui->healthPointEdit->setText(QString::number(hp));
}

void CreateCharacterForm::updateDef(){
    //qDebug()<<"Need to update Def";
    int def=10+ui->dexModEdit->text().toInt();
    ui->defEdit->setText(QString::number(def));
}


void CreateCharacterForm::updateAttackContact(){
    //qDebug()<<"Need to update contact attack";
    int at=ui->forModEdit->text().toInt()+1;
    ui->attackContactEdit->setText(QString::number(at));
}
void CreateCharacterForm::updateAttackDistance(){
    //qDebug()<<"Need to update distance attack";
    int at=ui->dexModEdit->text().toInt()+1;
    ui->attackDistanceEdit->setText(QString::number(at));
}

void CreateCharacterForm::updateAttackMagical(){
    //qDebug()<<"Need to update magical";
    int id_class=ui->classComboBox->itemData(ui->classComboBox->currentIndex()).toInt();
    if(id_class==ID_WIZARD){
        int val=ui->intModEdit->text().toInt()+1;
        ui->attackMagicalEdit->setText(QString::number(val));
    } else if(id_class==ID_PRIEST){
        int val=ui->sagModEdit->text().toInt()+1;
        ui->attackMagicalEdit->setText(QString::number(val));
    } else {
        ui->attackMagicalEdit->setText("");
    }

}


void CreateCharacterForm::check_validity(QString str){
    Q_UNUSED ( str );
    bool pbFlag=false;
    if(ui->forEdit->text().length()==0){
        pbFlag=true;
    }
    if(ui->dexEdit->text().length()==0){
        pbFlag=true;
    }
    if(ui->conEdit->text().length()==0){
        pbFlag=true;
    }
    if(ui->intEdit->text().length()==0){
        pbFlag=true;
    }
    if(ui->sagEdit->text().length()==0){
        pbFlag=true;
    }
    if(ui->chaEdit->text().length()==0){
        pbFlag=true;
    }
    if(ui->nameEdit->text().length()==0){
        pbFlag=true;
    }

    if(! pbFlag){
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    } else {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}


void CreateCharacterForm::fillCoCharacter(coCharacter *c){
    c->name=ui->nameEdit->text();

    c->strenght=ui->forEdit->text().toInt()+ui->forRaceEdit->text().toInt();
    c->dex=ui->dexEdit->text().toInt()+ui->dexRaceEdit->text().toInt();
    c->con=ui->conEdit->text().toInt()+ui->conRaceEdit->text().toInt();
    c->intelligence=ui->intEdit->text().toInt()+ui->intRaceEdit->text().toInt();
    c->sag=ui->sagEdit->text().toInt()+ui->sagRaceEdit->text().toInt();
    c->cha=ui->chaEdit->text().toInt()+ui->chaRaceEdit->text().toInt();

    c->modStrenght=ui->forModEdit->text().toInt();
    c->modDex=ui->dexModEdit->text().toInt();
    c->modCon=ui->conModEdit->text().toInt();
    c->modIntelligence=ui->intModEdit->text().toInt();
    c->modSag=ui->sagModEdit->text().toInt();
    c->modCha=ui->chaModEdit->text().toInt();

    c->attackContact=ui->attackContactEdit->text().toInt();
    c->attackDistance=ui->attackDistanceEdit->text().toInt();
    c->attackMagical=ui->attackMagicalEdit->text().toInt();

    c->def=ui->defEdit->text().toInt();
    c->pv=ui->healthPointEdit->text().toInt();
    c->dv=ui->dvEdit->text().toInt();


    c->race=ui->raceComboBox->itemData(ui->raceComboBox->currentIndex()).toInt();
    c->charClass=ui->classComboBox->itemData(ui->classComboBox->currentIndex()).toInt();

    c->level=1;

}
