#pragma once

// (Your includes for GL/glew.h, etc.)

class Mesh
{
public:
    Mesh() { VAO = 0; VBO = 0; vertexCount = 0; }

    // --- THIS IS THE ONLY FUNCTION THAT HAS CHANGED ---
    void Init(const float* vertices, unsigned int numOfValues, unsigned int vertexCount, bool hasTexCoords) {
        this->vertexCount = vertexCount;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numOfValues, vertices, GL_STATIC_DRAW);

        if (hasTexCoords)
        {
            // This is for your SURFACE object
            // A vertex consists of: 3 position floats + 3 normal floats + 2 texCoord floats = 8 floats total
            unsigned int stride = 8 * sizeof(float);

            // Attribute Location 0: Vertex Position (3 floats)
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
            glEnableVertexAttribArray(0);

            // Attribute Location 2: Vertex Normal (3 floats)
            // Starts after the 3 position floats
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(2);

            // Attribute Location 1: Texture Coordinates (2 floats)
            // Starts after the 3 position and 3 normal floats
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
        else
        {
            // This is for your TOWERBLOCK object
            // A vertex consists of: 3 position floats + 3 normal floats = 6 floats total
            unsigned int stride = 6 * sizeof(float);

            // Attribute Location 0: Vertex Position (3 floats)
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
            glEnableVertexAttribArray(0);

            // Attribute Location 2: Vertex Normal (3 floats)
            // Starts after the 3 position floats
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(2);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Render() {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glBindVertexArray(0);
    }

    void Clear() {
        if (VBO != 0) { glDeleteBuffers(1, &VBO); VBO = 0; }
        if (VAO != 0) { glDeleteVertexArrays(1, &VAO); VAO = 0; }
        vertexCount = 0;
    }

    ~Mesh() { Clear(); }
private:
    GLuint VAO, VBO;
    GLsizei vertexCount;
};