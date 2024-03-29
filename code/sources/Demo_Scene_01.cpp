#include <Demo_Scene_01.hpp>

#include <Game.hpp>
#include <Model.hpp>
#include <Entity.hpp>
#include <Cube.hpp>
#include <Skybox.hpp>
#include <Camera.hpp>
#include <Material_Loader.hpp>
#include <Framebuffer.hpp>

#include <Plane.hpp>
#include <Projected_Plane.hpp>

namespace prz
{
	Demo_Scene_01::Demo_Scene_01(Window& window) : 
		Scene
		(
			window,
			make_shared< Camera >(*this, "Active_Camera_For_Testing"),
			make_shared< Framebuffer >(*this, Game::assetsFolderPath() + "shaders/vertex.vert", Game::assetsFolderPath() + "shaders/framebuffer.frag", window.getSize().x, window.getSize().y),
			make_shared< Skybox >(Game::assetsFolderPath() + "textures/cube_maps/lake/goldrush_.tga", Game::assetsFolderPath() + "shaders/skybox.vert", Game::assetsFolderPath() + "shaders/skybox.frag")
		)
	{}

	void Demo_Scene_01::initialize()
	{
		// Create the scene entities

		PSPtr< Entity > head = create_entity("Head");
		head->add_model(Game::assetsFolderPath() + "models/obj/head.obj");
		head->transform().scale(0.2f, 0.2f, 0.2f);
		head->transform().translate_in_z(-1.f);

		PSPtr< Entity > cube = create_entity("Cube");
		PSPtr< Model >model(std::make_shared<Model >(1, "Model with a cube"));
		model->add_piece(std::make_shared< Cube >("cube_mesh"));
		cube->add_model(model);
		cube->transform().scale(PVec3(2.f));
		cube->transform().translate_in_z(-30.f);

		PSPtr< Entity > weapon = create_entity("Weapon");
		weapon->add_model(Game::assetsFolderPath() + "models/obj/m4mw3.obj");
		weapon->transform().translate_in_z(-4.f);
		weapon->transform().translate_in_x(100.f);
		weapon->set_parent(head);

		// Create the plane and the material for create the elevation

		PSPtr< Material > elevationMaterial = Material_Loader::instance().load_material
		(
			"Elevation_Material",
			Game::assetsFolderPath() + "shaders/elevation_shader.vert",
			Game::assetsFolderPath() + "shaders/transparency.frag",
			true
		);

		PSPtr< Texture > rockTexture = elevationMaterial->add_texture_2D
		(
			Game::assetsFolderPath() + "textures/2D/rock.jpg",
			"texture_color"
		);

		PSPtr< Texture > heightTexture = elevationMaterial->add_texture_2D
		(
			Game::assetsFolderPath() + "textures/2D/height_map.png",
			"height_map"
		);

		PSPtr< Entity > elevationPlane = create_entity("Elevation Plane");

		elevationPlane->add_model
		(	
			Game::assetsFolderPath() + "models/obj/plane.obj",
			elevationMaterial
		);

		elevationPlane->transform().translate_in_z(-1.f);
		elevationPlane->transform().translate_in_x(-20.f);
		elevationPlane->transform().scale(PVec3(10.f));

		// Create the frame buffer
	}

	void Demo_Scene_01::update(float deltaTime)
	{
		Scene::update(deltaTime);

		PSPtr < Entity > entity = get_entity("Weapon");
		entity->transform().rotate(0.f, 50.f * deltaTime, 0.f);

		PSPtr < Entity > entity1 = get_entity("Head");
		entity1->transform().rotate(0.f, 50.f * deltaTime, 50.f * deltaTime);
	}
}