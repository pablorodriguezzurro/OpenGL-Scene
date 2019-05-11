/**
 * @file ShaderProgram.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 30-04-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_SHADER_PROGRAM_H_
#define OPENGL_SCENE_SHADER_PROGRAM_H_

#include "Shader.hpp"

#include "Declarations.hpp"

namespace prz
{
	
	class Shader_Program
	{
	private:

		typedef std::map< PString, GLint > Uniform_Map;

	public:

		static const Shader_Program* activeShaderProgram()
		{
			return activeShaderProgram_;
		}

		static void disable()
		{
			glUseProgram(0);
		}

	public:

		Shader_Program()
		{
			instanceID_ = instanceCount_++;
			programObjID_ = glCreateProgram();
			islinkSuccessful_ = false;

			assert(programObjID_ != 0);
		}

		~Shader_Program()
		{
			glDeleteProgram(programObjID_);

			programObjID_ = 0;
		}

	private:

		Shader_Program(const Shader_Program&)
		{
		}

	public:

		unsigned id() const
		{
			return instanceID_;
		}

		bool is_usable() const
		{
			return (islinkSuccessful_);
		}

	public:

		void attach(const Shader & shader)
		{
			glAttachShader(programObjID_, shader);
		}

		void detach(const Shader & shader)
		{
			glDetachShader(programObjID_, shader);
		}

	public:

		bool link();

		void use() const
		{
			assert(is_usable());

			if (this != activeShaderProgram_)
			{
				glUseProgram(programObjID_);

				activeShaderProgram_ = this;
			}
		}

	public:

		GLint get_uniform_id(const char* id) const
		{
			assert(is_usable());

			GLint   uniformID = glGetUniformLocation(programObjID_, id);

			assert(uniformID != -1);

			return (uniformID);
		}

		void set_uniform_value(GLint uniform_id, const GLint & value) const { glUniform1i(uniform_id, value); }
		void set_uniform_value(GLint uniform_id, const GLuint & value) const { glUniform1ui(uniform_id, value); }
		void set_uniform_value(GLint uniform_id, const float& value) const { glUniform1f(uniform_id, value); }
		void set_uniform_value(GLint uniform_id, const float(&vector)[2]) const { glUniform2f(uniform_id, vector[0], vector[1]); }
		void set_uniform_value(GLint uniform_id, const float(&vector)[3]) const { glUniform3f(uniform_id, vector[0], vector[1], vector[2]); }
		void set_uniform_value(GLint uniform_id, const float(&vector)[4]) const { glUniform4f(uniform_id, vector[0], vector[1], vector[2], vector[3]); }
		void set_uniform_value(GLint uniform_id, const PVec2 & vector) const { glUniform2f(uniform_id, vector[0], vector[1]); }
		void set_uniform_value(GLint uniform_id, const PVec3& vector) const { glUniform3f(uniform_id, vector[0], vector[1], vector[2]); }
		void set_uniform_value(GLint uniform_id, const PVec4& vector) const { glUniform4f(uniform_id, vector[0], vector[1], vector[2], vector[3]); }
		void set_uniform_value(GLint uniform_id, const PMat2 & matrix) const { glUniformMatrix2fv(uniform_id, 1, GL_FALSE, glm::value_ptr(matrix)); }
		void set_uniform_value(GLint uniform_id, const PMat3 & matrix) const { glUniformMatrix3fv(uniform_id, 1, GL_FALSE, glm::value_ptr(matrix)); }
		void set_uniform_value(GLint uniform_id, const PMat4 & matrix) const { glUniformMatrix4fv(uniform_id, 1, GL_FALSE, glm::value_ptr(matrix)); }

	public:

		GLint get_vertex_attribute_id(const char* id) const
		{
			assert(is_usable());

			GLint   attribute_id = glGetAttribLocation(programObjID_, id);

			assert(attribute_id != -1);

			return (attribute_id);
		}

		void set_vertex_attribute(GLint attribute_id, const float& value) { glVertexAttrib1f(attribute_id, value); }
		void set_vertex_attribute(GLint attribute_id, const PVec2& vector) { glVertexAttrib2fv(attribute_id, glm::value_ptr(vector)); }
		void set_vertex_attribute(GLint attribute_id, const PVec3& vector) { glVertexAttrib3fv(attribute_id, glm::value_ptr(vector)); }
		void set_vertex_attribute(GLint attribute_id, const PVec4& vector) { glVertexAttrib4fv(attribute_id, glm::value_ptr(vector)); }

	public:

		const PString& log() const
		{
			return (logStr);
		}

	private:

		unsigned    instanceID_;
		GLuint      programObjID_;
		bool        islinkSuccessful_;
		PString logStr;

	private:

		static const Shader_Program* activeShaderProgram_;
		static unsigned int instanceCount_;

	};

} // !namespace prz 

#endif // !OPENGL_SCENE_SHADER_PROGRAM_H_

