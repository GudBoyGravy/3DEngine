#include "Engine.h"
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <sdl.h>
#include <iostream>

// vertices
const float vertices[] =
{
    // front
    -1.0f, -1.0f,  1.0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
     1.0f, -1.0f,  1.0, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     1.0f,  1.0f,  1.0, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f,  1.0, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    // back
    -1.0f, -1.0f, -1.0, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
     1.0f, -1.0f, -1.0, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
     1.0f,  1.0f, -1.0, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -1.0f,  1.0f, -1.0, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f
};



const GLuint indices[] =
{
    // front
    0, 1, 2,
    2, 3, 0,
    // right
    1, 5, 6,
    6, 2, 1,
    // back
    7, 6, 5,
    5, 4, 7,
    // left
    4, 0, 3,
    3, 7, 4,
    // bottom
    4, 5, 1,
    1, 0, 4,
    // top
    3, 2, 6,
    6, 7, 3
};

int main(int argc, char** argv)
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
>>>>>>> parent of 3e8d285 (Light and Materials)
=======
>>>>>>> parent of 3e8d285 (Light and Materials)
=======
>>>>>>> parent of 3e8d285 (Light and Materials)
    std::unique_ptr<nc::Engine> engine = std::make_unique<nc::Engine>();
    engine->Startup();
    engine->Get<nc::Renderer>()->Create("OpenGL", 800, 600);

    //create scene
    std::unique_ptr<nc::Scene> scene = std::make_unique<nc::Scene>();
    scene->engine = engine.get();

    nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
    nc::SetFilePath("../Resources");

    std::shared_ptr<nc::Program> program = engine->Get<nc::ResourceSystem>()->Get<nc::Program>("basic_program");
    std::shared_ptr<nc::Shader> vshader = engine->Get<nc::ResourceSystem>()->Get<nc::Shader>("Shaders/basic.vert", (void*)GL_VERTEX_SHADER);
    std::shared_ptr<nc::Shader> fshader = engine->Get<nc::ResourceSystem>()->Get<nc::Shader>("Shaders/basic.frag", (void*)GL_FRAGMENT_SHADER);

    program->AddShader(vshader);
    program->AddShader(fshader);
    program->Link();
    program->Use();

    //std::shared_ptr<nc::VertexIndexBuffer> vertexBuffer = engine.Get<nc::ResourceSystem>()->Get<nc::VertexIndexBuffer>("vertex_index_buffer");

    // vertex buffers
    std::shared_ptr<nc::VertexBuffer> vertexBuffer = engine->Get<nc::ResourceSystem>()->Get<nc::VertexBuffer>("cube_mesh");

    vertexBuffer->CreateVertexBuffer(sizeof(vertices), 8, (void*)vertices);
    vertexBuffer->CreateIndexBuffer(GL_UNSIGNED_INT, 36, (void*)indices);
    vertexBuffer->SetAttribute(0, 3, 8 * sizeof(float), 0);
    vertexBuffer->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));
    vertexBuffer->SetAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));


    //Texture
    {
        //auto texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Textures/rat.png");
        //texture->Bind();

        //texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("textures/spot.png");

        auto texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("textures/spot.png");
        texture->Bind();
    }

    //create Camera
    {
        auto actor = nc::ObjectFactory::Instance().Create<nc::Actor>("Actor");
        actor->name = "camera";
        actor->transform.position = glm::vec3{ 0, 0, 10 };

        {
            auto component = nc::ObjectFactory::Instance().Create<nc::CameraComponent>("CameraComponent");
            component->SetPerspective(45.0f, 800.0f / 600.0f, 0.01f, 100.0f);
            actor->AddComponent(std::move(component));
        }

        {
            auto component = nc::ObjectFactory::Instance().Create<nc::FreeCameraController>("FreeCameraController");
            component->speed = 3;
            component->sensitivity = 0.1f;
            actor->AddComponent(std::move(component));
        }

        scene->AddActor(std::move(actor));
    }

    // create cube
    {
        auto actor = nc::ObjectFactory::Instance().Create<nc::Actor>("Actor");
        actor->name = "cube";
        actor->transform.position = glm::vec3{ 0, 0, 0 };

        //auto component = nc::ObjectFactory::Instance().Create<nc::MeshComponent>("MeshComponent");
        //component->program = engine->Get<nc::ResourceSystem>()->Get<nc::Program>("basic_shader");
        //component->vertexBuffer = engine->Get<nc::ResourceSystem>()->Get<nc::VertexBuffer>("cube_mesh");

        auto component = nc::ObjectFactory::Instance().Create<nc::ModelComponent>("ModelComponent");
        component->program = engine->Get<nc::ResourceSystem>() -> Get<nc::Program>("basic_program");
        component->model = engine->Get<nc::ResourceSystem>() -> Get<nc::Model>("models/spot.obj");

        actor->AddComponent(std::move(component));
        scene->AddActor(std::move(actor));
    }

    glm::vec3 translate{ 0 };
    float angle = 0;


    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }
        SDL_PumpEvents();
            
        engine->Update();
        scene->Update(engine->time.deltaTime);

        //update actor
        auto actor = scene->FindActor("cube");
        if (actor != nullptr)
        {
            actor->transform.rotation.y += engine->time.deltaTime;
        }

        engine->Get<nc::Renderer>()->BeginFrame();

        scene->Draw(nullptr);

        engine->Get<nc::Renderer>()->EndFrame();

    }
    return 0;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
	// create engine
	std::unique_ptr<nc::Engine> engine = std::make_unique<nc::Engine>();
	engine->Startup();
	engine->Get<nc::Renderer>()->Create("OpenGL", 800, 600);

	nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	nc::SetFilePath("../resources");

	// create scene
	std::unique_ptr<nc::Scene> scene = std::make_unique<nc::Scene>();
	scene->engine = engine.get();

	// load scene
	rapidjson::Document document;
	bool success = nc::json::Load("scenes/main.scn", document);
	scene->Read(document);

	glm::vec3 translate{ 0.0f };
	float angle = 0;

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		}

		SDL_PumpEvents();
		engine->Update();
		scene->Update(engine->time.deltaTime);

		// update actor

		auto actor = scene->FindActor("model");
		if (actor != nullptr)
		{
			//actor->transform.position += direction * 5.0f * engine->time.deltaTime;
			actor->transform.rotation.y += engine->time.deltaTime;
		}

		engine->Get<nc::Renderer>()->BeginFrame();

		scene->Draw(nullptr);

		engine->Get<nc::Renderer>()->EndFrame();
	}

	return 0;
>>>>>>> Stashed changes
=======
>>>>>>> parent of 3e8d285 (Light and Materials)
=======
>>>>>>> parent of 3e8d285 (Light and Materials)
=======
>>>>>>> parent of 3e8d285 (Light and Materials)
}