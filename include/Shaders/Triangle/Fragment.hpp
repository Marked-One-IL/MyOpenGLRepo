#pragma once
namespace Triangle
{
    constexpr const char *Fragment =
R"glsl(

#version 330 constexpr
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

)glsl";
}