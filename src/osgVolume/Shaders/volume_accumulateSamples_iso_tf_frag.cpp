char volume_accumulateSamples_iso_tf_frag[] = "#version 110\n"
                                              "\n"
                                              "uniform sampler3D volumeTexture;\n"
                                              "\n"
                                              "uniform sampler1D tfTexture;\n"
                                              "uniform float tfScale;\n"
                                              "uniform float tfOffset;\n"
                                              "\n"
                                              "uniform float IsoSurfaceValue;\n"
                                              "\n"
                                              "varying vec3 lightDirection;\n"
                                              "\n"
                                              "vec4 accumulateSamples(vec4 fragColor, vec3 ts, vec3 te, vec3 dt, float scale, float cutoff, int num_iterations)\n"
                                              "{\n"
                                              "    vec3 texcoord = te.xyz;\n"
                                              "\n"
                                              "    float normalSampleDistance = length(dt);\n"
                                              "    vec3 deltaX = vec3(normalSampleDistance, 0.0, 0.0);\n"
                                              "    vec3 deltaY = vec3(0.0, normalSampleDistance, 0.0);\n"
                                              "    vec3 deltaZ = vec3(0.0, 0.0, normalSampleDistance);\n"
                                              "\n"
                                              "    float previous_a = texture3D( volumeTexture, texcoord).a;\n"
                                              "\n"
                                              "    float targetValue = IsoSurfaceValue;\n"
                                              "\n"
                                              "    while(num_iterations>0)\n"
                                              "    {\n"
                                              "        float a = texture3D( volumeTexture, texcoord).a;\n"
                                              "        float m = (previous_a-targetValue) * (a-targetValue);\n"
                                              "        if (m <= 0.0)\n"
                                              "        {\n"
                                              "            float r = (targetValue-a)/(previous_a-a);\n"
                                              "            texcoord = texcoord - r*dt;\n"
                                              "\n"
                                              "            float v = targetValue * tfScale + tfOffset;\n"
                                              "            vec4 color = texture1D( tfTexture, v);\n"
                                              "\n"
                                              "            float px = texture3D( volumeTexture, texcoord + deltaX).a;\n"
                                              "            float py = texture3D( volumeTexture, texcoord + deltaY).a;\n"
                                              "            float pz = texture3D( volumeTexture, texcoord + deltaZ).a;\n"
                                              "\n"
                                              "            float nx = texture3D( volumeTexture, texcoord - deltaX).a;\n"
                                              "            float ny = texture3D( volumeTexture, texcoord - deltaY).a;\n"
                                              "            float nz = texture3D( volumeTexture, texcoord - deltaZ).a;\n"
                                              "\n"
                                              "            vec3 grad = vec3(px-nx, py-ny, pz-nz);\n"
                                              "            if (grad.x!=0.0 || grad.y!=0.0 || grad.z!=0.0)\n"
                                              "            {\n"
                                              "                vec3 normal = normalize(grad);\n"
                                              "                float lightScale = 0.1 +  max(0.0, dot(normal.xyz, lightDirection))*0.9;\n"
                                              "\n"
                                              "                color.r *= lightScale;\n"
                                              "                color.g *= lightScale;\n"
                                              "                color.b *= lightScale;\n"
                                              "            }\n"
                                              "            return color;\n"
                                              "        }\n"
                                              "\n"
                                              "        previous_a = a;\n"
                                              "\n"
                                              "        texcoord += dt;\n"
                                              "\n"
                                              "        --num_iterations;\n"
                                              "    }\n"
                                              "\n"
                                              "    return vec4(0.0, 0.0, 0.0, 0.0);\n"
                                              "}\n"
                                              "\n";
