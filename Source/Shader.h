#pragma once

#include <string>
#include <glad/glad.h>

class Shader {
public:
	Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	Shader(const std::string& computeSource);
	~Shader();

	void setUniform1f(const std::string& name, const float value) const;
	void setUniform1i(const std::string& name, const int value) const;
	void setUniformVec3f(const std::string& name, float v0, float v1, float v2) const;

	void use();

	GLuint getProgramId() const { return m_program; }

private:
	GLuint m_program = 0;
	void checkCompileErrors(unsigned int shader, const std::string& type);
};