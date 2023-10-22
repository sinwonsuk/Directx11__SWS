#include "PreCompile.h"
#include "BabySlime.h"
#include "Spear.h"
#include "Spear_Effect.h"
#include "Player.h"
BabySlime::BabySlime()
{


}

BabySlime::~BabySlime()
{


}



void BabySlime::Start()
{
	babySlime = CreateComponent<GameEngineSpriteRenderer>(100);

	

	babySlime->CreateAnimation("babyslime_walk", "babyslime_walk", 0.1f, -1, -1, true);

	babySlime->AutoSpriteSizeOn();
	babySlime->SetAutoScaleRatio(2.0f);
	babySlime->ChangeAnimation("babyslime_walk");

	
	{
		Monster_BaseBar = CreateComponent<GameEngineSpriteRenderer>(101);
		Monster_BaseBar->SetSprite("MonsterUI", 0);
		Monster_BaseBar->SetPivotType(PivotType::Left);
		Monster_BaseBar->Transform.AddLocalPosition({ -30.0f,60.0f });
		Monster_BaseBar->Off();
	}

	{
		Monster_HpBar = CreateComponent<GameEngineSpriteRenderer>(101);
		Monster_HpBar->SetSprite("MonsterUI", 1);
		Monster_HpBar->SetPivotType(PivotType::Left);
		Monster_HpBar->Transform.AddLocalPosition({ -30.0f,60.0f });
		Monster_HpBar->Off();
	}
	

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y });

	
	
	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::BabySlime);
		Col->Transform.SetLocalScale({ 15.0f,15.0f });
	}

	Event.Enter = [this](GameEngineCollision* Col, GameEngineCollision* col)
	{
		/*	GameEngineActor* Actor = col->GetActor();
			Spear* ptr = dynamic_cast<Spear*>(Actor);*/

		if (Weapon_Collision_Check == false)
		{
			std::shared_ptr<Spear_Effect> Object = GetLevel()->CreateActor<Spear_Effect>();
			Object->Transform.SetLocalPosition(Transform.GetWorldPosition());
			Monster_HpBar->Transform.AddLocalScale({ -0.5f,0.0f });
			Weapon_Collision_Check = true;
			Hp -= 10.0f;
		}
		


		Monster_BaseBar->On();
		Monster_HpBar->On();

		/*GameEngineActor* Actor = col->GetActor();
		Spear* ptr = dynamic_cast<Spear*>(Actor);
		ptr->Col->Off();*/
	};

	Event.Stay = [this](GameEngineCollision* Col, GameEngineCollision* col)
	{
	/*	Monster_BaseBar->On();
		Monster_HpBar->On();*/
		//Collision_Check = true;
	};


	Event.Exit = [this](GameEngineCollision* Col, GameEngineCollision* col)
	{
	/*	Monster_BaseBar->Off();
		Monster_HpBar->Off();*/
	};

}


void BabySlime::Update(float _Delta)
{
	Col->CollisionEvent(ContentsCollisionType::Spear, Event);


	if (Hp <= 0)
	{
		this->Off();
	}
	MonsterPushUpdate(_Delta);

	UpdateState(_Delta); 
}

void BabySlime::MonsterPushUpdate(float _Delta)
{

	if (Weapon_Collision_Check == true)
	{
		PushTime_Check += _Delta;
	}


	if (Weapon_Collision_Check == true && PushTime_Check <= 0.15)
	{


		if (Player::this_Player->GetPlayerStateValue() == PlayerState::Spear_Down_Attack_01)
		{
			Transform.AddLocalPosition({ float4::DOWN * PushSpeed * _Delta });
		}
		else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Spear_Down_Attack_02)
		{
			Transform.AddLocalPosition({ float4::DOWN * PushSpeed * _Delta });
		}
		else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Spear_Down_Attack_03)
		{
			Transform.AddLocalPosition({ float4::DOWN * PushSpeed * _Delta });
		}

		else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Spear_Left_Attack_01)
		{
			Transform.AddLocalPosition({ float4::LEFT * PushSpeed * _Delta });
		}
		else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Spear_Left_Attack_02)
		{
			Transform.AddLocalPosition({ float4::LEFT * PushSpeed * _Delta });
		}
		else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Spear_Left_Attack_03)
		{
			Transform.AddLocalPosition({ float4::LEFT * PushSpeed * _Delta });
		}


		else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Spear_Up_Attack_01)
		{
			Transform.AddLocalPosition({ float4::UP * PushSpeed * _Delta });
		}
		else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Spear_Up_Attack_02)
		{
			Transform.AddLocalPosition({ float4::UP * PushSpeed * _Delta });
		}
		else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Spear_Up_Attack_03)
		{
			Transform.AddLocalPosition({ float4::UP * PushSpeed * _Delta });
		}

		else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Spear_Right_Attack_01)
		{
			Transform.AddLocalPosition({ float4::RIGHT * PushSpeed * _Delta });
		}
		else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Spear_Right_Attack_02)
		{
			Transform.AddLocalPosition({ float4::RIGHT * PushSpeed * _Delta });
		}
		else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Spear_Right_Attack_03)
		{
			Transform.AddLocalPosition({ float4::RIGHT * PushSpeed * _Delta });
		}



	}

	if (PushTime_Check > 0.55)
	{
		PushTime_Check = 0;
		Weapon_Collision_Check = false;
	}

}

void BabySlime::AnimationCheck(const std::string_view& _AnimationName)
{
	babySlime->ChangeAnimation(_AnimationName);
}