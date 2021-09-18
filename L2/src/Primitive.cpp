#include "Primitive.h"

#include <iostream>

#include <glm/gtx/string_cast.hpp>


State Shape::getState()
{
    float* arr = new float[getArraySize()];
    populateBuffer(arr);

    return State(m_entry, arr);
}

Rectangle::Rectangle(Renderer* renderer)
    :
    Shape(renderer, renderer->getRectangleEntry()), pos(0.0f), width(0.0f), height(0.0f)
{
}

Rectangle::Rectangle(Renderer* renderer, const float& _x, const float& _y, const float& _z, const float& _width, const float& _height)
    :
    Shape(renderer, renderer->getRectangleEntry()), pos(_x, _y, _z, 1.0f), width(_width), height(_height)
{
}

Rectangle::Rectangle(Renderer* renderer, const glm::vec3& _pos, const float& _width, const float& _height)
    :
    Shape(renderer, renderer->getRectangleEntry()), pos(_pos, 1.0f), width(_width), height(_height)
{
}

Rectangle::Rectangle(Renderer* renderer, const float& _x, const float& _y, const float& _z, const float& _width, const float& _height, const Color& _color)
    :
    Shape(renderer, renderer->getRectangleEntry(), _color), pos(_x, _y, _z, 1.0f), width(_width), height(_height)

{
}

Rectangle::Rectangle(Renderer* renderer, const glm::vec3& _pos, const float& _width, const float& _height, const Color& _color)
    :
    Shape(renderer, renderer->getRectangleEntry(), _color), pos(_pos, 1.0f), width(_width), height(_height)
{
}

void Rectangle::setPosition(const glm::vec3& position)
{
    pos = glm::vec4(position, 1.0f);
}

void Rectangle::setRenderer(Renderer* renderer)
{
    m_renderer = renderer; 
    m_entry = renderer->getRectangleEntry();
}

void Rectangle::populateBuffer(float* data)
{

    v0.x = 0.0f;    v1.x = 0.0f;           v2.x = 0.0f + width;    v3.x = 0.0f + width;
    v0.y = 0.0f;    v1.y = 0.0f + height;  v2.y = 0.0f + height;   v3.y = 0.0f;
    v0.z = 0.0f;    v1.z = 0.0f;           v2.z = 0.0f;            v3.z = 0.0f;
    v0.w = 1.0f;    v1.w = 1.0f;           v2.w = 1.0f;            v3.w = 1.0f;

    transform[0][3] = pos.x;
    transform[1][3] = pos.y;
    transform[2][3] = pos.z;

    v0 = v0 * transform;
    v1 = v1 * transform;
    v2 = v2 * transform;
    v3 = v3 * transform;

    //  pos
    //  0               1                      2                        3
    data[0] = v0.x;    data[6] = v1.x;         data[12] = v2.x;      data[18] = v3.x;
    data[1] = v0.y;    data[7] = v1.y;         data[13] = v2.y;      data[19] = v3.y;
    data[2] = v0.z;    data[8] = v1.z;         data[14] = v2.z;      data[20] = v3.z;

    // r                       g                    b
    data[3] =   color.r;     data[4] =  color.g;    data[5] =   color.b;
    data[9] =   color.r;     data[10] = color.g;    data[11] =  color.b;
    data[15] =  color.r;     data[16] = color.g;    data[17] =  color.b;
    data[21] =  color.r;     data[22] = color.g;    data[23] =  color.b;

}

Circle::Circle(Renderer* renderer)
    :
    Shape(renderer, renderer->getCircleEntry()), pos(0.0f), radius(0.0f)
{
}

Circle::Circle(Renderer* renderer, const float& _x, const float& _y, const float& _z, const float& _radius)
    :
    Shape(renderer, renderer->getCircleEntry()), pos(_x, _y, _z, 1.0f), radius(_radius)
{
}

Circle::Circle(Renderer* renderer, const glm::vec3& _pos, const float& _radius)
    :
    Shape(renderer, renderer->getCircleEntry()), pos(_pos, 1.0f), radius(_radius)
{
}

Circle::Circle(Renderer* renderer, const float& _x, const float& _y, const float& _z, const float& _radius, const Color& _color)
    :
    Shape(renderer, renderer->getCircleEntry(), _color), pos(_x, _y, _z, 1.0f), radius(_radius)
{
}

Circle::Circle(Renderer* renderer, const glm::vec3& _pos, const float& _radius, const Color& _color)
    :
    Shape(renderer, renderer->getCircleEntry(), _color), pos(_pos, 1.0f), radius(_radius)
{
}

void Circle::setPosition(const glm::vec3& position)
{
    pos = glm::vec4(position, 1.0f);
}

void Circle::setRenderer(Renderer* renderer)
{
    m_renderer = renderer;
    m_entry = renderer->getCircleEntry();
}

void Circle::populateBuffer(float* data)
{
    v0.x = 0.0f;    v1.x = 0.0f;                v2.x = 0.0f + 2 * radius;   v3.x = 0.0f + 2 * radius;
    v0.y = 0.0f;    v1.y = 0.0f + 2 * radius;   v2.y = 0.0f + 2 * radius;   v3.y = 0.0f;
    v0.z = 0.0f;    v1.z = 0.0f;                v2.z = 0.0f;                v3.z = 0.0f;
    v0.w = 1.0f;    v1.w = 1.0f;                v2.w = 1.0f;                v3.w = 1.0f;


    transform[0][3] = pos.x;
    transform[1][3] = pos.y;
    transform[2][3] = pos.z;


    v0 = v0 * transform;
    v1 = v1 * transform;
    v2 = v2 * transform;
    v3 = v3 * transform;

    //  pos
    //  0               1                      2                        3
    data[0] = v0.x;    data[9] = v1.x;          data[18] = v2.x;      data[27] = v3.x;
    data[1] = v0.y;    data[10] = v1.y;         data[19] = v2.y;      data[28] = v3.y;
    data[2] = v0.z;    data[11] = v1.z;         data[20] = v2.z;      data[29] = v3.z;

    //  center
    //  0               1                      2                        3
    data[3] = v0.x + radius;   data[12] = v1.x + radius;  data[21] = v2.x - radius;  data[30] = v3.x - radius;
    data[4] = v0.y + radius;   data[13] = v1.y - radius;  data[22] = v2.y - radius;  data[31] = v3.y + radius;
    data[5] = radius;          data[14] = radius;         data[23] = radius;         data[32] = radius;

    // r                       g                    b
    data[6] =   color.r;     data[7] =  color.g;    data[8] =   color.b;
    data[15] =  color.r;     data[16] = color.g;    data[17] =  color.b;
    data[24] =  color.r;     data[25] = color.g;    data[26] =  color.b;
    data[33] =  color.r;     data[34] = color.g;    data[35] =  color.b;

}

Line::Line(Renderer* renderer)
    :
    Shape(renderer, renderer->getLineEntry()), pos1(0.0f), pos2(0.0f)
{
}

Line::Line(Renderer* renderer, const float& _x1, const float& _y1, const float& _z1, const float& _x2, const float& _y2, const float& _z2)
    :
    Shape(renderer, renderer->getLineEntry()), pos1(_x1, _y1, _z1, 1.0f), pos2(_x2, _y2, _z2, 1.0f)
{
}

Line::Line(Renderer* renderer, const glm::vec3& _pos1, const glm::vec3& _pos2)
    :
    Shape(renderer, renderer->getLineEntry()), pos1(_pos1, 1.0f), pos2(_pos2, 1.0f)
{
}

Line::Line(Renderer* renderer, const float& _x1, const float& _y1, const float& _z1, const float& _x2, const float& _y2, const float& _z2, const Color& _color)
    :
    Shape(renderer, renderer->getLineEntry(), _color), pos1(_x1, _y1, _z1, 1.0f), pos2(_x2, _y2, _z2, 1.0f)
{
}

Line::Line(Renderer* renderer, const glm::vec3& _pos1, const glm::vec3& _pos2, const Color& _color)
    :
    Shape(renderer, renderer->getLineEntry(), _color), pos1(_pos1, 1.0f), pos2(_pos2, 1.0f)
{
}

void Line::setPosition(const glm::vec3& position)
{
    float diff_x = position.x - pos1.x;
    float diff_y = position.y - pos1.y;
    pos2.x += diff_x;
    pos2.y += diff_y;
    pos1.x += diff_x;
    pos1.y += diff_y;
}

void Line::setRenderer(Renderer* renderer)
{
    m_renderer = renderer;
    m_entry = renderer->getLineEntry();
}

void Line::populateBuffer(float* data)
{
    v0.x = 0.0f;    v1.x = pos2.x - pos1.x;
    v0.y = 0.0f;    v1.y = pos2.y - pos1.y;   
    v0.z = 0.0f;    v1.z = 0.0f;
    v0.w = 1.0f;    v1.w = 1.0f;                

    transform[0][3] = pos1.x;
    transform[1][3] = pos1.y;
    transform[2][3] = pos1.z;

    v0 = v0 * transform;
    v1 = v1 * transform;

    //  pos
    //  0               1
    data[0] = v0.x;    data[6] = v1.x;   
    data[1] = v0.y;    data[7] = v1.y;
    data[2] = v0.z;    data[8] = v1.z;

    // r                       g                    b
    data[3] =   color.r;     data[4] =  color.g;    data[5] =   color.b;
    data[9] =   color.r;     data[10] = color.g;    data[11] =  color.b;
}

Point::Point(Renderer* renderer)
    :
    Shape(renderer, renderer->getPointEntry()), pos(0.0f)
{
}

Point::Point(Renderer* renderer, const float& _x, const float& _y, const float& _z)
    :
    Shape(renderer, renderer->getPointEntry()), pos(_x, _y, _z, 1.0f)
{
}

Point::Point(Renderer* renderer, const glm::vec3& _pos)
    :
    Shape(renderer, renderer->getPointEntry()), pos(_pos, 1.0f)
{
}

Point::Point(Renderer* renderer, const float& _x, const float& _y, const float& _z, const Color& _color)
    :
    Shape(renderer, renderer->getPointEntry(), _color), pos(_x, _y, _z, 1.0f)
{
}

Point::Point(Renderer* renderer, const glm::vec3& _pos, const Color& _color)
    :
    Shape(renderer, renderer->getPointEntry(), _color), pos(_pos, 1.0f)
{
}

void Point::setPosition(const glm::vec3& position)
{
    pos = glm::vec4(position, 1.0f);
}

void Point::setRenderer(Renderer* renderer)
{
    m_renderer = renderer;
    m_entry = renderer->getPointEntry();
}

void Point::populateBuffer(float* data)
{
    //  pos
    //  0
    data[0] = pos.x;
    data[1] = pos.y;
    data[2] = pos.z;

    // r                       g                    b
    data[3] = color.r;     data[4] = color.g;    data[5] = color.b;
}

Sprite::Sprite(Renderer* renderer, TextureSource* source_texture)
    :
    Shape(renderer, renderer->getSpriteEntry(source_texture->getTextureSlot())), pos(0.0f), width(0.0f), height(0.0f),
    m_texture_source(source_texture)
{
}

Sprite::Sprite(Renderer* renderer, TextureSource* source_texture, const float& _x, const float& _y, const float& _z, const float& _width, const float& _height)
    :
    Shape(renderer, renderer->getSpriteEntry(source_texture->getTextureSlot())), pos(_x, _y, _z, 1.0f), width(_width), height(_height),
    m_texture_source(source_texture)
{
}

Sprite::Sprite(Renderer* renderer, TextureSource* source_texture, const glm::vec3& _pos, const float& _width, const float& _height)
    :
    Shape(renderer, renderer->getSpriteEntry(source_texture->getTextureSlot())), pos(_pos, 1.0f), width(_width), height(_height),
    m_texture_source(source_texture)
{
}

Sprite::Sprite(Renderer* renderer, TextureSource* source_texture, const float& _x, const float& _y, const float& _z, const float& _width, const float& _height, const Color& _color)
    :
    Shape(renderer, renderer->getSpriteEntry(source_texture->getTextureSlot()), _color), pos(_x, _y, _z, 1.0f), width(_width), height(_height),
    m_texture_source(source_texture)
{
}

Sprite::Sprite(Renderer* renderer, TextureSource* source_texture, const glm::vec3& _pos, const float& _width, const float& _height, const Color& _color)
    :
    Shape(renderer, renderer->getSpriteEntry(source_texture->getTextureSlot()), _color), pos(_pos, 1.0f), width(_width), height(_height),
    m_texture_source(source_texture)
{
}

void Sprite::setPosition(const glm::vec3& position)
{
    pos = glm::vec4(position, 1.0f);
}

void Sprite::setRenderer(Renderer* renderer)
{
    m_renderer = renderer;
    m_entry = renderer->getSpriteEntry(m_texture_source->getTextureSlot());
}

void Sprite::setTextureSource(TextureSource* texture_source)
{
    m_texture_source = texture_source;
}

void Sprite::populateBuffer(float* data)
{
    v0.x = 0.0f;    v1.x = 0.0f;           v2.x = 0.0f + width;    v3.x = 0.0f + width;
    v0.y = 0.0f;    v1.y = 0.0f + height;  v2.y = 0.0f + height;   v3.y = 0.0f;
    v0.z = 0.0f;    v1.z = 0.0f;           v2.z = 0.0f;            v3.z = 0.0f;
    v0.w = 1.0f;    v1.w = 1.0f;           v2.w = 1.0f;            v3.w = 1.0f;

    transform[0][3] = pos.x;
    transform[1][3] = pos.y;
    transform[2][3] = pos.z;

    v0 = v0 * transform;
    v1 = v1 * transform;
    v2 = v2 * transform;
    v3 = v3 * transform;

    //  pos
    //  0               1                      2                        3
    data[0] = v0.x;    data[9] =  v1.x;         data[18] = v2.x;      data[27] = v3.x;
    data[1] = v0.y;    data[10] = v1.y;         data[19] = v2.y;      data[28] = v3.y;
    data[2] = v0.z;    data[11] = v1.z;         data[20] = v2.z;      data[29] = v3.z;

    // r                       g                    b
    data[3] =   color.r;     data[4] =  color.g;    data[5] =   color.b;
    data[12] =  color.r;     data[13] = color.g;    data[14] =  color.b;
    data[21] =  color.r;     data[22] = color.g;    data[23] =  color.b;
    data[30] =  color.r;     data[31] = color.g;    data[32] =  color.b;

    TexCoords tc = m_texture_source->getTextureCoordinatesNormalised();

    // tex coord
    //  0           1               2                   3

    data[6] = tc.top_left.x;     data[15] = tc.bot_left.x;     data[24] = tc.bot_right.x;     data[33] = tc.top_right.x;
    data[7] = tc.top_left.y;     data[16] = tc.bot_left.y;     data[25] = tc.bot_right.y;     data[34] = tc.top_right.y;

    // tex id

    float texture_slot = m_texture_source->getTextureSlot();

    data[8] =  texture_slot;
    data[17] = texture_slot;
    data[26] = texture_slot;
    data[35] = texture_slot;
}
