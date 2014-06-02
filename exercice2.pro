QT += widgets
QT += xml
CONFIG += c++11
QT       += sql # On rajoute SQL
CONFIG   += console # On rajoute la console
TEMPLATE = app # On veut une application, oui

SOURCES += \
    main.cpp \
    templatemanager.cpp \
    database.cpp \
    EntityStd.cpp \
    uv.cpp \
    Formation.cpp \
    Exception.cpp \
    enums.cpp \
    Etudiant.cpp \
    Dossier.cpp

HEADERS += \
    templatemanager.h \
    database.h \
    EntityStd.h \
    uv.h \
    Formation.h \
    enums.h \
    Semestre.h \
    Exception.h \
    Etudiant.h \
    Inscription.h \
    Dossier.h
