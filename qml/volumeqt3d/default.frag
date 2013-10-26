varying highp vec4 texCoord;
//in vec3 voxelCoord;
uniform sampler3D myTexture3D;
uniform sampler2D qt_Texture0;

void main(void)
{
    mediump vec4 textureColor = texture2D(qt_Texture0, texCoord.st);
//    mediump vec4 textureColor2 = texture3D(myTexture3D, voxelCoord);
    gl_FragColor = textureColor;
}
