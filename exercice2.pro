QT += widgets
QT += xml

QT += script
CONFIG += c++11
QT       += sql # On rajoute SQL
CONFIG   += console # On rajoute la console
TEMPLATE = app # On veut une application, oui

SOURCES += \
    templatemanager.cpp \
    database.cpp \
    EntityStd.cpp \
    uv.cpp \
    Formation.cpp \
    Etudiant.cpp \
    Dossier.cpp \
    mainfenetre.cpp \
    modifieretudiant.cpp \
    modifieruv_fen.cpp \
    Categorie.cpp \
    Note.cpp \
    Saison.cpp \
    Condition.cpp \
    ConditionChecker.cpp \
    main2.cpp \
    creerdossier.cpp \
    Semestre.cpp \
    gererformation.cpp \
    QTgraphTools.cpp \
    modifiernote.cpp \
    modifiersaison.cpp \
    modifiersemestre.cpp \
    modifiercategorie.cpp \
    gerercategorie.cpp \
    gererprevision.cpp

HEADERS += \
    templatemanager.h \
    database.h \
    EntityStd.h \
    uv.h \
    Formation.h \
    Semestre.h \
    Etudiant.h \
    Inscription.h \
    Dossier.h \
    mainfenetre.h \
    modifieretudiant.h \
    modifieruv_fen.h \
    Categorie.h \
    Note.h \
    Saison.h \
    Condition.h \
    ConditionChecker.h \
    creerdossier.h \
    gererformation.h \
    QTgraphTools.h \
    modifiernote.h \
    modifiersaison.h \
    modifiersemestre.h \
    modifiercategorie.h \
    gerercategorie.h \
    gererprevision.h
    main.cpp.vieux


FORMS += \
    mainfenetre.ui \
    modifieretudiant.ui \
    modifieruv_fen.ui \
    editerdossier.ui \
    creerdossier.ui \
    gererformation.ui \
    modifiernote.ui \
    modifiersaison.ui \
    modifiersemestre.ui \
    modifiercategorie.ui \
    gerercategorie.ui \
    gererprevision.ui
