#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoord;

uniform vec2 uOffset;
uniform float uSize;
uniform float uDegrees;

vec2 increasePoint(vec2 point, float size)
{
    return point * size;
}
vec2 rotatePoint(vec2 point, float degrees)
{
    float a = radians(degrees);

    float x = point.x * cos(a) - point.y * sin(a);
    float y = point.x * sin(a) + point.y * cos(a);

    return vec2(x, y);
}
vec2 movePoint(vec2 point, vec2 offset)
{
    return vec2(point.x + offset.x, point.y - offset.y);
}

void main()
{
    vec2 newPos = vec2(aPos.x, aPos.y);
    newPos = increasePoint(newPos, uSize);
    newPos = rotatePoint(newPos, uDegrees);
    newPos = movePoint(newPos, uOffset);
    gl_Position = vec4(newPos, aPos.z, 1.0f);
    TexCoord = aTexCoord;
}