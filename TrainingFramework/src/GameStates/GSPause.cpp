#include "GSPause.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPause::GSPause()
{

}


GSPause::~GSPause()
{
}



void GSPause::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//resume button
	texture = ResourceManagers::GetInstance()->GetTexture("resume");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 200);
	button->SetSize(201, 93);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 350);
	button->SetSize(201, 93);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName = std::make_shared< Text>(shader, font, "Pause menu", TEXT_COLOR::GREEN, 1.0);
	m_Text_gameName->Set2DPosition(Vector2(screenWidth / 2 - 80, 120));
}

void GSPause::Exit()
{
}


void GSPause::Pause()
{

}

void GSPause::Resume()
{

}


void GSPause::HandleEvents()
{

}

void GSPause::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPause::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPause::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSPause::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
}

