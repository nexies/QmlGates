#include <QApplication>
#include <QDebug>
#include <QDir>

#include <QStandardPaths>
#include "Foreign/GatesFrameForeign.h"
#include <QQuickWindow>

#include <QDebug>
#include "utilities/win/Functions.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
     GatesFrameForeign fr;
     qDebug() << QDir::homePath();
     fr.setDirectory(QDir::homePath() + QDir::separator() + "OneDrive" + QDir::separator() + "Рабочий стол");
     //fr.setDirectory(QDir::homePath());
     //fr.setDirectory(QDir::homePath());
     //"C:\Users\green\OneDrive\Рабочий стол"
     fr.setColor(Qt::red);
     fr.setOpacity(0.6);
     fr.show();

    //qDebug() << Q_FUNC_INFO;

    return a.exec();

    //return 0;
}

#endif
