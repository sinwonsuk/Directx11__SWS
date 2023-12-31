#include "PreCompile.h"
#include "golem_Stone.h"
#include "Player.h"
#include "Spear_Effect.h"
#include "Inventory.h"
#include "Items.h"
golem_Stone::golem_Stone()
{
}

golem_Stone::~golem_Stone()
{
}

void golem_Stone::Start()
{
	Stone = CreateComponent<GameEngineSpriteRenderer>(130);
	Stone->CreateAnimation("golemhead_cycle_down", "golemhead_cycle_down", 0.1f, -1, -1, true);
	Stone->CreateAnimation("golemhead_cycle_left", "golemhead_cycle_left", 0.1f, -1, -1, true);
	Stone->CreateAnimation("golemhead_cycle_right", "golemhead_cycle_right", 0.1f, -1, -1, true);
	Stone->CreateAnimation("golemhead_cycle_up", "golemhead_cycle_up", 0.1f, -1, -1, true);
	Stone->CreateAnimation("golemhead_prepare_down", "golemhead_prepare_down", 0.1f, -1, -1, true);
	Stone->CreateAnimation("golemhead_prepare_left", "golemhead_prepare_left", 0.1f, -1, -1, true);
	Stone->CreateAnimation("golemhead_prepare_right", "golemhead_prepare_right", 0.1f, -1, -1, true);
	Stone->CreateAnimation("golemhead_prepare_up", "golemhead_prepare_up", 0.1f, -1, -1, true);

	Stone->CreateAnimation("golemhead_stunned_down", "golemhead_stunned_down", 0.1f, -1, -1, true);
	Stone->CreateAnimation("golemhead_stunned_left", "golemhead_stunned_left", 0.1f, -1, -1, true);
	Stone->CreateAnimation("golemhead_stunned_right", "golemhead_stunned_right", 0.1f, -1, -1, true);
	Stone->CreateAnimation("golemhead_stunned_up", "golemhead_stunned_up", 0.1f, -1, -1, true);

	//Wizard->SetPivotType(PivotType::Bottom);

	Stone->AutoSpriteSizeOn();
	Stone->SetAutoScaleRatio(2.0f);
	Stone->ChangeAnimation("golemhead_prepare_up");

	{
		Monster_BaseBar = CreateComponent<GameEngineSpriteRenderer>(130);
		Monster_BaseBar->SetSprite("MonsterUI", 0);
		Monster_BaseBar->SetPivotType(PivotType::Left);
		Monster_BaseBar->Transform.AddLocalPosition({ -30.0f,60.0f });
		Monster_BaseBar->Off();
	}

	{
		Monster_HpBar = CreateComponent<GameEngineSpriteRenderer>(130);
		Monster_HpBar->SetSprite("MonsterUI", 1);
		Monster_HpBar->SetPivotType(PivotType::Left);
		Monster_HpBar->Transform.AddLocalPosition({ -30.0f,60.0f });
		Monster_HpBar->Off();
	}

	{
		Monster_Weapon = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster_Weapon);
		Monster_Weapon->Transform.SetLocalScale({ 50.0f,50.0f });
		Monster_Weapon->SetCollisionType(ColType::AABBBOX2D);
	}
	Event.Enter = [this](GameEngineCollision* Col, GameEngineCollision* col)
	{
		/*	GameEngineActor* Actor = col->GetActor();
			Spear* ptr = dynamic_cast<Spear*>(Actor);*/

		if (Weapon_Collision_Check == false)
		{
			std::shared_ptr<Spear_Effect> Object = GetLevel()->CreateActor<Spear_Effect>();
			Object->Transform.SetLocalPosition(Transform.GetWorldPosition());

			Hit_Sound = GameEngineSound::SoundPlay("golem_dungeon_golem_hit.wav");

			if (Inventory::This_Inventory->Item_Renders[26]->Item_Select == 6)
			{
				Monster_HpBar->Transform.AddLocalScale({ -0.3f,0.0f });
				Hp -= 30.0f;
			}
			else if (Inventory::This_Inventory->Item_Renders[26]->Item_Select == 7)
			{
				Monster_HpBar->Transform.AddLocalScale({ -1.0f,0.0f });
				Hp -= 100.0f;
			}
			else if (Inventory::This_Inventory->Item_Renders[26]->Item_Select == 8)
			{
				Monster_HpBar->Transform.AddLocalScale({ -0.5f,0.0f });
				Hp -= 50.0f;
			}
			else if (Inventory::This_Inventory->Item_Renders[26]->Item_Select == 9)
			{
				Monster_HpBar->Transform.AddLocalScale({ -0.5f,0.0f });
				Hp -= 50.0f;
			}
			Weapon_Collision_Check = true;
			ColorCheck = true;
		}

		Monster_BaseBar->On();
		Monster_HpBar->On();

		//Hp -= 10.0f;




		/*GameEngineActor* Actor = col->GetActor();
		Spear* ptr = dynamic_cast<Spear*>(Actor);
		ptr->Col->Off();*/
	};

	Event.Stay = [this](GameEngineCollision* Col, GameEngineCollision* col)
	{



	};


	Event.Exit = [this](GameEngineCollision* Col, GameEngineCollision* col)
	{
		/*Monster_BaseBar->Off();
		Monster_HpBar->Off();*/
	};






	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
		Col->Transform.SetLocalScale({ 50.0f,50.0f });
	}

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y });

	
}

void golem_Stone::Update(float _Delta)
{
	Time += _Delta;

	//if(Monster_HpBar->Transform.AddLocalScale({ -0.3f,0.0f });)


	if (Player::this_Player->MonsterDeath == true)
	{
		this->Death();
	}

	if (Hp <= 0)
	{
		Monster_HpBar->Transform.SetLocalScale({ 0.0f,0.0f });

		if (Death_Sound_Check == false)
		{
			Death_Sound = GameEngineSound::SoundPlay("enemy_death.wav");
			Death_Sound.SetVolume(2.5f);
			Death_Sound_Check = true;
		}

		Monster_HpBar->Off(); 
		Monster_Weapon->Off();
		Number -= _Delta * 1;
		Stone->GetColorData().MulColor = { 1,1,1,Number };
		Monster_BaseBar->GetColorData().MulColor = { 1,1,1,Number };
		if (Number < 0.1)
		{
			for (size_t i = 0; i < 5; i++)
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


	Monster_Damage(Stone, _Delta);


	if (Col->Collision(ContentsCollisionType::CameraCollision))
	{
		
		
		
		MonsterDir();

		MonsterPushUpdate(_Delta);



		CollisionStop(_Delta, MapName, Dir);


		Col->CollisionEvent(ContentsCollisionType::Spear, Event);

		UpdateState(_Delta);
	}


	//Monster_Collsision(_Delta);

	if (Number < -0.5)
	{
		this->Death();
	}


}
void golem_Stone::AnimationCheck(const std::string_view& _AnimationName)
{
	Stone->ChangeAnimation(_AnimationName);
}

void golem_Stone::CollisionStop(float _Delta, std::string_view _Name, float4 _distance_fixation)
{

	float4 Left_Stone_Pos = { Transform.GetWorldPosition().X - 20.0f,Transform.GetWorldPosition().Y };
	float4 Right_Stone_Pos = {Transform.GetWorldPosition().X + 20.0f,Transform.GetWorldPosition().Y };
	float4 Up_Stone_Pos = { Transform.GetWorldPosition().X,Transform.GetWorldPosition().Y + 20.0f };
	float4 Down_Stone_Pos = { Transform.GetWorldPosition().X ,Transform.GetWorldPosition().Y - 20.0f };

	if (GameEngineColor::MAGENTA == GetColor({ (Left_Stone_Pos - _distance_fixation) / 40 }, { 255,0,0,255 }, _Name))
	{
		Transform.AddLocalPosition({ float4::RIGHT * _Delta * 10.0f });

		Attack_Sound_Check = false;
		Roll_Sound.Stop();
		ChangeState(golem_Stone_State::LeftCollision);
		return;
	}

	else if (GameEngineColor::BLUE == GetColor({ (Left_Stone_Pos - _distance_fixation) / 40 }, { 255,0,0,255 }, _Name))
	{
		Transform.AddLocalPosition({ float4::RIGHT * _Delta * 10.0f });
		Attack_Sound_Check = false;
		Roll_Sound.Stop();
		ChangeState(golem_Stone_State::LeftCollision);
		return;
	}
	else if (GameEngineColor::GREEN == GetColor({ (Left_Stone_Pos - _distance_fixation) / 40 }, { 0,0,255,255 }, _Name))
	{
		Transform.AddLocalPosition({ float4::RIGHT * _Delta * 10.0f });
		Attack_Sound_Check = false;
		Roll_Sound.Stop();
		ChangeState(golem_Stone_State::LeftCollision);
		return;
	}



	else if (GameEngineColor::MAGENTA == GetColor({ (Right_Stone_Pos - _distance_fixation) / 40 }, { 255,0,0,255 }, _Name))
	{
		Transform.AddLocalPosition({ float4::LEFT * _Delta * 10.0f });
		Attack_Sound_Check = false;
		Roll_Sound.Stop();
		ChangeState(golem_Stone_State::RightCollision);
		return;
	}

	else if (GameEngineColor::BLUE == GetColor({ (Right_Stone_Pos - _distance_fixation) / 40 }, { 255,0,0,255 }, _Name))
	{
		Transform.AddLocalPosition({ float4::LEFT * _Delta * 10.0f });
		Attack_Sound_Check = false;
		Roll_Sound.Stop();
		ChangeState(golem_Stone_State::RightCollision);
		return;
	}
	else if (GameEngineColor::GREEN == GetColor({ (Right_Stone_Pos - _distance_fixation) / 40 }, { 0,0,255,255 }, _Name))
	{
		Transform.AddLocalPosition({ float4::LEFT * _Delta * 10.0f });
		Attack_Sound_Check = false;
		Roll_Sound.Stop();
		ChangeState(golem_Stone_State::RightCollision);
		return;
	}
	

	else if (GameEngineColor::MAGENTA == GetColor({ (Up_Stone_Pos - _distance_fixation) / 40 }, { 255, 0, 0, 255 }, _Name))
	{
		Transform.AddLocalPosition({ float4::DOWN * _Delta * 10.0f });
		Attack_Sound_Check = false;
		Roll_Sound.Stop();
		ChangeState(golem_Stone_State::UpCollision);
		return;
	}

	else if (GameEngineColor::BLUE == GetColor({ (Up_Stone_Pos - _distance_fixation) / 40 }, { 255, 0, 0, 255 }, _Name))
	{
		Transform.AddLocalPosition({ float4::DOWN * _Delta * 10.0f });
		Attack_Sound_Check = false;
		Roll_Sound.Stop();
		ChangeState(golem_Stone_State::UpCollision);
		return;
	}
	else if (GameEngineColor::GREEN == GetColor({ (Up_Stone_Pos - _distance_fixation) / 40 }, { 0, 0, 255, 255 }, _Name))
	{
		Transform.AddLocalPosition({ float4::DOWN * _Delta * 10.0f });
		Attack_Sound_Check = false;
		Roll_Sound.Stop();
		ChangeState(golem_Stone_State::UpCollision);
		return;

	}


	else if (GameEngineColor::MAGENTA == GetColor({ (Down_Stone_Pos - _distance_fixation) / 40 }, { 255, 0, 0, 255 }, _Name))
	{
		Transform.AddLocalPosition({ float4::UP * _Delta * 10.0f });
		Attack_Sound_Check = false;
		Roll_Sound.Stop();
		ChangeState(golem_Stone_State::DownCollision);
		return;
	}

	else if (GameEngineColor::BLUE == GetColor({ (Down_Stone_Pos - _distance_fixation) / 40 }, { 255, 0, 0, 255 }, _Name))
	{
		Transform.AddLocalPosition({ float4::UP * _Delta * 10.0f });
		Attack_Sound_Check = false;
		Roll_Sound.Stop();
		ChangeState(golem_Stone_State::DownCollision);
		return;
	}
	else if (GameEngineColor::GREEN == GetColor({ (Down_Stone_Pos - _distance_fixation) / 40 }, { 0, 0, 255, 255 }, _Name))
	{
		Transform.AddLocalPosition({ float4::UP * _Delta * 10.0f });
		Attack_Sound_Check = false;
		Roll_Sound.Stop();
		ChangeState(golem_Stone_State::DownCollision);
		return;
	}
	




}

GameEngineColor golem_Stone::GetColor(float4 _Pos, GameEngineColor _DefaultColor, std::string_view _Name)
{
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(_Name);

	return Tex->GetColor(_Pos, _DefaultColor);
}

void golem_Stone::MonsterPushUpdate(float _Delta)
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

void golem_Stone::MonsterDir()
{
	float4 Player = Player::this_Player->Transform.GetWorldPosition() - Transform.GetWorldPosition();
	float4 Monster = { -1,0,0 };
	float Dot = float4::DotProduct3D(Player.NormalizeReturn(), Monster);
	float radian = atan2(Player.Y, Player.X) - atan2(Monster.Y, Monster.X);
	degree = float(abs(radian * (180.0 / 3.141592)));
}
