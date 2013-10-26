#ifndef VOLUMEITEM_H
#define VOLUMEITEM_H

#include <QQuickItem3D>

class VolumeItem : public QQuickItem3D
{
    Q_OBJECT
public:
    explicit VolumeItem(QQuickItem3D *parent = 0);


signals:

public slots:

private:

    // QQuickItem3D interface
public:
    void draw(QGLPainter *painter);
};

#endif // VOLUMEITEM_H
