attribute highp vec4 qt_Vertex; // = VerPos
attribute highp vec4 qt_MultiTexCoord0; // = VerClr ?
uniform highp mat4 qt_ModelViewProjectionMatrix; // = MVP

varying highp vec4 qt_TexCoord0;
varying highp vec4 projectedPosition;
varying highp vec4 entryPoint; // = EntryPoint
varying highp vec4 entryPointTexCoord; // = EntryPoint
varying highp vec4 exitPointCoord; // = EntryPointCoord

void main(void)
{
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    projectedPosition = gl_Position;
    entryPoint = qt_Vertex;
    entryPointTexCoord = qt_Vertex; // Should be set to a texture coordinate
}
