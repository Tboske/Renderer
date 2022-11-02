#include "Tribe.h"

#include "hierarchy/components/RenderComponent.h"
#include "hierarchy/components/TransformComponent.h"
#include "render/Renderer.h"
#include "GameTime.h"
#include "hierarchy/SceneManager.h"
#include "hierarchy/Scene.h"
#include "hierarchy/GameObject.h"

#include "render/Window.h"
#include "render/TextureManager.h"


Tribe::Tribe()
{
	spdlog::set_level(spdlog::level::debug);

	m_pWindow = std::make_unique<Window>("Test Window");
	m_pRenderer = std::make_unique<Renderer>(m_pWindow.get());
	m_pGameTime = std::make_unique<GameTime>();
	m_pSceneManager = std::make_unique<SceneManager>();
}

Tribe::~Tribe()
{
	m_pSceneManager.reset();
	m_pGameTime.reset();
	m_pRenderer.reset();
}

void Tribe::LoadGame() 
{
	const auto pScene = m_pSceneManager->AddScene("StartScene");

	const auto pGameObject = pScene->AddChild("NewObject");

	const auto pTrans = pGameObject->AddComponent<TransformComponent>(glm::vec3{50,30,2});
	pGameObject->AddComponent<RenderComponent>(pTrans, m_pRenderer.get());


	Locator<TextureManager>::Get()->LoadTexture("test.png");
	Locator<TextureManager>::Get()->LoadTexture("test2.png");
}

void Tribe::Run()
{
	Initialize();
	LoadGame();

	while (!m_pWindow->ShouldEnd())
	{
		m_pGameTime->Update();

		// update scene
		m_pSceneManager->Update();	
		
		// draw
		m_pSceneManager->Render();
		m_pRenderer->Draw();

		// sleep thread
		std::this_thread::sleep_for(std::chrono::duration<double>(m_pGameTime->GetSleepTime()));
	}
	Cleanup();
}

void Tribe::Initialize()
{
	Locator<TextureManager>::Set(new TextureManager("resources/textures/"));
}

void Tribe::Cleanup()
{
	SafeDelete(Locator<TextureManager>::Get());
}