#include "Tribe.h"

#include "hierarchy/SceneManager.h"
#include "hierarchy/Scene.h"
#include "hierarchy/GameObject.h"

#include "hierarchy/components/RenderComponent.h"
#include "hierarchy/components/TransformComponent.h"

#include "core/GameTime.h"
#include "core/InputManager.h"
#include "render/Renderer.h"
#include "render/Window.h"
#include "render/TextureManager.h"


Tribe::Tribe()
{
	spdlog::set_level(spdlog::level::debug);

	m_pWindow = std::make_unique<Window>("Test Window");
	m_pRenderer = std::make_unique<Renderer>(m_pWindow->GetWindow());
	InputManager::Init(m_pWindow->GetWindow());
	m_pGameTime = std::make_unique<GameTime>();
	m_pSceneManager = std::make_unique<SceneManager>();


	Locator<TextureManager>::Set(new TextureManager("resources/textures/"));
}

Tribe::~Tribe()
{
	SafeDelete(Locator<TextureManager>::Get());


	m_pSceneManager.reset();
	m_pGameTime.reset();
	m_pRenderer.reset();
	m_pWindow.reset();
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
	LoadGame();

	while (!m_pWindow->ShouldEnd())
	{
		// time
		m_pGameTime->Update();

		// update scene
		m_pSceneManager->Update();	
		
		// draw
		m_pSceneManager->Render();
		m_pRenderer->Draw();

		// sleep thread
		m_pWindow->PollWindowEvents();
		std::this_thread::sleep_for(std::chrono::duration<double>(m_pGameTime->GetSleepTime()));
	}
}