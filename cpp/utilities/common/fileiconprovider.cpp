#include "fileiconprovider.h"
#include <QDebug>
#include <QElapsedTimer>

#include <qsystemdetection.h>
#include <QImageReader>
#include <QByteArray>

#ifdef Q_OS_WIN
#include "utilities/win/shellqt.h"
#endif

FileIconProvider::FileIconProvider()
{

}

QIcon FileIconProvider::icon(const QFileInfo &info) const
{
    auto imageFormat = QImageReader::imageFormat(info.filePath());

    if(!imageFormat.isEmpty())
    {
        qDebug() << "[FileIconProvider] : file " << info.fileName() << "seems to be an image";
        return extractImageIcon(info);
    }

#ifdef Q_OS_WIN
    return extractIcons(info.filePath());
#else
    return QFileIconProvider::icon(info);
#endif

}

QIcon FileIconProvider::extractImageIcon(const QFileInfo &info) const
{
    QImageReader reader;
    reader.setFileName(info.filePath());
    QIcon stdIcon = QFileIconProvider::icon(info);

    QImage image = reader.read();
    QPixmap pixmap = QPixmap::fromImage(image);
    qDebug() << "[FileIconProvider] : resulting pixmap size : " << pixmap.size();

    QIcon out;
    QElapsedTimer timer;

    timer.start();
//    out.addPixmap(stdIcon.pixmap({16, 16}));
    out.addPixmap(stdIcon.pixmap({32, 32}));
//    out.addPixmap(pixmap.scaled(64, 64, Qt::KeepAspectRatio  , Qt::FastTransformation));
    out.addPixmap(pixmap.scaled(128, 128, Qt::KeepAspectRatio, Qt::FastTransformation));
//    out.addPixmap(pixmap.scaled(256, 256, Qt::KeepAspectRatio, Qt::FastTransformation));
    out.addPixmap(pixmap.scaled(512, 512, Qt::KeepAspectRatio, Qt::FastTransformation));

    qDebug() << "[FileIconProvider] : Pixmap scalings took " << timer.elapsed() << " milliseconds";
    qDebug() << "                                          " << timer.nsecsElapsed() << " nanoseconds";

    return out;
}
