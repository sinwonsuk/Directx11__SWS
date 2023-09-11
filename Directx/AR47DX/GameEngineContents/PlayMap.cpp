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
	// 플레이어의 위치를 이미지의 좌표계로 변경한다.
	// 이미지는 위에서부터 아래로 내려갈수록 +가 되기 때문이다.
	_Pos.Y *= -1.0f;

	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("loadingBG.bmp");


	return Tex->GetColor(_Pos, _DefaultColor);
}