#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "PlayLevel.h"
#include "TitleLevel.h"
#include "WorldLevel.h"
#include "TutorialLevel.h"
#include "ShopLevel.h"
#include "Dungeon_Entrance_Level.h"
#include "ContentsControlWindow.h"
#include "Path_Finder_Level.h"
#include "EndLevel.h"
ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	GameEngineGUI::CreateGUIWindow<ContentsControlWindow>("ContentsControlWindow");

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<TutorialLevel>("TutorialLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<WorldLevel>("WorldLevel");
	GameEngineCore::CreateLevel<ShopLevel>("ShopLevel");
	GameEngineCore::CreateLevel<Dungeon_Entrance_Level>("Dungeon_Entrance_Level");
	GameEngineCore::CreateLevel<Path_Finder_Level>("Path_Finder_Level");
	GameEngineCore::CreateLevel<End_Level>("EndLevel");
	GameEngineCore::ChangeLevel("TitleLevel");



}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}