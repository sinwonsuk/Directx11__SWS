#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "PlayMap.h"
#include "Monster.h"
#include "ContentsEnum.h"

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::Start()
{
	{
		// ������ ���� ������ �������.
		TestCollision = CreateComponent<GameEngineComponent>(30);
		TestCollision->Transform.SetLocalScale({ 30, 30, 1 });

		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(30);
		MainSpriteRenderer->SetSprite("HoHoYee_AttackABC2");
		MainSpriteRenderer->SetImageScale({ 100.0f, 100.0f });
		// MainSpriteRenderer->Transform.SetLocalScale({30, 30, 1.0f});

		/*MainSpriteRenderer->CreateAnimation("Run", "HoHoYee_AttackABC2", 0.05f, -1, -1, true);
		MainSpriteRenderer->ChangeAnimation("Run");
		MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
		MainSpriteRenderer->Transform.SetLocalPosition({ 100.0f, 0.0f, 0.0f });

		MainSpriteRenderer->SetEndEvent("Run", std::bind(&Player::TestEvent, this, std::placeholders::_1));*/

		// MainSpriteRenderer->Transform.SetLocalScale({5, 5});
		// MainSpriteRenderer->AutoSpriteSizeOn();
		// MainSpriteRenderer->SetAutoScaleRatio(2.0f);
		// MainSpriteRenderer->Transform.SetLocalScale({-100.0f, 100.0f, 1.0f});
	}

	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(30);
		MainSpriteRenderer->SetSprite("HoHoYee_AttackABC2");
		MainSpriteRenderer->Transform.SetLocalPosition({ 0, 70, 1.0f });
		MainSpriteRenderer->SetImageScale({ 100.0f, 20.0f });
		MainSpriteRenderer->SetPivotType(PivotType::Left);
	}

	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
		Col->Transform.SetLocalScale({ -100.0f, 100.0f, 1.0f });
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

}

void Player::TestEvent(GameEngineRenderer* _Renderer)
{
	int a = 0;
}

void Player::Update(float _Delta)
{
	MainSpriteRenderer->AddImageScale(float4{-10.0f, 0.0f, 0.0f} *_Delta);

	// ���Ͱ� ���Ͷ� �浹�ϰ� ������?
	// �� �̷��� ��ġ

	EventParameter Event;

	Event.Enter = [](GameEngineCollision* Col)
		{
			Col->GetActor()->Death();
			int a = 0;
		};

	Event.Stay = [](GameEngineCollision* Col)
		{
			int a = 0;
		};


	Event.Exit = [](GameEngineCollision* Col)
		{
			// 

			int a = 0;
		};

	Col->CollisionEvent(ContentsCollisionType::Monster, Event);

	//Col->Collision(ContentsCollisionType::Monster, {100.0f, 0.0f, 0.0f}, [](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)
	//	{
	//		for (size_t i = 0; i < _Collision.size(); i++)
	//		{
	//			_Collision[i]->GetActor()->Death();
	//		}
	//	});

	//if (xxxx ��Ȳ�� �Ǹ�)
	//{
	//	MainSpriteRenderer->Death();
	//	MainSpriteRenderer = nullptr;
	//}

	// �浹�߳� ���߳ĸ� ����

	//std::list<std::shared_ptr<Monster>> MonsterList = 
	//	GetLevel()->GetObjectGroupConvert<Monster>(ContentsObjectType::Monster);

	//for (std::shared_ptr<Monster> MonsterPtr : MonsterList)
	//{
	//	// �������� �ϴ� ���� => ���ͷε� �Ҽ��ִµ�
	//	// ���� ���ʹ� ��ġ�� ������ ����ִ� �뵵�� ���˴ϴ�.
	//	// MainSpriteRenderer->Transform.Collision(MonsterPtr->Renderer->Transform);

	//	GameEngineTransform& Left = TestCollision->Transform;
	//	GameEngineTransform& Right = MonsterPtr->Renderer->Transform;
	//	Right.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });

	//	// �ݸ��� �Ķ���͸� ����� ������. 
	//	if (GameEngineTransform::Collision({ Left , Right, ColType::OBBBOX2D }))
	//	{
	//		MonsterPtr->Death();
	//		int a = 0;
	//		// �浹�ߴ�.
	//	}
	//}


	float Speed = 100.0f;

	if (GameEngineInput::IsDown('A'))
	{
		MainSpriteRenderer->AnimationPauseSwitch();
	}


	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W'))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}

	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}

	//GameEngineColor Color = PlayMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	//if (GameEngineColor::RED != Color)
	//{
	//	GrivityForce.Y -= _Delta * 100.0f;
	//	Transform.AddLocalPosition(GrivityForce * _Delta);
	//}
	//else 
	//{
	//	GrivityForce = 0.0f;
	//}
	// ���� ���ٰ��ϰ� �ʹٸ� while������ �÷��ּ���.


	// float4 Color = GetColor(Transform.GetWorldPosition());
}