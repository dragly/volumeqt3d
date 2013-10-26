#include <volumeeffect.h>

#include <QtCore/qdir.h>

#include <QtGui/QGuiApplication>
#include <QtQuick/qquickview.h>

#include <QtCore/qdebug.h>

#include <QOpenGLShaderProgram>
#include <QGLFormat>

int main(int argc, char *argv[])
{
//    qmlRegisterType<VolumeItem>("Dragly", 1, 0, "VolumeItem");
    qmlRegisterType<VolumeShaderProgram>("Dragly", 1, 0, "VolumeShaderProgram");

//    QOpenGLContext context;

    QGuiApplication app(argc, argv);
    QSurfaceFormat f;
    f.setSamples(0);
//    f.setOption(QSurfaceFormat::StereoBuffers);
    QQuickView view;
    view.setFormat(f);
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    qDebug() << QGLFormat::openGLVersionFlags();
#ifdef Q_OS_ANDROID
    view.setSource(QUrl(QLatin1String("assets:/")+QStringLiteral("qml/volumeqt3d/main.qml")));
#else
    view.setSource(QUrl::fromLocalFile("qml/volumeqt3d/main.qml"));
#endif
    if (QGuiApplication::arguments().contains(QLatin1String("-maximize")))
        view.showMaximized();
    else if (QGuiApplication::arguments().contains(QLatin1String("-fullscreen")))
        view.showFullScreen();
    else
        view.show();
    return app.exec();
}
