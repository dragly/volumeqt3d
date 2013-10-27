#include "cubemesh.h"

#include <QGLBuilder>
#include <QGLAbstractScene>

class CubeMeshPrivate
{
public:
    CubeMeshPrivate();
    ~CubeMeshPrivate();

    QMap<int, QGLSceneNode *> lodGeometry;
    QGLSceneNode *topNode;
    QGLSceneNode *currentCube;
    Qt::Axis axis;
    bool sceneSet;
};

CubeMeshPrivate::CubeMeshPrivate()
    : topNode(new QGLSceneNode)
    , currentCube(0)
    , axis(Qt::ZAxis)
    , sceneSet(false)
{
    topNode->setObjectName(QLatin1String("CubeMesh"));
}

CubeMeshPrivate::~CubeMeshPrivate()
{
    topNode->removeNode(currentCube);
    delete topNode;
    QList<QGLSceneNode*> lods = lodGeometry.values();
    qDeleteAll(lods);
}

class CubeScene : public QGLAbstractScene
{
public:
    explicit CubeScene(QGLSceneNode *s) : m_s(s) {}
    ~CubeScene() {}
    QList<QObject *> objects() const
    {
        QList<QObject *> s;
        s.append(m_s);
        return s;
    }
    QGLSceneNode *mainNode() const
    {
        return m_s;
    }
private:
    QGLSceneNode *m_s;
};

CubeMesh::CubeMesh(QQuickItem *parent) :
    QQuickMesh(parent)
  , d(new CubeMeshPrivate)
{
    createGeometry();
}

CubeMesh::~CubeMesh() {
    delete d;
}

void CubeMesh::createGeometry() {
    QGLSceneNode* geometry;
    QGLBuilder builder;
    builder.newSection(QGL::NoSmoothing);

    QGeometryData quad;
//    QVector3DArray vertices = {
//        0.0, 0.0, 0.0,
//        0.0, 0.0, 1.0
//    };
//    quad.appendVertexArray();

    geometry = builder.finalizedSceneNode();
    geometry->setParent(this);
    if (!d->sceneSet)
    {
        setScene(new CubeScene(d->topNode));
        d->sceneSet = true;
    }
}
