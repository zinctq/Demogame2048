#include "GSPlay.h"
#include<iostream>
#include<conio.h>

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "SpriteAnimation.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
static int score;

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg2");



	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 4, 55);
	button->SetSize(201, 93);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	//pause button
	texture = ResourceManagers::GetInstance()->GetTexture("pause");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 4 * 3, 55);
	button->SetSize(201, 93);
	button->SetOnClick([]() {
		score++;
		});
	m_listButton.push_back(button);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "Score: " + std::to_string(score) , TEXT_COLOR::WHILE, 1.8);
	m_score->Set2DPosition(Vector2(5, 145));

	

	// Animation
	/*shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("coin1");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	obj->Set2DPosition(240, 400);
	obj->SetSize(52, 52);
	m_listSpriteAnimations.push_back(obj);*/

	
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{

	
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlay::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto obj : m_listSpriteAnimations)
	{
		obj->Update(deltaTime);
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	m_score->Update(deltaTime);
}

void GSPlay::Draw()
{
	m_BackGround->Draw();

	for (auto obj : m_listSpriteAnimations)
	{
		obj->Draw();
	}

	for (auto it : m_listButton)
	{
		it->Draw();
	}

	m_score->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}