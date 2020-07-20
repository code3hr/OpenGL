#shader vertex
#version 330
attribute vec3 position;

void main()
{
    gl_Position.xyz = position;
    gl_Position.w = 1.0;
}


#shader fragment
#version 120

void main()
{
    gl_FragColor = vec4(0.2, 0.3, 0.8, 1.0);
}