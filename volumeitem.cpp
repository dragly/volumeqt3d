#include "volumeitem.h"

#include <QQuickEffect>
#include <QOpenGLShaderProgram>
#include <volumeeffect.h>
#include <iostream>

using namespace std;

VolumeItem::VolumeItem(QQuickItem3D *parent) :
    QQuickItem3D(parent)
{
    //    QOpenGLShaderProgram program;
}

#define GL_ERROR() checkForOpenGLError(__FILE__, __LINE__)
int checkForOpenGLError(const char* file, int line)
{
    // return 1 if an OpenGL error occured, 0 otherwise.
    GLenum glErr;
    int retCode = 0;

    glErr = glGetError();
    while(glErr != GL_NO_ERROR)
    {
        cout << "glError in file " << file
             << "@line " << line << endl;
        retCode = 1;
        exit(EXIT_FAILURE);
    }
    return retCode;
}

void VolumeItem::draw(QGLPainter *painter)
{
    // Bail out if this item and its children have been disabled.
    if (!isEnabled())
        return;
    if (!isInitialized())
        initialize(painter);

    //    if (!d->bConnectedToOpenGLContextSignal) {
    //        QQuickWindow * pCanvas = window();
    //        Q_ASSERT(pCanvas);
    //        QOpenGLContext* pOpenGLContext = pCanvas->openglContext();
    //        Q_ASSERT(pOpenGLContext);
    //        bool Ok = QObject::connect(pOpenGLContext, SIGNAL(aboutToBeDestroyed()), this, SLOT(handleOpenglContextIsAboutToBeDestroyed()), Qt::DirectConnection);
    //        Q_UNUSED(Ok);  // quell compiler warning
    //        Q_ASSERT(Ok);
    //        d->bConnectedToOpenGLContextSignal = true;
    //    }

    //Setup picking
//    int prevId = painter->objectPickId();
//    painter->setObjectPickId(objectPickId());

    //Setup effect (lighting, culling, effects etc)
    const QGLLightParameters *currentLight = 0;
    QMatrix4x4 currentLightTransform;
    drawLightingSetup(painter, currentLight, currentLightTransform);
    bool viewportBlend, effectBlend;
    drawEffectSetup(painter, viewportBlend, effectBlend);
    drawCullSetup();

    //Local and Global transforms
    drawTransformSetup(painter);

    // ***** VOLUME RENDERING ******

//"head256.raw", 256, 256, 225
//    GLuint g_volTexObj = -1;
//    GLuint width = 256;
//    GLuint height = 256;
//    GLuint depth = 225;
//    FILE *fp;
//    size_t size = width * height * depth;
//    GLubyte *data = new GLubyte[size];			  // 8bit
//    if (!(fp = fopen("qml/volumeqt3d/head256.raw", "rb")))
//    {
//        cout << "Error: opening .raw file failed" << endl;
//        exit(EXIT_FAILURE);
//    }
//    else
//    {
//        cout << "OK: open .raw file successed" << endl;
//    }
//    if ( fread(data, sizeof(char), size, fp)!= size)
//    {
//        cout << "Error: read .raw file failed" << endl;
//        exit(1);
//    }
//    else
//    {
//        cout << "OK: read .raw file successed" << endl;
//    }
//    fclose(fp);
//    glGenTextures(1, &g_volTexObj);
//    VolumeEffect program;
//    program.setVertexShaderFromFile("qml/volumeqt3d/default.vert");
//    program.setFragmentShaderFromFile("qml/volumeqt3d/default.frag");
//    program.setActive(painter, true);


//    painter->glActiveTexture(GL_TEXTURE0);

//    qDebug() << "Fixed: " << painter->isFixedFunction();
//    qDebug() << program.link();
//    qDebug() << program.bind();
//    qDebug() << program.programId() << " " << program.shaders().at(1)->shaderId();
//    int vertexLocation = program.attributeLocation("vertex");
//    int matrixLocation = program.uniformLocation("matrix");
//    int colorLocation = program.uniformLocation("color");
//    int volumeTextureLocation = program.uniformLocation("VolumeTex");

//    glGenTextures(1, &g_volTexObj);
//    // bind 3D texture target
//    // bind 3D texture target
//    glBindTexture(GL_TEXTURE_3D, g_volTexObj);
//    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//    // pixel transfer happens here from client to OpenGL server
//    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
//    data[0] = 10;
//    glTexImage3D(GL_TEXTURE_3D, 0, GL_INTENSITY, width, height, depth, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
//    GL_ERROR();
    // ***** END VOLUME RENDERING ******


    //Drawing
    drawItem(painter);
    drawChildren(painter);

    //Cleanup
    drawTransformCleanup(painter);
    drawLightingCleanup(painter, currentLight, currentLightTransform);
    drawEffectCleanup(painter, viewportBlend, effectBlend);
    drawCullCleanup();

    //Reset pick id.
//    painter->setObjectPickId(prevId);

//    delete []data;
}
