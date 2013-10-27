#extension GL_ARB_gpu_shader5 : enable
uniform sampler3D myTexture3D;
uniform highp mat4 qt_ModelViewMatrix; // = MV

varying highp vec4 entryPoint; // = EntryPoint
varying highp vec4 entryPointTexCoord; // = EntryPoint

void main(void)
{
    float stepSize = 0.005;
    mat4 inverseMatrix = inverse(qt_ModelViewMatrix);
    vec4 eyeCoord = inverseMatrix[3];
    vec3 eye = eyeCoord.xyz;
    vec3 exitPoint = eye;
    vec3 direction = exitPoint - entryPoint;
    float directionLength = length(direction);
    vec3 deltaDir = normalize(direction) * stepSize;
    float deltaDirLength = length(deltaDir);
    vec4 startPoint = entryPointTexCoord + vec4(0.5, 0.5, 0.5, 0.0); // TODO: Remove this after implementing proper texture coordinates
    vec3 voxelCoord = startPoint;
    vec4 colorAcummulated = vec4(1.0, 1.0, 1.0, 0.0);
    float traversedLength = 0.0;
    for(int i = 0; i < 1.732 / stepSize; i++) { // 1.732 = cube diagonal
        voxelCoord += deltaDir;
        vec3 voxelValue = texture3D(myTexture3D, voxelCoord);
        colorAcummulated += vec4(0.0, 0.0, 0.0, voxelValue.x) * stepSize * 2;
        traversedLength += deltaDirLength;
        if(voxelCoord.x > 1.0 || voxelCoord.y > 1.0 || voxelCoord.z > 1.0
                || voxelCoord.x < 0.0 || voxelCoord.y < 0.0 || voxelCoord.z < 0.0) {
            break;
        }
    }
    gl_FragColor = vec4(colorAcummulated);

    // Testing:
    //    gl_FragColor = vec4(normalize(eye).xyz, 1.0);
    //    gl_FragColor = vec4(normalize(direction).xyz, 1.0);
    //    gl_FragColor = vec4(normalize(eyeCoord).xyz, 1.0);
    //    gl_FragColor = vec4(deltaDir.xyz * 100.0, 1.0);
    //    gl_FragColor = vec4(traversedLength, 0.0, 0.0, 1.0);
//        gl_FragColor = vec4(texture2D(qt_Texture0, gl_FragCoord.xy / vec2(1000, 800)));

}
