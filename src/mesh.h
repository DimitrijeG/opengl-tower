#pragma once


class Mesh
{
public:
    Mesh() { VAO = 0; VBO = 0; vertexCount = 0; }

    void Init(const float* vertices, unsigned int numOfValues, unsigned int vertexCount, bool hasTexCoords) {
        this->vertexCount = vertexCount;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numOfValues, vertices, GL_STATIC_DRAW);

        if (hasTexCoords)
        {
            unsigned int stride = 8 * sizeof(float);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(2);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
        else
        {
            unsigned int stride = 6 * sizeof(float);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(2);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Render() const {
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