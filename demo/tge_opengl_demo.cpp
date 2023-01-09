#include "glad/glad.h"
#include "tge/tge.hpp"
#include "tge/window.hpp"
#include "hdk/profile.hpp"

int main()
{
	tge::initialise();
	{
		tge::window wnd
		{{
			.title = "Tangle Window Demo",
			.window_flags = tge::window_flag::opengl | tge::window_flag::transparent
		}};
		bool ret = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(tge::get_opengl_proc_address));
		hdk::assert(ret);

		/*OGL boilerplate begin*/
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		const GLchar* vtx_src = R"-(
			#version 450 core
			void main()
			{
				const vec3 verts[3] = vec3[](
					vec3(-0.5, -0.5, 0.0), vec3(0.5, -0.5, 0.0), vec3(0.0f, 0.5, 0.0)
				);
				gl_Position = vec4(verts[gl_VertexID], 1.0);
			}
		)-";
		const GLchar* frg_src = R"-(
			#version 450 core
			layout(location = 0) out vec4 frag_colour;
			void main()
			{
				frag_colour = vec4(1.0, 0.0, 0.0, 1.0);
			}
		)-";

		GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &vtx_src, nullptr);
		glCompileShader(vertex_shader);
		int success_v;
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success_v);
		hdk::assert(success_v, "Failed to compile vertex shader");


		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &frg_src, nullptr);
		glCompileShader(fragment_shader);
		int success_f;
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success_f);
		hdk::assert(success_f, "Failed to compile fragment shader");

		GLuint program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);
		int success_p;
		glGetProgramiv(program, GL_LINK_STATUS, &success_p);
		hdk::assert(success_p, "Failed to link shader program");
		glGetProgramiv(program, GL_VALIDATE_STATUS, &success_p);
		hdk::assert(success_p, "Failed to validate shader program");

		glClearColor(0.0, 0.0, 1.0, 0.0);

		while(!wnd.is_close_requested())
		{
			HDK_FRAME_BEGIN;
			glClear(GL_COLOR_BUFFER_BIT);
			glViewport(0, 0, wnd.get_dimensions()[0], wnd.get_dimensions()[1]);
			glUseProgram(program);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			wnd.update();
			HDK_FRAME_END;
		}

		glDeleteVertexArrays(1, &vao);
	}
	tge::terminate();
}
