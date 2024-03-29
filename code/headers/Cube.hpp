/**
 * @file Cube.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief Class that store the information of a cube
 * @version 0.1
 * @date 30-04-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_CUBE_MESH_H_
#define OPENGL_SCENE_CUBE_MESH_H_

#include <Mesh.hpp>

#include <Declarations.hpp>

namespace prz
{
	
	/**
	 * @brief Class that store the information of a cube
	 * 
	 */
	class Cube : public Mesh
	{
	public:	

		/**
		 * @brief Construct a new Cube
		 * 
		 * @param name 
		 */
		Cube(const PString& name = "undefined");

	private:

		static const PBuffer< GLfloat > coordinates_;
		static const PBuffer< GLfloat > normals_;
		static const PBuffer< GLfloat > textureUVs_;
		static const PBuffer< GLuint > indices_;
	};

} // !namespace prz 

#endif // !OPENGL_SCENE_CUBE_MESH_H_
