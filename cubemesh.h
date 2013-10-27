#ifndef CUBEMESH_H
#define CUBEMESH_H

#include <QQuickItem>
#include <QQuickMesh>

class CubeMeshPrivate;

class CubeMesh : public QQuickMesh
{
    Q_OBJECT
public:
    explicit CubeMesh(QQuickItem *parent = 0);

    void createGeometry();
    ~CubeMesh();
signals:

public slots:

private:
    CubeMeshPrivate* d;

};

#endif // CUBEMESH_H
