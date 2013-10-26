import QtQuick 2.0
import Dragly 1.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Viewport {
    width: 1000
    height: 800

    //    Sphere {
    //        effect: Effect {
    //            color: "red"
    //        }
    //    }

    light: Light {
        position: Qt.vector3d(10,20,5)
    }

    Item3D {
        mesh: Mesh { source: "cube.obj" }
        effect: VolumeShaderProgram {
            property real multiplier: 2
//            texture: "qtlogo.png"
            texture3D: "head256.raw"

            vertexShader: "
                        attribute highp vec4 qt_Vertex;
                        uniform highp mat4 qt_ModelViewProjectionMatrix;

                        attribute highp vec4 qt_MultiTexCoord0;
                        varying highp vec4 texCoord;

                        void main(void)
                        {
                            texCoord = qt_MultiTexCoord0;
                            gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
                        }
                        "
            fragmentShader: "
                        varying highp vec4 texCoord;
//                        uniform sampler2D qt_Texture0;
                        uniform sampler3D myTexture3D;
                        uniform highp float multiplier;

                        void main(void)
                        {
                            mediump vec4 textureColor = texture3D(myTexture3D, texCoord.stp);
                            gl_FragColor = textureColor;
                        }
                        "
        }
    }

    //    VolumeItem {
    //        mesh: Mesh {
    //            source: "cube.obj"
    //        }
    //        mesh: SphereMesh {}
    //        effect: ShaderProgram {
    //            texture: "qtlogo.png"

    //            vertexShader: "
    //            attribute highp vec4 qt_Vertex;
    //            uniform highp mat4 qt_ModelViewProjectionMatrix;

    //            attribute highp vec4 qt_MultiTexCoord0;
    //            varying highp vec4 texCoord;

    //            void main(void)
    //            {
    //                texCoord = qt_MultiTexCoord0;
    //                gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    //            }
    //            "
    //            fragmentShader: "
    //            varying highp vec4 texCoord;
    //            uniform sampler2D qt_Texture0;

    //            void main(void)
    //            {
    //                mediump vec4 textureColor = texture2D(qt_Texture0, texCoord.st);
    //                gl_FragColor = textureColor;
    //            }
    //            "
    //        }
    //    }
}
