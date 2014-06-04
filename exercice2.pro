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
    Dossier.cpp \
    mainfenetre.cpp \
    ajouteruv_fen.cpp \
    ajouteretudiant_fen.cpp \
    ajouterformation_fen.cpp \
    ajouteruvformation_fen.cpp \
    modifieretudiant.cpp \
    modifieruv_fen.cpp \
    modifierform.cpp

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
    Dossier.h \
    mainfenetre.h \
    ajouteruv_fen.h \
    ajouteretudiant_fen.h \
    ajouterformation_fen.h \
    ajouteruvformation_fen.h \
    modifieretudiant.h \
    modifieruv_fen.h \
    modifierform.h

FORMS += \
    mainfenetre.ui \
    ajouteruv_fen.ui \
    ajouteretudiant_fen.ui \
    ajouterformation_fen.ui \
    ajouteruvformation_fen.ui \
    modifieretudiant.ui \
    modifieruv_fen.ui \
    modifierform.ui \
    modifierform.ui
