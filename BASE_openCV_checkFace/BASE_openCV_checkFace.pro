QT       += core gui
QT       +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH       +=D:\OpenCV\opencv-4.5.4\buildQt\install\include
LIBS              +=D:\OpenCV\opencv-4.5.4\buildQt\install\x64\mingw\lib\libopencv_*.a
LIBS              +=D:\Dlib\dlib-19.24\build\lib\libdlib.a
INCLUDEPATH       +=D:\Dlib\dlib-19.24\build\include



CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    delete_info.cpp \
    face_match.cpp \
    faceck.cpp \
    facecpt.cpp \
    fcpt_gain.cpp \
    filedelet.cpp \
    infochge.cpp \
    main.cpp \
    mainwindow.cpp \
    picture_cap.cpp

HEADERS += \
    delete_info.h \
    face_match.h \
    faceck.h \
    facecpt.h \
    fcpt_gain.h \
    filedelet.h \
    infochge.h \
    mainwindow.h \
    picture_cap.h

FORMS += \
    delete_info.ui \
    face_match.ui \
    faceck.ui \
    facecpt.ui \
    fcpt_gain.ui \
    infochge.ui \
    mainwindow.ui \
    picture_cap.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
