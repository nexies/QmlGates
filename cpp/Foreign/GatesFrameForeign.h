#pragma once

#include <QObject>
#include "DirEntryModel.h"


class QQmlContext;
class QQuickWidget;

class GatesFrameForeign : public QObject
{
    Q_OBJECT
public:
    GatesFrameForeign(QObject * parent = nullptr);

    QWindow * window () { return _window; }

public slots:
    void show();
    void hide();
    void setVisible(bool visible);
    void setDirectory(const QString & directory);

    void setColor(const QColor & color);
    void setOpacity(float opacity);

protected:
    QString getNameForDirectory(const QString & path);

private:
    QQmlContext * _context { nullptr };
    QWindow * _window { nullptr };
    QQuickWidget * _widget { nullptr };
    DirEntryModel * _dirModel { nullptr };
};
