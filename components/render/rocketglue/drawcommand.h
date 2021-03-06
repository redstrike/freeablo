#ifndef DRAW_COMMAND_H
#define DRAW_COMMAND_H

#include <misc/disablewarn.h>
    #include <Rocket/Core.h>
#include <misc/enablewarn.h>

#include <vector>

struct DrawCommand
{
    enum
    {
        Draw,
        EnableScissor,
        SetScissor
    } mode;

    struct
    {
        std::vector<Rocket::Core::Vertex> vertices;
        std::vector<int> indices;
        Rocket::Core::TextureHandle texture;
        Rocket::Core::Vector2f translation;
    } draw;
    
    struct
    {
        int x;
        int y;
        int width;
        int height;
    } setScissor;

    bool enableScissor;
};

#endif
