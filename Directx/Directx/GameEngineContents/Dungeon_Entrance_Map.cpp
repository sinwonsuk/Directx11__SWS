#include "PreCompile.h"
#include "Dungeon_Entrance_Map.h"
#include "Player.h"
Dungeon_Entrance_Map::Dungeon_Entrance_Map()
{
}

Dungeon_Entrance_Map::~Dungeon_Entrance_Map()
{
}

GameEngineColor Dungeon_Entrance_Map::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
{
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Dungeon_Entrance_Pixel.png");
	return Tex->GetColor(_Pos, _DefaultColor);

}

void Dungeon_Entrance_Map::PixelCollision(float _Delta)
{
	float4 Left_Player_Pos = { Player::this_Player->Transform.GetWorldPosition().X - 20.0f,Player::this_Player->Transform.GetWorldPosition().Y };
	float4 Right_Player_Pos = { Player::this_Player->Transform.GetWorldPosition().X + 20.0f,Player::this_Player->Transform.GetWorldPosition().Y };
	float4 Up_Player_Pos = { Player::this_Player->Transform.GetWorldPosition().X,Player::this_Player->Transform.GetWorldPosition().Y + 20.0f };
	float4 Down_Player_Pos = { Player::this_Player->Transform.GetWorldPosition().X ,Player::this_Player->Transform.GetWorldPosition().Y - 20.0f };

	if (GameEngineColor::MAGENTA == GetColor({ Left_Player_Pos }, { 255,0,0,255 }))
	{
		Player::this_Player->LeftMove = false;
	}

	else
	{
		Player::this_Player->LeftMove = true;
	}



	if (GameEngineColor::MAGENTA == GetColor({ Right_Player_Pos }, { 255,0,0,255 }))
	{
		Player::this_Player->RightMove = false;
	}
	else
	{
		Player::this_Player->RightMove = true;
	}


	if (GameEngineColor::MAGENTA == GetColor({ Up_Player_Pos }, { 255, 0, 0, 255 }))
	{
		Player::this_Player->UpMove = false;
	}
	else
	{
		Player::this_Player->UpMove = true;
	}



	if (GameEngineColor::MAGENTA == GetColor({ Down_Player_Pos }, { 255, 0, 0, 255 }))
	{
		Player::this_Player->DownMove = false;
	}
	else
	{
		Player::this_Player->DownMove = true;
	}

	/*else
	{
		Player::this_Player->RightMove = true;
		Player::this_Player->UpMove = true;
		Player::this_Player->LeftMove = true;
		Player::this_Player->DownMove = true;
	}*/











}
void Dungeon_Entrance_Map::Start()
{

	GameEngineInput::AddInputObject(this);

	float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
	Transform.SetLocalPosition({ 1204, -1028 });

	{
		BackGround = CreateComponent<GameEngineSpriteRenderer>(-100);
		BackGround->SetSprite("DungeonsEntrance_Base", 0);
		BackGround->AutoSpriteSizeOn();
		BackGround->SetAutoScaleRatio(2.0f);
		//BackGround->Transform.AddLocalPosition({ 0.0f,0.0f,100.0f });
	}


	{
		DungeonsEntrance_Top = CreateComponent<GameEngineSpriteRenderer>(-40);
		DungeonsEntrance_Top->SetSprite("DungeonsEntrance_Top", 0);
		DungeonsEntrance_Top->AutoSpriteSizeOn();
		DungeonsEntrance_Top->SetAutoScaleRatio(2.0f);
		DungeonsEntrance_Top->Transform.SetWorldPosition({ 1216.0f,-1102.0f });
		//DungeonsEntrance_Top->Transform.SetWorldPosition({ 624.0f,-1262.0f });
	}
	{
		Dungeon_Door = CreateComponent<GameEngineSpriteRenderer>(-40);
		Dungeon_Door->SetSprite("Dungeon1_Door", 0);
		Dungeon_Door->AutoSpriteSizeOn();
		Dungeon_Door->SetAutoScaleRatio(2.0f);
		Dungeon_Door->Transform.SetWorldPosition({ 699.0f,-892.0f });	
	}
	{
		Dungeon_Door_02 = CreateComponent<GameEngineSpriteRenderer>(-40);
		Dungeon_Door_02->SetSprite("Dungeon_Door", 0);
		Dungeon_Door_02->AutoSpriteSizeOn();
		Dungeon_Door_02->SetAutoScaleRatio(2.0f);
		Dungeon_Door_02->Transform.SetWorldPosition({ 1711,-907.0f });
	}

	{
		Dungeon_Door_03 = CreateComponent<GameEngineSpriteRenderer>(-40);
		Dungeon_Door_03->SetSprite("Dungeon_Door", 0);
		Dungeon_Door_03->AutoSpriteSizeOn();
		Dungeon_Door_03->SetAutoScaleRatio(2.0f);
		Dungeon_Door_03->Transform.SetWorldPosition({ 1481.0f,-624.0f });
	}

	{
		Dungeon_Door_04 = CreateComponent<GameEngineSpriteRenderer>(-40);
		Dungeon_Door_04->SetSprite("Dungeon_Door", 0);
		Dungeon_Door_04->AutoSpriteSizeOn();
		Dungeon_Door_04->SetAutoScaleRatio(2.0f);
		Dungeon_Door_04->Transform.SetWorldPosition({ 942.0f,-624.0f });
	}

	{
		Dungeon_Open = CreateComponent<GameEngineSpriteRenderer>(0);
		Dungeon_Open->CreateAnimation("Dungeon_Open", "Dungeon_Open", 0.1f, -1, -1, false);
		Dungeon_Open->CreateAnimation("Dungeon_Close", "Dungeon_Close", 0.1f, -1, -1, false);
		Dungeon_Open->Off(); 


		Dungeon_Open->AutoSpriteSizeOn();
		Dungeon_Open->SetAutoScaleRatio(2.0f);
		Dungeon_Open->Transform.SetWorldPosition({ 699.0f,-892.0f });
		Dungeon_Open->ChangeAnimation("Dungeon_Open");

	}
	



	/*{
		

		Dungeon_Entrance_Pixel = CreateComponent<GameEngineSpriteRenderer>(-100);
		Dungeon_Entrance_Pixel->SetSprite("Dungeon_Entrance_Pixel", 0);
		Dungeon_Entrance_Pixel->AutoSpriteSizeOn();
		Dungeon_Entrance_Pixel->SetAutoScaleRatio(1.0f);
	}*/

	Change_Town = CreateComponent<GameEngineCollision>(ContentsCollisionType::Dungeon_Entrance);
	Change_Town->Transform.SetLocalScale({ 100.0f,10.0f });
	Change_Town->Transform.SetWorldPosition({ 1211,-1954 });
	Change_Town->SetCollisionType(ColType::AABBBOX2D);


	Dungeon_Near = CreateComponent<GameEngineCollision>(ContentsCollisionType::Dungeon_Near);
	Dungeon_Near->Transform.SetLocalScale({ 250.0f,220.0f });
	Dungeon_Near->Transform.SetWorldPosition({ 733.0f,-1037.0f });
	Dungeon_Near->SetCollisionType(ColType::AABBBOX2D);



}





void Dungeon_Entrance_Map::Update(float _DeltaTime)
{
	if (Dungeon_Near->Collision(ContentsCollisionType::Player))
	{

		CollisionCheck = true; 
		Dungeon_Open->On(); 
		Dungeon_Door->Off(); 
	}

	if (Dungeon_Near->Collision(ContentsCollisionType::Player) ==false && CollisionCheck ==true)
	{
		Dungeon_Open->ChangeAnimation("Dungeon_Close"); 
	
		if (Dungeon_Open->IsCurAnimationEnd())
		{
			Dungeon_Door->On(); 
			Dungeon_Open->ChangeAnimation("Dungeon_Open");
			Dungeon_Open->Off();
			CollisionCheck = false;
		}

	}



	PixelCollision(_DeltaTime);
	//std::shared_ptr<class GameEngineSpriteRenderer> AD  = Dungeon_Door;

	if (Change_Town->Collision(ContentsCollisionType::Player))
	{
		int a = 0;
	
	
		if (GameEngineInput::IsDown('J',this))
		{
			GameEngineCore::ChangeLevel("WorldLevel");
		}
	}
	
	
	//if (GameEngineInput::IsDown('1') && check == false)
	//{
	//	check = true;
	//}
	//else if (GameEngineInput::IsDown('1') && check == true)
	//{
	//	check = false;
	//}


	//if (check == true)
	//{
	//	if (GameEngineInput::IsPress('A'))
	//	{
	//		GetLevel()->GetMainCamera()->Transform.AddWorldPosition({ 5.0f,0.0f });
	//	}

	//	if (GameEngineInput::IsPress('D'))
	//	{
	//		GetLevel()->GetMainCamera()->Transform.AddWorldPosition({ -5.0f,0.0f });
	//		return;
	//	}

	//	if (GameEngineInput::IsPress('W'))
	//	{
	//		GetLevel()->GetMainCamera()->Transform.AddWorldPosition(float4::UP *5);
	//		return;
	//	}

	//	if (GameEngineInput::IsPress('S'))
	//	{
	//		GetLevel()->GetMainCamera()->Transform.AddWorldPosition(float4::DOWN* 5);
	//		return;
	//	}
	//}
	//if (check == false)
	//{


	//	if (GameEngineInput::IsPress('A'))
	//	{
	//		AD->Transform.AddWorldPosition({ 1.0f,0.0f });
	//	}

	//	if (GameEngineInput::IsPress('D'))
	//	{
	//		AD->Transform.AddWorldPosition({ -1.0f,0.0f });
	//		return;
	//	}

	//	if (GameEngineInput::IsPress('W'))
	//	{
	//		AD->Transform.AddWorldPosition(float4::UP);
	//		return;
	//	}

	//	if (GameEngineInput::IsPress('S'))
	//	{
	//		AD->Transform.AddWorldPosition(float4::DOWN);
	//		return;
	//	}
	//}

	//
	//TransformData date = AD->Transform.GetConstTransformDataRef();

	///*date.LocalPosition

	//float4 WorldMousePos*/

	//float4 WorldMousePos = date.WorldPosition;
	//OutputDebugStringA(WorldMousePos.ToString("\n").c_str());

}