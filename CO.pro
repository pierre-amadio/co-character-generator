######################################################################
# Automatically generated by qmake (2.01a) Fri Sep 23 11:54:15 2011
######################################################################

QT += sql
QT += widgets
QT += printsupport

TEMPLATE = app
TARGET = co-creator 
DEPENDPATH += .
INCLUDEPATH += .

VERSION = 1.1
RELEASE = 0

# Input
HEADERS += caracroll.h \
           charactersheetviewerform.h \
           cocharacter.h \
           corules.h \
           createcharactercaraclineedit.h \
           createcharacterform.h \
           databasestuff.h \
           diceview.h \
           mainwindow.h \
           randomcaracform.h \
           rawcaractableviewdelegate.h \
           sheetviewer.h \

FORMS += caracroll.ui \
         charactersheetviewerform.ui \
         createcharactercaraclineedit.ui \
         createcharacterform.ui \
         diceview.ui \
         mainwindow.ui \
         randomcaracform.ui
SOURCES += caracroll.cpp \
           charactersheetviewerform.cpp \
           cocharacter.cpp \
           corules.cpp \
           createcharactercaraclineedit.cpp \
           createcharacterform.cpp \
           databasestuff.cpp \
           diceview.cpp \
           main.cpp \
           mainwindow.cpp \
           randomcaracform.cpp \
           rawcaractableviewdelegate.cpp \
           sheetviewer.cpp
RESOURCES += coRessources.qrc

TRANSLATIONS = translations/co_fr.ts

unix:{

DOCFILES.files = COPYING LISEZMOI.txt
DOCFILES.path = /usr/share/doc/co-character-generator-$$VERSION

BINARY.files = $$TARGET
BINARY.path = /bin

INSTALLS += DOCFILES BINARY 
}
