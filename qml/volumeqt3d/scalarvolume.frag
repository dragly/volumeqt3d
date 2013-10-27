//uniform sampler2D qt_Texture0;
uniform sampler3D myTexture3D;
uniform highp mat4 qt_ModelViewProjectionMatrix; // = MVP
uniform highp mat4 qt_ModelViewMatrix; // = MV
uniform highp mat4 qt_ProjectionMatrix; // = MV
//uniform vec3 eye;

varying highp vec4 qt_TexCoord0;
varying highp vec4 entryPoint; // = EntryPoint
varying highp vec4 exitPointCoord; // = EntryPointCoord
//varying highp vec4 eyeCoord;
//varying highp vec4 texCoord3D;

void main(void)
{
    // Original Qt:
    //    gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0.st);

//    gl_FragColor = vec4(qt_TexCoord0.xy, 1.0, 1.0);
//    gl_FragColor = vec4(entryPoint.xyz, 1.0);
//    gl_FragColor = vec4(texCoord3D.xyz, 1.0);


//    vec3 exitPoint = texture2D(qt_Texture0, gl_FragCoord.st / vec2(1000, 800)).xyz;
//    gl_FragColor = vec4(exitPoint, 1.0);

//    gl_FragColor = vec4(gl_FragCoord.xy / vec2(1000, 800), 0.0, 1.0);


//    vec3 eye = vec3(eyeX, eyeY, eyeZ);
    mat4 inverseMatrix = inverse(qt_ModelViewMatrix);
    vec4 eyeCoord = inverseMatrix[3];
//    vec3 eye = normalize(-eyeCoord.xyz / eyeCoord.w);
    vec3 eye = eyeCoord.xyz;
    vec3 exitPoint = vec3(gl_FragCoord.xy / vec2(1000, 800), 0);
    exitPoint += eye;
    gl_FragColor = vec4(1.0, 1.0, exitPoint.z, 1.0);
    vec3 direction = -exitPoint + entryPoint;
    float directionLength = length(direction);
    vec3 deltaDir = normalize(direction) * 0.01;
    float deltaDirLength = length(deltaDir);
    entryPoint += vec4(0.5, 0.5, 0.5, 0.0);
    vec3 voxelCoord = entryPoint;
    vec4 colorAcummulated = vec4(0.0, 0.0, 0.0, 1.0);
    float traversedLength = 0.0;
    for(int i = 0; i < 100; i++) {
        voxelCoord += deltaDir;
        vec3 voxelValue = texture3D(myTexture3D, voxelCoord);
        colorAcummulated += vec4(voxelValue.xyx * 0.02, 0.0);
        traversedLength += deltaDirLength;
        if(traversedLength > 1.0) {
            break;
        }
    }
    gl_FragColor = vec4(colorAcummulated);
//    gl_FragColor = vec4(normalize(eye).xyz, 1.0);
//    gl_FragColor = vec4(normalize(direction).xyz, 1.0);
    //    gl_FragColor = vec4(normalize(eyeCoord).xyz, 1.0);
//        gl_FragColor = vec4(deltaDir.xyz * 100.0, 1.0);
//    gl_FragColor = vec4(traversedLength, 0.0, 0.0, 1.0);
}
