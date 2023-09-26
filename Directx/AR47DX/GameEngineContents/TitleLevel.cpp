#include "PreCompile.h"
#include "TitleLevel.h"
#include "Title.h"
TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{

	{
		// ������ ���̴��� ���δ� ���δ� �ε��ϴ� �ڵ带 ģ��.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Texture");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}

		GameEngineSprite::CreateCut("TestPlayer.png", 6, 6);
		GameEngineSprite::CreateCut("spearHitEffect_3.png", 3, 1);
		GameEngineSprite::CreateSingle("collision.png");
	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
			GameEngineDirectory& Dir = Directorys[i];

			GameEngineSprite::CreateFolder(Dir.GetStringPath());
		}

		GameEngineSprite::CreateSingle("Button_E.png");
		GameEngineSprite::CreateSingle("Button_I.png");
		GameEngineSprite::CreateSingle("Button_J.png");
		GameEngineSprite::CreateSingle("Button_K.png");
		GameEngineSprite::CreateSingle("Button_Space.png");
		GameEngineSprite::CreateSingle("Button_Z.png");
		GameEngineSprite::CreateSingle("Circle.png");
		GameEngineSprite::CreateSingle("HealthBar_Base.png");
		GameEngineSprite::CreateSingle("Heart.png");
		GameEngineSprite::CreateSingle("Hp_Bar.png");
		GameEngineSprite::CreateSingle("Pocket.png");
		GameEngineSprite::CreateSingle("Bag.png");
		GameEngineSprite::CreateSingle("Training_Spear.png");
		GameEngineSprite::CreateSingle("MiniWill.png");

	}




	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);


	std::shared_ptr<Title> Object = CreateActor<Title>(TitleOrder::Title);



}


void TitleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsPress('P'))
	{
		GameEngineCore::ChangeLevel("TutorialLevel");
	}
}


void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}