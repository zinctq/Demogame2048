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
int score;
extern bool clickstat;
int keypressed;
int value[4][4];

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	clickstat = 0;
	score = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			value[i][j] = 0;
	int a = rand() % 4;
	int b = rand() % 4;
	value[a][b] = 2;
	a = rand() % 4;
	b = rand() % 4;
	while (value[a][b] == 2)
	{
		a = rand() % 4;
		b = rand() % 4;
	}
	value[a][b] = 2;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bgPlay");


	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	for (int i=0; i<4;i++)
		for (int j = 0; j < 4; j++)
		{
			texture = ResourceManagers::GetInstance()->GetTexture("titleBg");
			m_tile[i][j] = std::make_shared<Sprite2D>(model, shader, texture);
			m_tile[i][j]->Set2DPosition(90 + 100 * i, 250 + 100 * j);
			m_tile[i][j]->SetSize(95, 95);
		}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (value[i][j] == 0) {
				texture = ResourceManagers::GetInstance()->GetTexture("titleBg");
				m_value[i][j] = std::make_shared<Sprite2D>(model, shader, texture);
				m_value[i][j]->Set2DPosition(90 + 100 * i, 250 + 100 * j);
				m_value[i][j]->SetSize(95, 95);
			}
			else if (value[i][j] == 2) {
				texture = ResourceManagers::GetInstance()->GetTexture("title2");
				m_value[i][j] = std::make_shared<Sprite2D>(model, shader, texture);
				m_value[i][j]->Set2DPosition(90 + 100 * i, 250 + 100 * j);
				m_value[i][j]->SetSize(95, 95);
			}
		}

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 4, 55);
	button->SetSize(201, 93);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	//pause button
	texture = ResourceManagers::GetInstance()->GetTexture("pause");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 4 * 3, 55);
	button->SetSize(201, 93);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Pause);
		});
	m_listButton.push_back(button);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "Score: " + std::to_string(score) , TEXT_COLOR::WHILE, 1.8);
	m_score->Set2DPosition(Vector2(5, 145));

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font2 = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_key = std::make_shared< Text>(shader, font2, "Key pressed: None", TEXT_COLOR::WHILE, 1.8);
	m_key->Set2DPosition(Vector2(5, 245));



	

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
	if (!clickstat) clickstat = 1;
	else {
		if (key == 40) {


		}
		
		clickstat = 0;
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (!clickstat) clickstat = 1;
	else {
		for (auto it : m_listButton)
		{
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle()) break;
		}
		clickstat = 0;
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

	m_score->UpdateText(deltaTime, "Score: " + std::to_string(score));
	m_key->UpdateText(deltaTime, "Key pressed: " + std::to_string(keypressed));
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

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			m_tile[i][j]->Draw();
			m_value[i][j]->Draw();
		}

	m_score->Draw();
	//m_key->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}