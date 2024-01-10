#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    GLuint programID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    GLuint getProgramID();

    void setMat4(const std::string& name, const glm::mat4& value);
    void setVec3(const std::string& name, const glm::vec3& value);

private:
    void checkCompileErrors(GLuint shader, std::string type);
};

#endif // SHADER_H
