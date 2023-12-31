#include "PreCompile.h"
#include "Tutorial_Map_06.h"
#include "Slime_Potal.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "Player.h"
#include "golem_Wizard.h"
#include "golem_Solder.h"
#include "golem_Stone.h"
TutorialMap_06::TutorialMap_06()
{
}

TutorialMap_06::~TutorialMap_06()
{
}

void TutorialMap_06::Start()
{
	Map_Number = 5;

	




	{

		BackGround = CreateComponent<GameEngineSpriteRenderer>(-100);
		BackGround->SetSprite("Tutorial_BackGround", 1);
		BackGround->SetImageScale({ 1380.0f,750.0f });

	}

	{
		Map_floor_01 = CreateComponent<GameEngineSpriteRenderer>(-100);
		Map_floor_01->SetSprite("Tutorial_Floor_06", 0);
		Map_floor_01->SetImageScale({ 1050.0f,552.0f });
	}

	{
		LeftDoor = CreateComponent<GameEngineSpriteRenderer>(-100);
		LeftDoor->Transform.AddLocalRotation({ 0.0f,0.0f,90.0f });
		LeftDoor->Transform.AddLocalPosition({ -550.0f,20.0f,0.0f });
		LeftDoor->SetAutoScaleRatio(1.5f);
		LeftDoor->SetSprite("Door", 1);
	}
	{
		RightDoor = CreateComponent<GameEngineSpriteRenderer>(-100);
		RightDoor->Transform.AddLocalRotation({ 0.0f,0.0f,-90.0f });
		RightDoor->Transform.AddLocalPosition({ 550.0f,20.0f,0.0f });
		RightDoor->SetAutoScaleRatio(1.5f);
		RightDoor->SetSprite("Door", 0);
	}



	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y });
	Transform.AddLocalPosition({ 1280 * Map_Number ,0.0f });




	/*{
		std::shared_ptr<Slime_Potal> object = GetLevel()->CreateActor<Slime_Potal>();
		object->Transform.SetLocalPosition({ Transform.GetWorldPosition().X,Transform.GetWorldPosition().Y + 300.0f });
	}

	{
		std::shared_ptr<Slime_Potal> object = GetLevel()->CreateActor<Slime_Potal>();
		object->Transform.SetLocalPosition({ Transform.GetWorldPosition().X,Transform.GetWorldPosition().Y - 300.0f });
	}*/


	Collision_Door = CreateComponent<GameEngineCollision>(ContentsCollisionType::Door);
	Collision_Door->Transform.AddLocalPosition({ 550.0f,20.0f,0.0f });
	Collision_Door->Transform.SetLocalScale({ 90.0f,120.0f,0.0f });
}

void TutorialMap_06::Update(float _Delta)
{
	TimeCheck += _Delta; 


	

    int Time = Random.RandomInt(1, 5);


	int Monster = Random.RandomInt(0, 2);
	
	int MonsterMove = Random.RandomInt(0, 1);


	//Random.SetSeed()

	if (Map_Check == 5)
	{
		ObjectCollision(_Delta, "Tutirial_Pixel_Map_06.png");
	}

	if (Player::this_Player->Transform.GetWorldPosition().X > 6500 && PlayerCheck ==false)
	{
		{
			std::shared_ptr<Slime_Potal> object = GetLevel()->CreateActor<Slime_Potal>();
			object->Transform.SetLocalPosition({ Transform.GetWorldPosition().X,Transform.GetWorldPosition().Y + 300.0f });
		}

		{
			std::shared_ptr<Slime_Potal> object = GetLevel()->CreateActor<Slime_Potal>();
			object->Transform.SetLocalPosition({ Transform.GetWorldPosition().X,Transform.GetWorldPosition().Y - 300.0f });
		}
		PlayerCheck = true;
	}

	

		if (Time < TimeCheck && PlayerCheck ==true)
		{

			if (Monster == 0)
			{
				if (MonsterMove == 0)
				{
					std::shared_ptr<golem_Wizard> object = GetLevel()->CreateActor<golem_Wizard>();
					object->Transform.SetLocalPosition({ Transform.GetWorldPosition().X,Transform.GetWorldPosition().Y + 250.0f });
					object->Set_MapName("Tutirial_Pixel_Map_06.png");
					object->Set_Dir({ 1280 * Map_Number,0.0f });

					TimeCheck = 0; 
				}
				if (MonsterMove == 1)
				{
					std::shared_ptr<golem_Wizard> object = GetLevel()->CreateActor<golem_Wizard>();
					object->Transform.SetLocalPosition({ Transform.GetWorldPosition().X,Transform.GetWorldPosition().Y - 250.0f });
					object->Set_MapName("Tutirial_Pixel_Map_06.png");
					object->Set_Dir({ 1280 * Map_Number,0.0f });
					TimeCheck = 0;
				}
			}
			if (Monster == 1)
			{
				if (MonsterMove == 0)
				{
					std::shared_ptr<golem_Solder> object = GetLevel()->CreateActor<golem_Solder>();
					object->Transform.SetLocalPosition({ Transform.GetWorldPosition().X,Transform.GetWorldPosition().Y + 250.0f });
					object->Set_MapName("Tutirial_Pixel_Map_06.png");
					object->Set_Dir({ 1280 * Map_Number,0.0f });
					TimeCheck = 0;
				}
				if (MonsterMove == 1)
				{
					std::shared_ptr<golem_Solder> object = GetLevel()->CreateActor<golem_Solder>();
					object->Transform.SetLocalPosition({ Transform.GetWorldPosition().X,Transform.GetWorldPosition().Y - 250.0f });
					object->Set_MapName("Tutirial_Pixel_Map_06.png");
					object->Set_Dir({ 1280 * Map_Number,0.0f });
					TimeCheck = 0;
				}
			}
			if (Monster == 2)
			{
				if (MonsterMove == 0)
				{
					std::shared_ptr<golem_Stone> object = GetLevel()->CreateActor<golem_Stone>();
					object->Transform.SetLocalPosition({ Transform.GetWorldPosition().X,Transform.GetWorldPosition().Y + 200.0f });
					object->Set_MapName("Tutirial_Pixel_Map_06.png");
					object->Set_Dir({ 1280 * Map_Number,0.0f });
					TimeCheck = 0;
				}
				if (MonsterMove == 1)
				{
					std::shared_ptr<golem_Stone> object = GetLevel()->CreateActor<golem_Stone>();
					object->Transform.SetLocalPosition({ Transform.GetWorldPosition().X,Transform.GetWorldPosition().Y - 200.0f });
					object->Set_MapName("Tutirial_Pixel_Map_06.png");
					object->Set_Dir({ 1280 * Map_Number,0.0f });

					TimeCheck = 0;
				}
			}

		}


	






}
