#include "terrain.h"

#include <math.h>
#include "gl/shaders/ShaderAttribLocations.h"
#include <iostream>
Terrain::Terrain() : m_numRows(100), m_numCols(m_numRows)
{
}


/**
 * Returns a pseudo-random value between -1.0 and 1.0 for the given row and column.
 */
float Terrain::randValue(int row, int col) {
    return -1.0 + 2.0 * glm::fract(sin(row * 127.1f + col * 311.7f) * 43758.5453123f);
}


/**
 * Returns the object-space position for the terrain vertex at the given row and column.
 */
glm::vec3 Terrain::getPosition(int row, int col) {
    glm::vec3 position;
    position.x = 10 * row/m_numRows - 5;
    position.y = 0;
    position.z = 10 * col/m_numCols - 5;

    // TODO: Adjust position.y using value noise.

    position.y = getHeight(20.f,2.f,row,col) + getHeight(10.f,0.1f,row,col) + getHeight(5.f,0.5f,row,col);
    return position;
}

float Terrain::getHeight(float freq, float amp, int row, int col){
    int newRow = floor(row/freq);
    int newCol = floor(col/freq);

    float heightA = randValue(newRow, newCol);
    float heightB = randValue(newRow, newCol + 1);
    float heightC = randValue(newRow + 1, newCol);
    float heightD = randValue(newRow + 1, newCol + 1);

    float xDist = glm::fract(col/freq);
    float yDist = glm::fract(row/freq);

    float topMix = glm::mix(heightA,heightB,xDist*xDist*(3-2*xDist));
    float botMix = glm::mix(heightC,heightD,xDist*xDist*(3-2*xDist));
    float combMix = glm::mix(topMix,botMix, yDist*yDist*(3-2*yDist));

    return combMix * amp;
}




/**
 * Returns the normal vector for the terrain vertex at the given row and column.
 */
glm::vec3 Terrain::getNormal(int row, int col) {
    // TODO: Compute the normal at the given row and column using the positions of the
    //       neighboring vertices.
    glm::vec3 p = getPosition(row, col);



    glm::vec3 p0 = getPosition(row, col + 1);
    glm::vec3 p1 = getPosition(row - 1, col + 1);
    glm::vec3 p2 = getPosition(row - 1, col);
    glm::vec3 p3 = getPosition(row - 1, col - 1);
    glm::vec3 p4 = getPosition(row, col - 1);
    glm::vec3 p5 = getPosition(row + 1, col - 1);
    glm::vec3 p6 = getPosition(row + 1, col);
    glm::vec3 p7 = getPosition(row + 1, col + 1);


    glm::vec3 n0 = glm::normalize(glm::cross((p1 - p), (p0 - p)));
    glm::vec3 n1 = glm::normalize(glm::cross((p2 - p), (p1 - p)));
    glm::vec3 n2 = glm::normalize(glm::cross((p3 - p), (p2 - p)));
    glm::vec3 n3 = glm::normalize(glm::cross((p4 - p), (p3 - p)));
    glm::vec3 n4 = glm::normalize(glm::cross((p5 - p), (p4 - p)));
    glm::vec3 n5 = glm::normalize(glm::cross((p6 - p), (p5 - p)));
    glm::vec3 n6 = glm::normalize(glm::cross((p7 - p), (p6 - p)));
    glm::vec3 n7 = glm::normalize(glm::cross((p0 - p), (p7 - p)));

    glm::vec3 average = glm::normalize((n0 + n1 + n2 + n3 + n4 + n5 + n6 + n7)/8.f);

    return average;
}


/**
 * Initializes the terrain by storing positions and normals in a vertex buffer.
 */
void Terrain::init() {
    // TODO: Change from GL_LINE to GL_FILL in order to render full triangles instead of wireframe.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    // Initializes a grid of vertices using triangle strips.
    int numVertices = (m_numRows - 1) * (2 * m_numCols + 2);
    std::vector<glm::vec3> data(2 * numVertices);
    int index = 0;
    for (int row = 0; row < m_numRows - 1; row++) {
        for (int col = m_numCols - 1; col >= 0; col--) {
            data[index++] = getPosition(row, col);
            data[index++] = getNormal  (row, col);
            data[index++] = getPosition(row + 1, col);
            data[index++] = getNormal  (row + 1, col);
        }
        data[index++] = getPosition(row + 1, 0);
        data[index++] = getNormal  (row + 1, 0);
        data[index++] = getPosition(row + 1, m_numCols - 1);
        data[index++] = getNormal  (row + 1, m_numCols - 1);
    }

    // Initialize OpenGLShape.
    m_shape = std::make_unique<OpenGLShape>();
    m_shape->setVertexData(&data[0][0], data.size() * 3, VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, numVertices);
    m_shape->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_shape->setAttribute(ShaderAttrib::NORMAL, 3, sizeof(glm::vec3), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_shape->buildVAO();
}


/**
 * Draws the terrain.
 */
void Terrain::draw()
{
    m_shape->draw();
}

/*
Questions from lab
What is a noise function and how do we use it to generate terrains?
    function that generates a series of pseudo-random values, used for height value.

What is the difference between bilinear interpolation and bicubic interpolation, and why are we using bicubic interpolation?
    Bicubic interpolation uses cubic functions instead of lines to transition from one value to the next.
    smoother transition between points, and x at 0 an 1 remain the same

What is an octave? Explain what the terrain of an octave with high frequency and high amplitude would look like.
    noise levels. extreme up and downs really fast.
*/
