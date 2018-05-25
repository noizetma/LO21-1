QT += widgets

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11
SOURCES += \
    main.cpp \
    cell.cpp \
    generateuretat.cpp \
    etat.cpp \
    voisinage.cpp \
    transitionrule.cpp \
    cellularautomata.cpp \
    cabuilder.cpp \
    mainwindow.cpp \
    fenetre1d.cpp \
    fenetre2d.cpp \
    fenetreconfig.cpp

HEADERS += \
    cell.h \
    generateuretat.h \
    etat.h \
    voisinage.h \
    transitionrule.h \
    cellularautomata.h \
    automateexception.h \
    cabuilder.h \
    mainwindow.h \
    fenetre1d.h \
    fenetre2d.h \
    fenetreconfig.h
