#include "PreCompile.h"
#include "PlayerEffect.h"
#include <GameEngineCore/GameEngineCore.h>

PlayerEffect::PlayerEffect() 
{
}

PlayerEffect::~PlayerEffect() 
{
}

void PlayerEffect::Start()
{








	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("FadePostEffect");
	EffectUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	EffectUnit.ShaderResHelper.SetSampler("DiffuseTexSampler", "POINT");
	EffectUnit.ShaderResHelper.SetTexture("DiffuseTex", EffectTarget->GetTexture(0));

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	ResultTarget = GameEngineRenderTarget::Create();
	ResultTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);


}

void PlayerEffect::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	EffectTarget->Copy(0, ResultTarget, 0);
}