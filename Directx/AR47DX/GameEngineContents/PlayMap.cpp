#include "PreCompile.h"
#include "PlayMap.h"

PlayMap* PlayMap::MainMap;

PlayMap::PlayMap()
{
	MainMap = this;
}

PlayMap::~PlayMap()
{
}

void PlayMap::Update(float _DeltaTime)
{
	//static float Time = 5.0f;
	//Time -= _DeltaTime;

	//if (nullptr != Renderer && Time <= 0.0f)
	//{
	//	Renderer->Death();
	//	Renderer = nullptr;
	//}
}

void PlayMap::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->SetSprite("loadingBG.bmp");

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("loadingBG.bmp");

		float4 HScale = Tex->GetScale().Half();
		HScale.Y *= -1.0f;


		float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
		Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
		Renderer->SetImageScale({ 1280,720 });
	}
}

GameEngineColor PlayMap::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
{
	// �÷��̾��� ��ġ�� �̹����� ��ǥ��� �����Ѵ�.
	// �̹����� ���������� �Ʒ��� ���������� +�� �Ǳ� �����̴�.
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("loadingBG.bmp");


	return Tex->GetColor(_Pos, _DefaultColor);
}