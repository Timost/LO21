QT += widgets
QT += xml
CONFIG += c++11
QT       += sql # On rajoute SQL
QT       -= gui # On enlève la GUI
CONFIG   += console # On rajoute la console
TEMPLATE = app # On veut une application, oui

SOURCES += \
    main.cpp \
    UTProfiler.cpp \
    uvediteur.cpp \
    profiler.cpp \
    templatemanager.cpp \
    database.cpp

HEADERS += \
    UTProfiler.h \
    uvediteur.h \
    profiler.h \
    templatemanager.h \
    database.h
