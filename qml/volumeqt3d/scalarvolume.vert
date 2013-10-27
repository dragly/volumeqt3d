attribute highp vec4 qt_Vertex; // = VerPos
attribute highp vec4 qt_MultiTexCoord0; // = VerClr ?
//attribute highp vec4 qt_Custom0;
uniform highp mat4 qt_ModelViewProjectionMatrix; // = MVP

varying highp vec4 qt_TexCoord0;
varying highp vec4 entryPoint; // = EntryPoint
varying highp vec4 entryPointTexCoord; // = EntryPoint
varying highp vec4 exitPointCoord; // = EntryPointCoord
//varying highp vec4 eyeCoord;
//varying highp vec4 texCoord3D;

void main(void)
{
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    qt_TexCoord0 = qt_MultiTexCoord0;
//    texCoord3D = qt_Custom0;
    entryPoint = qt_Vertex;
    entryPointTexCoord = qt_Vertex; // Should be set to a texture coordinate
//    exitPointCoord = gl_Position;
}
