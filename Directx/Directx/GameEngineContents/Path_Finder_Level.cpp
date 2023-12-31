#include "PreCompile.h"
#include "Path_Finder_Level.h"
#include "Player.h"
#include "golem_Solder.h"
#include "Dungeon_Map_10.h"
#include "CameraCollision.h"
#include "TileMap.h"
#include "MonsterTest.h"
#include "Boss_Rock.h"
#include "BabySlime.h"
Path_Finder_Level::Path_Finder_Level()
{
}

Path_Finder_Level::~Path_Finder_Level()
{
}

void Path_Finder_Level::Start()
{
	//float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	//GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	//GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	//{
	//	std::shared_ptr<CameraCollision> object = CreateActor<CameraCollision>();
	//}


	//
	//std::shared_ptr<BabySlime> Object = CreateActor<BabySlime>();
	////Object->Set_BossPos({0,0 });



	{
		std::shared_ptr<MonsterTest> Object =CreateActor<MonsterTest>();
		//Object->Transform.SetLocalPosition({ 840.0f,-440.0f });
	}

	/*{
		std::shared_ptr<MonsterTest> Object = CreateActor<MonsterTest>();
		Object->Transform.SetLocalPosition({ 840.0f,-440.0f });
	}

	{
		std::shared_ptr<MonsterTest> Object = CreateActor<MonsterTest>();
		Object->Transform.SetLocalPosition({ 840.0f,-440.0f });
	}

	{
		std::shared_ptr<MonsterTest> Object = CreateActor<MonsterTest>();
		Object->Transform.SetLocalPosition({ 840.0f,-440.0f });
	}

	{
		std::shared_ptr<MonsterTest> Object = CreateActor<MonsterTest>();
		Object->Transform.SetLocalPosition({ 840.0f,-440.0f });
	}

	{
		std::shared_ptr<MonsterTest> Object = CreateActor<MonsterTest>();
		Object->Transform.SetLocalPosition({ 840.0f,-440.0f });
	}

	{
		std::shared_ptr<MonsterTest> Object = CreateActor<MonsterTest>();
		Object->Transform.SetLocalPosition({ 840.0f,-440.0f });
	}

	{
		std::shared_ptr<MonsterTest> Object = CreateActor<MonsterTest>();
		Object->Transform.SetLocalPosition({ 840.0f,-440.0f });
	}


	

	{
		std::shared_ptr<Dungeon_Map_10> Object = CreateActor<Dungeon_Map_10>();
	}*/
	
	{
		std::shared_ptr<TileMap> Object = CreateActor<TileMap>();
	}
	
}

void Path_Finder_Level::Update(float _Delta)
{
}

void Path_Finder_Level::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		std::shared_ptr<Player> Object = CreateActor<Player>(-100);
		Object->Transform.AddLocalPosition({ 0.0f,0.0f });
	}


}

void Path_Finder_Level::LevelEnd(GameEngineLevel* _NextLevel)
{
	Player::this_Player = nullptr;
}
