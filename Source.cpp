#include "Angel.h"
#include "Sphere.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<iostream>

// OpenGL initialization
typedef Angel::vec4  color4;
typedef Angel::vec4  point4;
typedef Angel::vec3  point3;

const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

point4 points[NumVertices];
color4 colors[NumVertices];

GLfloat skyboxvertices[] = {
    // positions      //normal    // texture Coords
    -0.5f, -0.5f, -0.5f, 0.0f,0.0f,-1.0f, 0.0f, 0.0f,  //back - 
     0.5f, -0.5f, -0.5f, 0.0f,0.0f,-1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f,0.0f,-1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f,0.0f,-1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f,0.0f,-1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f,0.0f,-1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 0.0f,0.0f,1.0f,  0.0f, 0.0f,//front
     0.5f, -0.5f,  0.5f, 0.0f,0.0f,1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f,0.0f,1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f,0.0f,1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f,0.0f,1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f,0.0f,1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,0.0f,0,  1.0f, 0.0f,//left
    -0.5f,  0.5f, -0.5f, -1,0,0,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1,0,0,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1,0,0,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1,0,0,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1,0,0,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1,0,0,  1.0f, 0.0f,//right
     0.5f,  0.5f, -0.5f,  1,0,0,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1,0,0,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1,0,0,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1,0,0,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1,0,0,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0,-1,0, 0.0f, 1.0f,//bottom
     0.5f, -0.5f, -0.5f,  0,-1,0, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0,-1,0, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0,-1,0, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0,-1,0, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0,-1,0, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0,1,0, 0.0f, 1.0f,//top
     0.5f,  0.5f, -0.5f,  0,1,0, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0,1,0, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0,1,0, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0,1,0, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0,1,0, 0.0f, 1.0f
};



GLuint skyboxIndices[] = {
    0, 1, 2, 2, 3, 0,     // Front face
    4, 5, 6, 6, 7, 4,     // Back face
    1, 5, 6, 6, 2, 1,     // Right face
    0, 4, 7, 7, 3, 0,     // Left face
    3, 2, 6, 6, 7, 3,     // Top face
    0, 1, 5, 5, 4, 0      // Bottom face
};

//GLuint skyboxvertices[] =
//{
//    -1,-1,1,
//    1,-1,1,
//    1,-1,-1,
//    -1,-1,-1,
//    -1,1,1,
//    1,1,1,
//    1,1,-1,
//    -1,1,-1
//
//};

//GLuint skyboxIndices[] =
//{
//    // Right
//    1, 2, 6,
//    6, 5, 1,
//    // Left
//    0, 4, 7,
//    7, 3, 0,
//    // Top
//    4, 5, 6,
//    6, 7, 4,
//    // Bottom
//    0, 3, 2,
//    2, 1, 0,
//    // Back
//    0, 1, 5,
//    5, 4, 0,
//    // Front
//    3, 7, 6,
//    6, 2, 3
//};



// Texture coordinates for the cube (same for all faces)
GLfloat cubeTexCoords[] = {
    // Front face
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    // Back face
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    // Right face
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    // Left face
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    // Top face
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    // Bottom face
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f
};




// RGBA colors
color4 vertex_colors[8] = {
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(1.0, 0.0, 0.0, 1.0),  // red
    color4(1.0, 1.0, 0.0, 1.0),  // yellow
    color4(0.0, 1.0, 0.0, 1.0),  // green
    color4(0.0, 0.0, 1.0, 1.0),  // blue
    color4(1.0, 0.0, 1.0, 1.0),  // magenta
    color4(1.0, 1.0, 1.0, 1.0),  // white
    color4(0.0, 1.0, 1.0, 1.0)   // cyan
};



float size = 0.03;
Sphere sun(0.2f);
Sphere mercury(size * 0.25);
Sphere venus(size * 0.8);
Sphere earth(size);
Sphere mars(size * 0.5);
Sphere jupiter(size * 3);
Sphere saturn(size * 2);
Sphere uranus(size * 1.5);
Sphere neptune(size * 1.2);
Sphere spaceship(0.01);
Sphere fuel(0.06);
float speed = 0.1f, yaw = -90.0f;
GLuint program, vao, vbo1, ibo1, vbo2, ibo2, vbo3, ibo3, vbo4, ibo4, vbo5, ibo5, vbo6, ibo6, vbo7, ibo7
, vbo8, ibo8, vbo9, ibo9,theta,vbo10,ibo10,vbor,ibor,
vPosition, vPosition_static, vNormal, modelUnifrom,
vTexture, texture0, texture1, texture2, texture3, skyboxVAO, skyboxVBO, skyboxFragmentShaderSource,
texture4,texture5, texture6,texture7, texture8,texture9,textureskybox,
modelAttrib, viewUniform, projectionUniform, cameraUniform;
GLuint skyboxVAO, skyboxVBO, skyboxEBO;
int Index = 0;
void quad(int a, int b, int c, int d)
{
    colors[Index] = vertex_colors[a]; points[Index] = skyboxvertices[a]; Index++;
    colors[Index] = vertex_colors[b]; points[Index] = skyboxvertices[b]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = skyboxvertices[c]; Index++;
    colors[Index] = vertex_colors[a]; points[Index] = skyboxvertices[a]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = skyboxvertices[c]; Index++;
    colors[Index] = vertex_colors[d]; points[Index] = skyboxvertices[d]; Index++;

}
// generate 12 triangles: 36 vertices and 36 colors
void colorcube()
{
    quad(1, 0, 3, 2);
    quad(2, 3, 7, 6);
    quad(3, 0, 4, 7);
    quad(6, 5, 1, 2);
    quad(4, 5, 6, 7);
    quad(5, 4, 0, 1);

}


float Theta1 = 0.0f;
float Theta2 = 0.0f;
float Theta3 = 0.0f;
float Theta4 = 0.0f;
float Theta5 = 0.0f;
float Theta6 = 0.0f;
float Theta7 = 0.0f;
float Theta8 = 0.0f;
float Theta9 = 0.0f;
int timer = 40000;
int counter = 0;
glm::mat4 model;
float randoms[21];
glm::vec3 cameraPos, cameraTarget, cameraDirection, cameraRight, cameraUp, cameraFront,modelship;
glm::mat4 view, projection;
// Load deep space images for the skybox
GLuint skyboxTextures[6];


void initTexture()
{
    stbi_set_flip_vertically_on_load(true);
    ////sky Box
    //glGenTextures(1, &textureskybox);
    //glBindTexture(GL_TEXTURE_2D, texture0);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    //int width, height, channels;
    //unsigned char* data_s = stbi_load("skybox.jpg", &width, &height, &channels, 0);
    //if (data_s)
    //{
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_s);
    //    glGenerateMipmap(GL_TEXTURE_2D);
    //}

    //stbi_image_free(data_s);
    // 
    
    // Generate texture ID for the skybox
    glGenTextures(1, &textureskybox);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureskybox);

    

    // Load and assign each face of the cube map
    std::vector<std::string> faces = {
        "right.bmp", "left.bmp",
        "up.bmp", "down.bmp",
        "front.bmp", "back.bmp"
    };

    int width, height, channels;
    for (unsigned int i = 0; i < faces.size(); ++i) {
        unsigned char* data_s = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
        if (data_s) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_s);
            stbi_image_free(data_s);
        }
        else {
            // Handle error loading texture
            std::cout << "Failed to load texture: " << faces[i] << std::endl;
            stbi_image_free(data_s);
        }
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //sun
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    unsigned char* data1 = stbi_load("sun.jpg", &width, &height, &channels, 0);

    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data1);
    //mercury
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data2 = stbi_load("moon1024.bmp", &width, &height, &channels, 0);

    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data2);
    //venus
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data3 = stbi_load("moon1024.bmp", &width, &height, &channels, 0);

    if (data3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data3);
    //earth
    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data4 = stbi_load("earth2048.bmp", &width, &height, &channels, 0);

    if (data4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data4);
    //mars
    glGenTextures(1, &texture5);
    glBindTexture(GL_TEXTURE_2D, texture5);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data5 = stbi_load("mars.png", &width, &height, &channels, 0);

    if (data5)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data5);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data5);
    //jupiter
    glGenTextures(1, &texture6);
    glBindTexture(GL_TEXTURE_2D, texture6);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data6 = stbi_load("jupiter.jpg", &width, &height, &channels, 0);

    if (data6)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data6);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data6);
    //saturn
    glGenTextures(1, &texture7);
    glBindTexture(GL_TEXTURE_2D, texture7);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data7 = stbi_load("saturn.jpg", &width, &height, &channels, 0);

    if (data7)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data7);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data7);
    //uranus
    glGenTextures(1, &texture8);
    glBindTexture(GL_TEXTURE_2D, texture8);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data8 = stbi_load("uranus.jpg", &width, &height, &channels, 0);

    if (data8)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data8);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data8);
    //neptune
    glGenTextures(1, &texture9);
    glBindTexture(GL_TEXTURE_2D, texture9);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data9 = stbi_load("neptune.jpg", &width, &height, &channels, 0);

    if (data9)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data9);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data9);
}

void initLight()
{
    point4 light_direction1(-0.2, 0.0, 0.0, 0.0);
    point4 light_direction2(0.2,0.0, 0.0, 0.0);

    color4 light_ambient(0.5, 0.5, 0.5, 1.0);
    color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
    color4 light_specular(1.0, 1.0, 1.0, 1.0);

    color4 material_ambient(0.5, 0.5, 0.5, 1.0);
    color4 material_diffuse(1.0, 1.0, 1.0, 1.0);
    color4 material_specular(1.0, 1.0, 1.0, 1.0);
    float material_shininess = 50.0;

    glUniform4fv(glGetUniformLocation(program, "lights[0].ambient"), 1, light_ambient);
    glUniform4fv(glGetUniformLocation(program, "lights[0].diffuse"), 1, light_diffuse);
    glUniform4fv(glGetUniformLocation(program, "lights[0].specular"), 1, light_specular);
    glUniform4fv(glGetUniformLocation(program, "lights[0].direction"), 1, light_direction1);

    glUniform4fv(glGetUniformLocation(program, "lights[1].ambient"), 1, light_ambient);
    glUniform4fv(glGetUniformLocation(program, "lights[1].diffuse"), 1, light_diffuse);
    glUniform4fv(glGetUniformLocation(program, "lights[1].specular"), 1, light_specular);
    glUniform4fv(glGetUniformLocation(program, "lights[1].direction"), 1, light_direction2);

    glUniform4fv(glGetUniformLocation(program, "material.ambient"), 1, material_ambient);
    glUniform4fv(glGetUniformLocation(program, "material.diffuse"), 1, material_diffuse);
    glUniform4fv(glGetUniformLocation(program, "material.specular"), 1, material_specular);
    glUniform1f(glGetUniformLocation(program, "material.shininess"), material_shininess);
}


void init()
{
    //Sbox cube
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxvertices) + sizeof(textureskybox), &skyboxvertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxIndices) + sizeof(textureskybox), &skyboxIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // Create a vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //spaceship
    glGenBuffers(1, &vbo10);
    glBindBuffer(GL_ARRAY_BUFFER, vbo10);
    glBufferData(GL_ARRAY_BUFFER, spaceship.getInterleavedVertexSize(), spaceship.getInterleavedVertices(), GL_STATIC_DRAW);


    glGenBuffers(1, &ibo10);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo10);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, spaceship.getIndexSize(), spaceship.getIndices(), GL_STATIC_DRAW);
    //fuel
    glGenBuffers(1, &vbor);
    glBindBuffer(GL_ARRAY_BUFFER, vbor);
    glBufferData(GL_ARRAY_BUFFER, fuel.getInterleavedVertexSize(), fuel.getInterleavedVertices(), GL_STATIC_DRAW);


    glGenBuffers(1, &ibor);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibor);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, fuel.getIndexSize(), fuel.getIndices(), GL_STATIC_DRAW);

    //sun
    glGenBuffers(1, &vbo1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sun.getInterleavedVertexSize(), sun.getInterleavedVertices(), GL_STATIC_DRAW);

    
    glGenBuffers(1, &ibo1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sun.getIndexSize(), sun.getIndices(), GL_STATIC_DRAW);
    //mercury
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, mercury.getInterleavedVertexSize(), mercury.getInterleavedVertices(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &ibo2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mercury.getIndexSize(), mercury.getIndices(), GL_STATIC_DRAW);
    //venus
    glGenBuffers(1, &vbo3);
    glBindBuffer(GL_ARRAY_BUFFER, vbo3);
    glBufferData(GL_ARRAY_BUFFER, venus.getInterleavedVertexSize(), venus.getInterleavedVertices(), GL_STATIC_DRAW);
   

    glGenBuffers(1, &ibo3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, venus.getIndexSize(), venus.getIndices(), GL_STATIC_DRAW);
    //earth
    glGenBuffers(1, &vbo4);
    glBindBuffer(GL_ARRAY_BUFFER, vbo4);
    glBufferData(GL_ARRAY_BUFFER, earth.getInterleavedVertexSize(), earth.getInterleavedVertices(), GL_STATIC_DRAW);
    

    glGenBuffers(1, &ibo4);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo4);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, earth.getIndexSize(), earth.getIndices(), GL_STATIC_DRAW);
    //mars
    glGenBuffers(1, &vbo5);
    glBindBuffer(GL_ARRAY_BUFFER, vbo5);
    glBufferData(GL_ARRAY_BUFFER, mars.getInterleavedVertexSize(), mars.getInterleavedVertices(), GL_STATIC_DRAW);
    

    glGenBuffers(1, &ibo5);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo5);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mars.getIndexSize(), mars.getIndices(), GL_STATIC_DRAW);
    //jupiter
    glGenBuffers(1, &vbo6);
    glBindBuffer(GL_ARRAY_BUFFER, vbo6);
    glBufferData(GL_ARRAY_BUFFER, jupiter.getInterleavedVertexSize(), jupiter.getInterleavedVertices(), GL_STATIC_DRAW);
   

    glGenBuffers(1, &ibo6);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo6);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, jupiter.getIndexSize(), jupiter.getIndices(), GL_STATIC_DRAW);
    //saturn
    glGenBuffers(1, &vbo7);
    glBindBuffer(GL_ARRAY_BUFFER, vbo7);
    glBufferData(GL_ARRAY_BUFFER, saturn.getInterleavedVertexSize(), saturn.getInterleavedVertices(), GL_STATIC_DRAW);
    

    glGenBuffers(1, &ibo7);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo7);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, saturn.getIndexSize(), saturn.getIndices(), GL_STATIC_DRAW);
    //uranus
    glGenBuffers(1, &vbo8);
    glBindBuffer(GL_ARRAY_BUFFER, vbo8);
    glBufferData(GL_ARRAY_BUFFER, uranus.getInterleavedVertexSize(), uranus.getInterleavedVertices(), GL_STATIC_DRAW);


    glGenBuffers(1, &ibo8);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo8);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, uranus.getIndexSize(), uranus.getIndices(), GL_STATIC_DRAW);
    //neptune
    glGenBuffers(1, &vbo9);
    glBindBuffer(GL_ARRAY_BUFFER, vbo9);
    glBufferData(GL_ARRAY_BUFFER, neptune.getInterleavedVertexSize(), neptune.getInterleavedVertices(), GL_STATIC_DRAW);


    glGenBuffers(1, &ibo9);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo9);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, neptune.getIndexSize(), neptune.getIndices(), GL_STATIC_DRAW);
    // Load shaders and use the resulting shader program
    program = InitShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    // set up vertex arrays
    vPosition = glGetAttribLocation(program, "vertexPosition");
    glEnableVertexAttribArray(vPosition);
    //vPosition_static = glGetAttribLocation(program, "gl_positionstatic");
    glEnableVertexAttribArray(vPosition);
    vNormal = glGetAttribLocation(program, "vertexNormal");
    glEnableVertexAttribArray(vNormal);
    vTexture = glGetAttribLocation(program, "vertexTexture");
    glEnableVertexAttribArray(vTexture);
    modelUnifrom = glGetUniformLocation(program, "model");
    viewUniform = glGetUniformLocation(program, "view");
    projectionUniform = glGetUniformLocation(program, "projection");
    cameraUniform = glGetUniformLocation(program, "camera");
    
    for (int i = 0;i < 21;i++)
    {
        float random1 = -1 + (rand() % 1);
        float random2 = -1 + (rand() % 1);
        float random3 = -1 + (rand() % 1);
        randoms[i] = random1;
        randoms[i] = random2;
        randoms[i] = random3;
    }

    cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraDirection = glm::normalize(cameraPos - cameraTarget);
    cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    projection = glm::perspective(glm::radians(45.f), 512.0f / 512.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));

    initLight();
    initTexture();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);

}



void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Sky Box
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 2.0f));
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));

    glDepthMask(GL_FALSE);
    glUseProgram(0);
    
    

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureskybox);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, skyboxIndices);

    glTexCoordPointer(2, GL_FLOAT, 0, cubeTexCoords);

    glBindVertexArray(skyboxVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDepthMask(GL_TRUE);

    //spaceship
    view = glm::mat4(1.0f);
    glBindBuffer(GL_ARRAY_BUFFER, vbo10);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo10);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, spaceship.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, spaceship.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));
    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 2.0f));
    model = glm::translate(model, glm::vec3(0.0f, -0.03f, -0.07f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, spaceship.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));
    glUniform3fv(cameraUniform, 1, glm::value_ptr(cameraPos));
    
    //fuel
    glBindBuffer(GL_ARRAY_BUFFER, vbor);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibor);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, fuel.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, fuel.getInterleavedStride(), (void*)(3 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.1f, 0.04f, -0.5f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, fuel.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //fuel
    glBindBuffer(GL_ARRAY_BUFFER, vbor);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibor);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, fuel.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, fuel.getInterleavedStride(), (void*)(3 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.38f, 0.84f, -0.05f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, fuel.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //fuel
    glBindBuffer(GL_ARRAY_BUFFER, vbor);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibor);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, fuel.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, fuel.getInterleavedStride(), (void*)(3 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.5f, 0.6f, -0.05f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, fuel.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //fuel
    glBindBuffer(GL_ARRAY_BUFFER, vbor);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibor);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, fuel.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, fuel.getInterleavedStride(), (void*)(3 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.6f, 0.32f, -0.1f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, fuel.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //fuel
    glBindBuffer(GL_ARRAY_BUFFER, vbor);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibor);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, fuel.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, fuel.getInterleavedStride(), (void*)(3 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.2f, 0.1f, -0.3f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, fuel.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //sun
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sun.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, sun.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, sun.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    
    model = glm::rotate(model, Theta1, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, sun.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //mercury
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, mercury.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, mercury.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, mercury.getInterleavedStride(), (void*)(6 * sizeof(float)));

    model = glm::mat4(1.0f);
    model = glm::rotate(model, Theta2, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.23f, 0.0f, 0.0f));
    model = glm::rotate(model, Theta2, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, mercury.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //venus
    glBindBuffer(GL_ARRAY_BUFFER, vbo3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo3);
    glBindTexture(GL_TEXTURE_2D, texture3);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, venus.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, venus.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, venus.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, Theta3, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.27f, 0.0f, 0.0f));
    model = glm::rotate(model, Theta3, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, venus.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //earth
    glBindBuffer(GL_ARRAY_BUFFER, vbo4);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo4);
    glBindTexture(GL_TEXTURE_2D, texture4);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, earth.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, earth.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, earth.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, Theta4, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.33f, 0.0f, 0.0f));
    model = glm::rotate(model, Theta4, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, earth.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //mars
    glBindBuffer(GL_ARRAY_BUFFER, vbo5);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo5);
    glBindTexture(GL_TEXTURE_2D, texture5);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, mars.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, mars.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, mars.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, Theta5, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.38f, 0.0f, 0.0f));
    model = glm::rotate(model, Theta5, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, mars.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //jupiter
    glBindBuffer(GL_ARRAY_BUFFER, vbo6);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo6);
    glBindTexture(GL_TEXTURE_2D, texture6);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, jupiter.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, jupiter.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, jupiter.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, Theta6, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
    model = glm::rotate(model, Theta6, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, jupiter.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //saturn
    glBindBuffer(GL_ARRAY_BUFFER, vbo7);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo7);
    glBindTexture(GL_TEXTURE_2D, texture7);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, saturn.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, saturn.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, saturn.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, Theta7, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.65f, 0.0f, 0.0f));
    model = glm::rotate(model, Theta7, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, saturn.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //uranus
    glBindBuffer(GL_ARRAY_BUFFER, vbo8);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo8);
    glBindTexture(GL_TEXTURE_2D, texture8);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, uranus.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, uranus.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, uranus.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, Theta8, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.76f, 0.0f, 0.0f));
    model = glm::rotate(model, Theta8, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, mars.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    //neptune
    glBindBuffer(GL_ARRAY_BUFFER, vbo9);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo9);
    glBindTexture(GL_TEXTURE_2D, texture9);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, neptune.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, neptune.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, neptune.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, Theta9, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.9f, 0.0f, 0.0f));
    model = glm::rotate(model, Theta9, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, neptune.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    glutSwapBuffers();
}




void idle() {
    Theta1 += 0.001f;
    Theta2 += 0.00501f;
    Theta3 += 0.0012f;
    Theta4 += 0.0015f;
    Theta5 += 0.0018f;
    Theta6 += 0.0019f;
    Theta7 += 0.0018f;
    Theta8 += 0.0028f;
    Theta9 += 0.0040f;
    counter++;
    timer--;
    if (timer < 0)
    {
        std::cout << "GAME OVER!";
        std::cout << "...... final score is";
        std::cout << counter;
        exit(EXIT_SUCCESS);
    }
    
    if (Theta1 > 360.0)
    {
        Theta1 = 0;
    }
    if (Theta2 > 360.0)
    {
        Theta2 = 0;
    }
    if (Theta3 > 360.0)
    {
        Theta3 = 0;
    }
    if (Theta4 > 360.0)
    {
        Theta4 = 0;
    }
    if (Theta5 > 360.0)
    {
        Theta5 = 0;
    }
    if (Theta6 > 360.0)
    {
        Theta6 = 0;
    }
    if (Theta7 > 360.0)
    {
        Theta7 = 0;
    }
    if (Theta8 > 360.0)
    {
        Theta8 = 0;
    }
    if (Theta9 > 360.0)
    {
        Theta9 = 0;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 033:
        std::cout << "GAME OVER!";
        std::cout << "...... final score is";
        std::cout << counter;
        exit(EXIT_SUCCESS);
         
        break;
    case 'r':
        cameraPos += speed * cameraUp;
        break;
    case 'f':
        cameraPos -= speed * cameraUp;
        break;
    case 'w':
        cameraPos += speed * cameraFront;
        break;
    case 's':
        cameraPos -= speed * cameraFront;
        break;
    case 'a':
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
        
        break;
    case 'd':
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
        break;
    case 'q':
        yaw -= 5.0f;
        cameraDirection.x = glm::cos(glm::radians(yaw));
        cameraDirection.z = glm::sin(glm::radians(yaw));
        cameraFront = glm::normalize(cameraDirection);
        break;
    case 'e':
        yaw += 5.0f;
        cameraDirection.x = glm::cos(glm::radians(yaw));
        cameraDirection.z = glm::sin(glm::radians(yaw));
        cameraFront = glm::normalize(cameraDirection);
        break;
    }
}


void
mouse(int button, int state, int x, int y)
{

}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitContextVersion(3, 2);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Title");

    glewInit();

    init();

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();
    
    return 0;
}
