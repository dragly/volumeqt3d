//uniform sampler2D qt_Texture0;
uniform sampler3D myTexture3D;

varying highp vec4 qt_TexCoord0;
varying highp vec4 entryPoint; // = EntryPoint
varying highp vec4 exitPointCoord; // = EntryPointCoord

void main(void)
{
    // Original Qt:
    //    gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0.st);

//    gl_FragColor = vec4(qt_TexCoord0.xy, 1.0, 1.0);
//    gl_FragColor = vec4(entryPoint.xyz, 1.0);
    gl_FragColor = vec4(exitPointCoord.xyz, 1.0);


//    vec3 exitPoint = texture2D(qt_Texture0, gl_FragCoord.st / vec2(1000, 800)).xyz;
//    gl_FragColor = vec4(exitPoint, 1.0);

//    gl_FragColor = vec4(gl_FragCoord.st / vec2(1000, 800), 0.0, 1.0);
    vec3 direction = exitPointCoord - entryPoint;
    float directionLength = length(direction);
    vec3 deltaDir = normalize(direction) * 0.01;
    vec3 voxelCoord = entryPoint;
    vec4 colorAcummulated = vec4(0.0, 0.0, 0.0, 1.0);
    for(int i = 0; i < 100; i++) {
        voxelCoord += deltaDir;
        vec3 voxelValue = texture3D(myTexture3D, voxelCoord);
        colorAcummulated += vec4(voxelValue.xyx * 0.01, 0.0);
    }
    gl_FragColor = vec4(colorAcummulated);
}
