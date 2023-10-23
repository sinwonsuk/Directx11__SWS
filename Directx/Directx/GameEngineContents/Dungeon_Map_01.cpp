#include "PreCompile.h"
#include "Dungeon_Map_01.h"
#include "Player.h"

Dungeon_Map_01::Dungeon_Map_01()
{
}

Dungeon_Map_01::~Dungeon_Map_01()
{
}



void Dungeon_Map_01::Start()
{
	/*{
		std::shared_ptr<Object_jar> Object = GetLevel()->CreateActor<Object_jar>();
	}*/

	

	

	{
		BackGround = CreateComponent<GameEngineSpriteRenderer>(100);
		BackGround->SetSprite("BackGround", 1);
		BackGround->SetImageScale({ 1380.0f,740.0f });
		BackGround->Transform.AddLocalPosition({ 0.0f,0.0f });
	}

	{
		Map_floor = CreateComponent<GameEngineSpriteRenderer>(-100);
		Map_floor->SetSprite("Floor_01", 0);
	
	}

	/*{

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
	}*/


	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y });
	


	Right_Collision_Door = CreateComponent<GameEngineCollision>(ContentsCollisionType::Door);
	Right_Collision_Door->Transform.AddLocalPosition({ 550.0f,20.0f,0.0f });
	Right_Collision_Door->Transform.SetLocalScale({ 90.0f,120.0f,0.0f });




}

void Dungeon_Map_01::Update(float _Delta)
{


	
	

}
