#include "PreCompile.h"
#include "Player.h"
#include "MiniBoss.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "Spear_Effect.h"
#include "Inventory.h"
#include "Items.h"
MiniBoss::MiniBoss()
{

}

MiniBoss::~MiniBoss()
{

}


void MiniBoss::Start()
{

	Transform.AddLocalPosition({ 0.0f,60.0f });
	Mini_Boss = CreateComponent<GameEngineSpriteRenderer>(130);
	Mini_Boss->CreateAnimation("Mini_Boss_Attack_Down", "Mini_Boss_Attack_Down", 0.1f, -1, -1, false);
	Mini_Boss->CreateAnimation("Mini_Boss_Move_Down", "Mini_Boss_Move_Down", 0.1f, -1, -1, true);
	Mini_Boss->CreateAnimation("Mini_Boss_Attack_Left", "Mini_Boss_Attack_Left", 0.1f, -1, -1, false);
	Mini_Boss->CreateAnimation("Mini_Boss_Move_Left", "Mini_Boss_Move_Left", 0.1f, -1, -1, true);
	Mini_Boss->CreateAnimation("Mini_Boss_Attack_Right", "Mini_Boss_Attack_Right", 0.1f, -1, -1, false);
	Mini_Boss->CreateAnimation("Mini_Boss_Move_Right", "Mini_Boss_Move_Right", 0.1f, -1, -1, true);
	Mini_Boss->CreateAnimation("Mini_Boss_Attack_Up", "Mini_Boss_Attack_Up", 0.1f, -1, -1, false);
	Mini_Boss->CreateAnimation("Mini_Boss_Move_Up", "Mini_Boss_Move_Up", 0.1f, -1, -1, true);

	{
		Monster_BaseBar = CreateComponent<GameEngineSpriteRenderer>(99);
		Monster_BaseBar->SetSprite("MonsterUI", 0);
		Monster_BaseBar->SetPivotType(PivotType::Left);
		Monster_BaseBar->Transform.AddLocalPosition({ -30.0f,120.0f });
		Monster_BaseBar->Off(); 
	}

	{
		Monster_HpBar = CreateComponent<GameEngineSpriteRenderer>(99);
		Monster_HpBar->SetSprite("MonsterUI", 1);
		Monster_HpBar->SetPivotType(PivotType::Left);
		Monster_HpBar->Transform.AddLocalPosition({ -30.0f,120.0f });
		Monster_HpBar->Off();
	}



	Mini_Boss->AutoSpriteSizeOn();
	Mini_Boss->SetAutoScaleRatio(2.0f);
	Mini_Boss->ChangeAnimation("Mini_Boss_Move_Down");
	//Mini_Boss->Transform.AddLocalPosition({ 0.0f,40.0f });



	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y });

	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
		Col->Transform.SetLocalScale({ 150.0f,150.0f }); 
	}

	{
		Mini_Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::MiniCol);
		Mini_Col->Transform.SetLocalScale({ 20.0f,20.0f });
		Mini_Col->SetCollisionType(ColType::AABBBOX2D);
	}

	{
		Monster_Weapon = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster_Weapon);
		Monster_Weapon->Transform.SetLocalScale({ 120.0f,120.0f });
		Monster_Weapon->SetCollisionType(ColType::AABBBOX2D);
		Monster_Weapon->Off(); 
	}

	Event.Enter = [this](GameEngineCollision* Col, GameEngineCollision* col)
	{
	

		if (Weapon_Collision_Check == false)
		{
			hit_Sound = GameEngineSound::SoundPlay("golem_dungeon_golem_hit.wav");


			std::shared_ptr<Spear_Effect> Object = GetLevel()->CreateActor<Spear_Effect>();
			Object->Transform.SetLocalPosition(Transform.GetWorldPosition());

			if (Inventory::This_Inventory->Item_Renders[26]->Item_Select == 6)
			{
				Monster_HpBar->Transform.AddLocalScale({ -0.05f,0.0f });
				Hp -= 5.0f;
			}
			else if (Inventory::This_Inventory->Item_Renders[26]->Item_Select == 7)
			{
				Monster_HpBar->Transform.AddLocalScale({ -0.3f,0.0f });
				Hp -= 30.0f;
			}
			else if (Inventory::This_Inventory->Item_Renders[26]->Item_Select == 8)
			{
				Monster_HpBar->Transform.AddLocalScale({ -0.1f,0.0f });
				Hp -= 10.0f;
			}
			else if (Inventory::This_Inventory->Item_Renders[26]->Item_Select == 9)
			{
				Monster_HpBar->Transform.AddLocalScale({ -0.2f,0.0f });
				Hp -= 20.0f;
			}
			Weapon_Collision_Check = true;
			ColorCheck = true;
		}

		Monster_BaseBar->On();
		Monster_HpBar->On();
		
	};

	Event.Stay = [this](GameEngineCollision* Col, GameEngineCollision* col)
	{
		
		

	};


	Event.Exit = [this](GameEngineCollision* Col, GameEngineCollision* col)
	{
		
	};


}

void MiniBoss::Update(float _Delta)
{
	
	if (Player::this_Player->MonsterDeath == true)
	{
		this->Death();
	}

	Monster_Damage(Mini_Boss, _Delta);




	
	if (Hp <= 0)
	{
		if (Death_Sound_Check == false)
		{
			Death_Sound = GameEngineSound::SoundPlay("enemy_death.wav");
			Death_Sound.SetVolume(2.5f);
			Death_Sound_Check = true;
		}

		Monster_HpBar->Transform.SetLocalScale({ 0.0f,0.0f });

		Number -= _Delta * 1;
		Mini_Boss->GetColorData().MulColor = { 1,1,1,Number };
		Monster_BaseBar->GetColorData().MulColor = { 1,1,1,Number };
		if (Number < 0.1)
		{
			for (size_t i = 0; i < 20; i++)
			{


				int Itemss = Random.RandomInt(0, 4);
				Random.SetSeed(Player::RandomSeed++);

				std::shared_ptr<Items> Object = GetLevel()->CreateActor<Items>();
				Object->Transform.SetWorldPosition({ Transform.GetWorldPosition() });
				Object->Set_Monster_Pos({ Transform.GetWorldPosition() });
				Object->Dir = Dir;



				Object->Set_item_Select(static_cast<Item>(Itemss));


			}
			this->Off();
		}


		return;
	}
	if (Col->Collision(ContentsCollisionType::CameraCollision))
	{
		Time += _Delta;
		MonsterDir();
		MonsterPushUpdate(_Delta);
		UpdateState(_Delta);
		Manager_Speed = Monster_Move(_Delta, Transform.GetWorldPosition(), MapName, Dir);
		
		Col->CollisionEvent(ContentsCollisionType::Spear, Event);
	}
	
	Monster_Collsision(_Delta);


	if (Number < -0.5)
	{
		this->Death();
	}
}


void MiniBoss::MonsterDir()
{
	float4 Player = Player::this_Player->Transform.GetWorldPosition() - Transform.GetWorldPosition();
	float4 Monster = { -1,0,0 };
	float Dot = float4::DotProduct3D(Player.NormalizeReturn(), Monster);
	float radian = atan2(Player.Y, Player.X) - atan2(Monster.Y, Monster.X);
	degree = float(abs(radian * (180.0 / 3.141592)));
}



void MiniBoss::MonsterPushUpdate(float _Delta)
{
	if (Inventory::This_Inventory->Item_Renders[26] != nullptr)
	{
		if (Inventory::This_Inventory->Item_Renders[26]->Item_Select == 6 || Inventory::This_Inventory->Item_Renders[26]->Item_Select == 9)
		{
			if (Weapon_Collision_Check == true)
			{
				PushTime_Check += _Delta;
			}


			if (Weapon_Collision_Check == true && PushTime_Check <= 0.15 && ObjectCollision(_Delta, Transform.GetWorldPosition(), MapName, Dir) == true)
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
		else if (Inventory::This_Inventory->Item_Renders[26]->Item_Select == 7)
		{
			if (Weapon_Collision_Check == true)
			{
				PushTime_Check += _Delta;
			}


			if (Weapon_Collision_Check == true && PushTime_Check <= 0.15 && ObjectCollision(_Delta, Transform.GetWorldPosition(), MapName, Dir) == true)
			{
				if (Player::this_Player->GetPlayerStateValue() == PlayerState::Sword_Down_Attack_01)
				{
					Transform.AddLocalPosition({ float4::DOWN * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Sword_Down_Attack_02)
				{
					Transform.AddLocalPosition({ float4::DOWN * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Sword_Down_Attack_03)
				{
					Transform.AddLocalPosition({ float4::DOWN * PushSpeed * _Delta });
				}

				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Sword_Left_Attack_01)
				{
					Transform.AddLocalPosition({ float4::LEFT * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Sword_Left_Attack_02)
				{
					Transform.AddLocalPosition({ float4::LEFT * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Sword_Left_Attack_03)
				{
					Transform.AddLocalPosition({ float4::LEFT * PushSpeed * _Delta });
				}


				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Sword_Up_Attack_01)
				{
					Transform.AddLocalPosition({ float4::UP * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Sword_Up_Attack_02)
				{
					Transform.AddLocalPosition({ float4::UP * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Sword_Up_Attack_03)
				{
					Transform.AddLocalPosition({ float4::UP * PushSpeed * _Delta });
				}

				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Sword_Right_Attack_01)
				{
					Transform.AddLocalPosition({ float4::RIGHT * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Sword_Right_Attack_02)
				{
					Transform.AddLocalPosition({ float4::RIGHT * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Sword_Right_Attack_03)
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
		else if (Inventory::This_Inventory->Item_Renders[26]->Item_Select == 8)
		{
			if (Weapon_Collision_Check == true)
			{
				PushTime_Check += _Delta;
			}


			if (Weapon_Collision_Check == true && PushTime_Check <= 0.15 && ObjectCollision(_Delta, Transform.GetWorldPosition(), MapName, Dir) == true)
			{
				if (Player::this_Player->GetPlayerStateValue() == PlayerState::Gloves_Down_Attack_01)
				{
					Transform.AddLocalPosition({ float4::DOWN * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Gloves_Down_Attack_02)
				{
					Transform.AddLocalPosition({ float4::DOWN * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Gloves_Down_Attack_03)
				{
					Transform.AddLocalPosition({ float4::DOWN * PushSpeed * _Delta });
				}

				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Gloves_Left_Attack_01)
				{
					Transform.AddLocalPosition({ float4::LEFT * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Gloves_Left_Attack_02)
				{
					Transform.AddLocalPosition({ float4::LEFT * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Gloves_Left_Attack_03)
				{
					Transform.AddLocalPosition({ float4::LEFT * PushSpeed * _Delta });
				}


				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Gloves_Up_Attack_01)
				{
					Transform.AddLocalPosition({ float4::UP * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Gloves_Up_Attack_02)
				{
					Transform.AddLocalPosition({ float4::UP * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Gloves_Up_Attack_03)
				{
					Transform.AddLocalPosition({ float4::UP * PushSpeed * _Delta });
				}

				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Gloves_Right_Attack_01)
				{
					Transform.AddLocalPosition({ float4::RIGHT * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Gloves_Right_Attack_02)
				{
					Transform.AddLocalPosition({ float4::RIGHT * PushSpeed * _Delta });
				}
				else if (Player::this_Player->GetPlayerStateValue() == PlayerState::Gloves_Right_Attack_03)
				{
					Transform.AddLocalPosition({ float4::RIGHT * PushSpeed * _Delta });
				}
			}

			if (PushTime_Check > 0.3)
			{
				PushTime_Check = 0;
				Weapon_Collision_Check = false;
			}
		}
	}

}
void MiniBoss::AnimationCheck(const std::string_view& _AnimationName)
{
	Mini_Boss->ChangeAnimation(_AnimationName);
}
