#pragma once

class TowerBlock
{
public:
    static void Init() { mesh.Init(vertices, 108, 36, false); }
    static void Clear() { mesh.Clear(); }

    TowerBlock(const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& color)
        : pos(pos), scale(scale), color(color)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::scale(model, scale);
    }

    void Render(Shader& shader) const {
        shader.SetBool("useTexture", false);

        shader.SetMatrix4fv("uM", model);
        shader.SetVector4fv("uColor", color);

        mesh.Render();
    }

    glm::vec3 getPosition() const { return pos; }
    glm::vec3 getScale() const { return scale; }

private:
    glm::vec3 pos;
    glm::vec3 scale;
    glm::vec4 color;
    glm::mat4 model;

    static Mesh mesh;
    static float vertices[];
};

Mesh TowerBlock::mesh;
float TowerBlock::vertices[] = {
    // Back face (-Z) 
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     // Front face (+Z) 
     -0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,
     -0.5f, -0.5f,  0.5f,
     // Left face (-X) 
     -0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,
     -0.5f, -0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,
     // Right face (+X) 
      0.5f,  0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f,  0.5f,  0.5f,
      // Top face (+Y) 
       0.5f,  0.5f,  0.5f,
       0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,
       // Bottom face (-Y) 
       -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
       -0.5f, -0.5f,  0.5f,
       -0.5f, -0.5f, -0.5f
};