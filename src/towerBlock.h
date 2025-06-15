#pragma once


class TowerBlock
{
public:
    static void Init() { mesh.Init(vertices, 180, 30, false); }
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
        shader.SetVector3fv("uObjectColor", glm::vec3(color));

        mesh.Render();
    }

    glm::vec3 getPosition() const { return pos; }
    glm::vec3 getScale() const { return scale; }
    glm::vec3 GetColor() const { return glm::vec3(color); }

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
     // positions          // normals
     // Back face (-Z)
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     // Front face (+Z)
     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     // Left face (-X)
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
     // Right face (+X)
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
      // Top face (+Y)
       0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,
       0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,
       0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f
};