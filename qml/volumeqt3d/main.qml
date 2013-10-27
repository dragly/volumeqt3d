import QtQuick 2.0
import Dragly 1.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Viewport {
    id: viewportRoot
    width: 1000
    height: 800

    //    Sphere {
    //        effect: Effect {
    //            color: "red"
    //        }
    //    }

    camera: Camera {
        id: myCamera
        eye: Qt.vector3d(5.0, 5.0, 5.0)
    }

    light: Light {
        position: Qt.vector3d(10,20,5)
    }

    Item3D {
        cullFaces: Item3D.CullDisabled
        mesh: Mesh {
            source: "cube.obj"
        }
        effect: VolumeShaderProgram {
            id: shaderProgram
            blending: true
            texture3D: "head256.raw"
            texture: "qtlogo.png"
            vertexShaderSource: "qml/volumeqt3d/scalarvolume.vert"
            fragmentShaderSource: "qml/volumeqt3d/scalarvolume.frag"
        }
    }
}
