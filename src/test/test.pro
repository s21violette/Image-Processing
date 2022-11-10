include(gtest_dependency.pri)

QT += gui

TEMPLATE = app
CONFIG += c++17
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread

SOURCES += \
        ../model/helpers/matrix.cc \
        ../model/model.cc \
        main.cpp         tst_filters.cpp

HEADERS += \
    ../model/helpers/matrix.h \
    ../model/model.h \
    test.h
