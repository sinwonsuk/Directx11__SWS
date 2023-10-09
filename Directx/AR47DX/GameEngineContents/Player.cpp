#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "TownMap.h"
#include "Monster.h"
#include "ContentsEnum.h"

Player* Player::this_Player; 

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::AnimationCheck(const std::string_view& _AnimationName)
{
	player->ChangeAnimation(_AnimationName);
}

void Player::Start()
{
	
	this_Player = this;
	{
		// ������ ���� ������ �������.
		player = CreateComponent<GameEngineSpriteRenderer>(-1);
	
		//player->SetImageScale({ 100.0f, 100.0f });

		player->CreateAnimation("Start", "PlayStart", 0.15f, -1, -1, false);

		player->CreateAnimation("UpIdle", "UpIdle", 0.1f, -1, -1, true);
		player->CreateAnimation("LeftIdle", "LeftIdle", 0.1f, -1, -1, true);
		player->CreateAnimation("DownIdle", "DownIdle", 0.1f, -1, -1, true);
		player->CreateAnimation("RightIdle", "RightIdle", 0.1f, -1, -1, true);
	
		player->CreateAnimation("UpMove", "UpMove", 0.1f, -1, -1, true);
		player->CreateAnimation("LeftMove", "LeftMove", 0.1f, -1, -1, true);
		player->CreateAnimation("DownMove", "DownMove", 0.1f, -1, -1, true);
		player->CreateAnimation("RightMove", "RightMove", 0.1f, -1, -1, true);

		player->CreateAnimation("Roll_Down", "Roll_Down", 0.05f, -1, -1, true);
		player->CreateAnimation("Roll_Left", "Roll_Left", 0.05f, -1, -1, true);
		player->CreateAnimation("Roll_Right", "Roll_Right", 0.05f, -1, -1, true);
		player->CreateAnimation("Roll_Up", "Roll_Up", 0.05f, -1, -1, true);

		player->CreateAnimation("Spear_Down_Attack_01", "Spear_Down_Attack_01", 0.1f, -1, -1, false);
		player->CreateAnimation("Spear_Down_Attack_02", "Spear_Down_Attack_02", 0.1f, -1, -1, false);
		player->CreateAnimation("Spear_Down_Attack_03", "Spear_Down_Attack_03", 0.1f, -1, -1, false);

		player->CreateAnimation("Spear_Left_Attack_01", "Spear_Left_Attack_01", 0.1f, -1, -1, false);
		player->CreateAnimation("Spear_Left_Attack_02", "Spear_Left_Attack_02", 0.1f, -1, -1, false);
		player->CreateAnimation("Spear_Left_Attack_03", "Spear_Left_Attack_03", 0.1f, -1, -1, false);

		player->CreateAnimation("Spear_Right_Attack_01", "Spear_Right_Attack_01", 0.1f, -1, -1, false);
		player->CreateAnimation("Spear_Right_Attack_02", "Spear_Right_Attack_02", 0.1f, -1, -1, false);
		player->CreateAnimation("Spear_Right_Attack_03", "Spear_Right_Attack_03", 0.1f, -1, -1, false);

		player->CreateAnimation("Spear_Up_Attack_01", "Spear_Up_Attack_01", 0.1f, -1, -1, false);
		player->CreateAnimation("Spear_Up_Attack_02", "Spear_Up_Attack_02", 0.1f, -1, -1, false);
		player->CreateAnimation("Spear_Up_Attack_03", "Spear_Up_Attack_03", 0.1f, -1, -1, false);

		

		player->AutoSpriteSizeOn();
		player->SetAutoScaleRatio(2.0f);
		player->ChangeAnimation("Start");
		player->SetFrameEvent("Start", 34, std::bind(&Player::TestEvent, this, std::placeholders::_1));
		
	}

	
	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
		Col->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });

}

void Player::TestEvent(GameEngineRenderer* _Renderer)
{
	ChangeState(PlayerState::Start_Stop);
}





void Player::Update(float _Delta)
{
	
	//MainSpriteRenderer->AddImageScale(float4{-10.0f, 0.0f, 0.0f} *_Delta);

	// ���Ͱ� ���Ͷ� �浹�ϰ� ������?
	// �� �̷��� ��ġ

	TransformData date = Transform.GetConstTransformDataRef();

	Col->Collision(ContentsCollisionType::Door, { 300.0f, 0.0f, 0.0f }, [](std::vector<std::shared_ptr<GameEngineCollision>>& _Collision){});

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

	//GetLevel()->GetMainCamera()->Transform.SetLocalPosition(Transform.GetWorldPosition());
	float4 WorldMousePos = GetLevel()->GetMainCamera()->GetWorldMousePos2D();
	OutputDebugStringA(WorldMousePos.ToString("\n").c_str());



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


	UpdateState(_Delta);
}