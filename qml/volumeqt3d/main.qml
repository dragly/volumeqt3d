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
        center: Qt.vector3d(0.0, 0.0, 0.0)
        eye: Qt.vector3d(1.0, 1.0, 1.0)
        nearPlane: 0.01
        farPlane: 100
        fieldOfView: 120
    }

    light: Light {
        position: Qt.vector3d(-10,20,-5)
    }

    Item3D {
        cullFaces: Item3D.CullFrontFaces
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
