#-------------------------------------------------
#
# Project created by QtCreator 2017-11-13T23:15:13
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageSearch
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Preprocessing/ImageConverter.cpp \
    main.cpp \
    MonoPixmap.cpp

HEADERS += \
    Preprocessing/ImageConverter.h \
    MonoPixmap.h

SUBDIRS += \
    ImageSearch.pro

DISTFILES += \
    images/architecture1.jpg \
    images/architecture_2.jpg \
    images/bamarket115.jpg \
    images/black.jpg \
    images/butterflywallpaper.jpg \
    images/Chang_PermanentMidnightintheChairofJasperJohns_large.jpg \
    images/damien_hirst.jpg \
    images/damien_hirst_does_fashion_week.jpg \
    images/damien_hirst_virgin_mother.jpg \
    images/damienhirst.jpg \
    images/dhirst_a3b9ddea.jpg \
    images/diamondskull.jpg \
    images/doodle.jpg \
    images/england.jpg \
    images/englandpath.jpg \
    images/Hhirst_BGE.jpg \
    images/jasper_johns.jpg \
    images/johns_portrait_380x311.jpg \
    images/latrobe.jpg \
    images/red.jpg \
    images/Scotland_castle_wedding.jpg \
    images/targetjasperjohns.jpg \
    images/Tower-Bridge-at-night--London--England_web.jpg \
    images/uk-golf-scotland.jpg \
    images/wallacestevens.jpg
