QT += quick gui widgets quickwidgets

# win32: QT += winextras


INCLUDEPATH += cpp/CustomQmlTypes
INCLUDEPATH += cpp

TARGET = Gates
OBJECTS_DIR = obj
UI_DIR = ui
MOC_DIR = moc

SOURCES += \
        QmlEngine.cpp \
        cpp/Core/GatesFrameDispatcher.cpp \
        cpp/CustomQmlTypes/DesktopService.cpp \
        cpp/CustomQmlTypes/DirEntryModel.cpp \
        cpp/CustomQmlTypes/FileSystemModel.cpp \
        cpp/CustomQmlTypes/GatesFrameState.cpp \
        cpp/CustomQmlTypes/IconProvider.cpp \
        cpp/CustomQmlTypes/ResizableFramelessWindow.cpp \
        cpp/CustomQmlTypes/RoundedRect.cpp \
        cpp/Foreign/GatesFrameForeign.cpp \
        cpp/Widgets/MainWindow.cpp \
        cpp/utilities/BlurBehindHelper/BlurBehindHelper.cpp \
        cpp/utilities/DesktopIconsHelper/DesktopIconsHelper.cpp \
        cpp/utilities/FileIconManager/FileIconProvider.cpp \
        cpp/utilities/ResizableHelper/ResizableHelper.cpp \
        # cpp/utilities/win/shellqt.cpp \
        main.cpp



# resources.files = main.qml
# resources.prefix = /$${TARGET}

resources.files = qml/Frame.qml \
qml/FrameNameBar.qml \
qml/GatesGridViewDelegate.qml \
qml/NameBarCustomButton.qml \
qml/IconGridView.qml \
qml/GatesFrame.qml

resources.prefix = /$${TARGET}
RESOURCES += resources \
    resources.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    QmlEngine.h \
    cpp/Core/GatesFrameDispatcher.h \
    cpp/CustomQmlTypes/DesktopService.h \
    cpp/CustomQmlTypes/DirEntryModel.h \
    cpp/CustomQmlTypes/FileSystemModel.h \
    cpp/CustomQmlTypes/GatesFrameState.h \
    cpp/CustomQmlTypes/IconProvider.h \
    cpp/CustomQmlTypes/ResizableFramelessWindow.h \
    cpp/CustomQmlTypes/RoundedRect.h \
    cpp/Foreign/GatesFrameForeign.h \
    cpp/Widgets/MainWindow.h \
    cpp/utilities/BlurBehindHelper/BlurBehindHelper.h \
    cpp/utilities/DesktopIconsHelper/DesktopIconsHelper.h \
    cpp/utilities/FileIconManager/FileIconProvider.h \
    cpp/utilities/ResizableHelper/ResizableHelper.h \
    cpp/utilities/win/Functions.h \
    cpp/utilities/win/WinStructs.h \
    # cpp/utilities/win/shellqt.h
    cpp/Widgets/defs.h \

FORMS += \
    cpp/Widgets/MainWindow.ui

DISTFILES += \
    qml/BlurShader.qml \
    qml/CustomButton.qml \
    qml/Frame.qml \
    qml/FrameNameBar.qml \
    qml/GatesFrame.qml \
    qml/GatesGridViewDelegate.qml \
    qml/IconGridView.qml \
    qml/NameBarCustomButton.qml \

