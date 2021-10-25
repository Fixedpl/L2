#include "Drawable.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "Texture.h"


State BufferFiller::getState()
{
    float* arr = new float[getArraySize()];
    populateBuffer(arr);

    return State(m_entry, arr);
}

void Rectangle::populateBuffer(float* data)
{
    glm::vec4 v0, v1, v2, v3;

    glm::mat4 transform = getWorldTransform();
    //std::cout << glm::to_string(transform) << "\n";

    v0.x = -m_origin.x;    v1.x = -m_origin.x;             v2.x = -m_origin.x + m_width;  v3.x = -m_origin.x + m_width;
    v0.y = -m_origin.y;    v1.y = -m_origin.y + m_height;  v2.y = -m_origin.y + m_height; v3.y = -m_origin.y;
    v0.z = -m_origin.z;    v1.z = -m_origin.z;             v2.z = -m_origin.z ;           v3.z = -m_origin.z;
    v0.w = 1.0f;           v1.w = 1.0f;                    v2.w = 1.0f;                   v3.w = 1.0f;

    v0 = transform * v0;
    v1 = transform * v1;
    v2 = transform * v2;
    v3 = transform * v3;

    //  pos
    //  0               1                      2                        3
    data[0] = v0.x;    data[6] = v1.x;         data[12] = v2.x;      data[18] = v3.x;
    data[1] = v0.y;    data[7] = v1.y;         data[13] = v2.y;      data[19] = v3.y;
    data[2] = v0.z;    data[8] = v1.z;         data[14] = v2.z;      data[20] = v3.z;

    // r                       g                    b
    data[3] =   m_color.r;     data[4] =  m_color.g;    data[5] =   m_color.b;
    data[9] =   m_color.r;     data[10] = m_color.g;    data[11] =  m_color.b;
    data[15] =  m_color.r;     data[16] = m_color.g;    data[17] =  m_color.b;
    data[21] =  m_color.r;     data[22] = m_color.g;    data[23] =  m_color.b;
}

void Circle::populateBuffer(float* data)
{
    glm::vec4 v0, v1, v2, v3;

    glm::mat4 transform = getWorldTransform();


    v0.x = -m_origin.x;    v1.x = -m_origin.x;                v2.x = -m_origin.x + 2 * m_radius; v3.x = -m_origin.x + 2 * m_radius;
    v0.y = -m_origin.y;    v1.y = -m_origin.y + 2 * m_radius; v2.y = -m_origin.y + 2 * m_radius; v3.y = -m_origin.y;
    v0.z = -m_origin.z;    v1.z = -m_origin.z;                v2.z = -m_origin.z;                v3.z = -m_origin.z;
    v0.w = 1.0f;           v1.w = 1.0f;                       v2.w = 1.0f;                       v3.w = 1.0f;


    v0 = transform * v0;
    v1 = transform * v1;
    v2 = transform * v2;
    v3 = transform * v3;


    //  pos
    //  0               1                      2                        3
    data[0] = v0.x;    data[9] =  v1.x;         data[18] = v2.x;      data[27] = v3.x;
    data[1] = v0.y;    data[10] = v1.y;         data[19] = v2.y;      data[28] = v3.y;
    data[2] = v0.z;    data[11] = v1.z;         data[20] = v2.z;      data[29] = v3.z;

    //  center
    //  0               1                      2                        3
    data[3] = v0.x + m_radius;   data[12] = v1.x + m_radius;  data[21] = v2.x - m_radius;  data[30] = v3.x - m_radius;
    data[4] = v0.y + m_radius;   data[13] = v1.y - m_radius;  data[22] = v2.y - m_radius;  data[31] = v3.y + m_radius;
    data[5] = m_radius;          data[14] = m_radius;         data[23] = m_radius;         data[32] = m_radius;

    // r                       g                    b
    data[6] =   m_color.r;     data[7] =  m_color.g;    data[8] =   m_color.b;
    data[15] =  m_color.r;     data[16] = m_color.g;    data[17] =  m_color.b;
    data[24] =  m_color.r;     data[25] = m_color.g;    data[26] =  m_color.b;
    data[33] =  m_color.r;     data[34] = m_color.g;    data[35] =  m_color.b;
}


void Line::populateBuffer(float* data)
{
    glm::vec4 v0, v1;


    v0.x = -m_origin.x;    v1.x = -m_origin.x + m_finish.x - m_start.x;
    v0.y = -m_origin.y;    v1.y = -m_origin.y + m_finish.y - m_start.y;
    v0.z = -m_origin.z;    v1.z = -m_origin.z;
    v0.w = 1.0f;           v1.w = 1.0f;                


    glm::mat4 transform = getWorldTransform();

    v0 = transform * v0;
    v1 = transform * v1;

    //  pos
    //  0               1
    data[0] = v0.x;    data[6] = v1.x;   
    data[1] = v0.y;    data[7] = v1.y;
    data[2] = v0.z;    data[8] = v1.z;

    // r                       g                    b
    data[3] = m_color.r;     data[4] =  m_color.g;    data[5] =   m_color.b;
    data[9] = m_color.r;     data[10] = m_color.g;    data[11] =  m_color.b;
}

void Point::populateBuffer(float* data)
{
    glm::vec4 v0(0.0f);

    glm::mat4 transform = getWorldTransform();

    v0 = transform * v0;

    //  pos
    //  0
    data[0] = v0.x;
    data[1] = v0.y;
    data[2] = v0.z;

    // r                       g                    b
    data[3] = m_color.r;     data[4] = m_color.g;    data[5] = m_color.b;
}

void Sprite::populateBuffer(float* data)
{
    glm::vec4 v0, v1, v2, v3;

   glm::mat4 transform = getWorldTransform();

    v0.x = -m_origin.x;    v1.x = -m_origin.x;            v2.x = -m_origin.x + m_width;    v3.x = -m_origin.x + m_width;
    v0.y = -m_origin.y;    v1.y = -m_origin.y + m_height; v2.y = -m_origin.y + m_height;   v3.y = -m_origin.y;
    v0.z = -m_origin.z;    v1.z = -m_origin.z;            v2.z = -m_origin.z;              v3.z = -m_origin.z;
    v0.w = 1.0f;    v1.w = 1.0f;            v2.w = 1.0f;              v3.w = 1.0f;

    v0 = transform * v0;
    v1 = transform * v1;
    v2 = transform * v2;
    v3 = transform * v3;

    //  pos
    //  0               1                      2                        3
    data[0] = v0.x;     data[9] = v1.x;         data[18] = v2.x;      data[27] = v3.x;
    data[1] = v0.y;    data[10] = v1.y;         data[19] = v2.y;      data[28] = v3.y;
    data[2] = v0.z;    data[11] = v1.z;         data[20] = v2.z;      data[29] = v3.z;

    // r                       g                    b
    data[3] =  m_color.r;     data[4] =  m_color.g;    data[5] =  m_color.b;
    data[12] = m_color.r;     data[13] = m_color.g;    data[14] = m_color.b;
    data[21] = m_color.r;     data[22] = m_color.g;    data[23] = m_color.b;
    data[30] = m_color.r;     data[31] = m_color.g;    data[32] = m_color.b;

    const TexCoords tc = m_texture_source->getTextureCoordinatesNormalised();

    // tex coord
    //  0           1               2                   3

    data[6] = tc.bot_left.x;     data[15] = tc.top_left.x;     data[24] = tc.top_right.x;     data[33] = tc.bot_right.x;
    data[7] = tc.bot_left.y;     data[16] = tc.top_left.y;     data[25] = tc.top_right.y;     data[34] = tc.bot_right.y;

    // tex id

    const float texture_slot = m_texture_source->getTextureSlot();


    data[8] =  texture_slot;
    data[17] = texture_slot;
    data[26] = texture_slot;
    data[35] = texture_slot;
}
