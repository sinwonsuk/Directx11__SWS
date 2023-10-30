#include "PreCompile.h"
#include "GameEngineRenderUnit.h"
#include "GameEngineMesh.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineMaterial.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineShader.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderer.H"


GameEngineRenderUnit::GameEngineRenderUnit() 
{
}

GameEngineRenderUnit::~GameEngineRenderUnit() 
{
}

void GameEngineRenderUnit::SetText(const std::string& _Font, const std::string& _Text, float _Scale, float4 _Color, FW1_TEXT_FLAG Flag)
{
	Font = GameEngineFont::Find(_Font);

	if (nullptr == Font)
	{
		MsgBoxAssert("�ε����� �ʴ� ��Ʈ�� ����Ϸ��� �߽��ϴ�.");
	}
	

	FontText = _Text;
	FontScale = _Scale;
	FontColor = _Color;
	FontFlag = Flag;
}

void GameEngineRenderUnit::ResSetting()
{
	if (nullptr != Font)
	{
		return;
	}

	Mesh->InputAssembler1();
	Material->VertexShader();
	LayOut->Setting();
	Mesh->InputAssembler2();
	Material->Rasterizer();
	Material->PixelShader();
	Material->Blend();
	Material->DepthStencil();

	ShaderResHelper.AllShaderResourcesSetting();

	// �ִ� ������ ���� Ÿ���� �������� �մϴ�.
	D3D11_VIEWPORT ViewPort = {};
	ViewPort.Width = GameEngineCore::MainWindow.GetScale().X;
	ViewPort.Height = GameEngineCore::MainWindow.GetScale().Y;
	ViewPort.MinDepth = 0.0f;
	ViewPort.MaxDepth = 1.0f;
	ViewPort.TopLeftX = 0.0f;
	ViewPort.TopLeftY = 0.0f;
	GameEngineCore::GetContext()->RSSetViewports(1, &ViewPort);
}


void GameEngineRenderUnit::Draw()
{
	if (nullptr != Font)
	{
		float4x4 ViewPort;

		float4 ScreenPos = ParentRenderer->Transform.GetWorldPosition();
		float4 Scale = GameEngineCore::MainWindow.GetScale();
		ViewPort.ViewPort(Scale.X, Scale.Y, 0, 0);

		ScreenPos *= ParentRenderer->Transform.GetConstTransformDataRef().ViewMatrix;
		ScreenPos *= ParentRenderer->Transform.GetConstTransformDataRef().ProjectionMatrix;
		ScreenPos *= ViewPort;
		// WindowPos
		Font->FontDraw(FontText, FontScale, ScreenPos, FontColor, FontFlag);

		GameEngineCore::GetContext()->GSSetShader(nullptr, nullptr, 0);

		return;
	}

	Mesh->Draw();
}


void GameEngineRenderUnit::SetMesh(std::string_view _Name)
{
	Mesh = GameEngineMesh::Find(_Name);

	if (nullptr == Mesh)
	{
		MsgBoxAssert("�������� �ʴ� �Ž��� �����Ϸ��� �߽��ϴ�.");
	}

	if (nullptr == LayOut && nullptr != Material)
	{
		LayOut = std::make_shared<GameEngineInputLayOut>();
		LayOut->ResCreate(Mesh->GetVertexBuffer(), Material->GetVertexShader());
	}

}

void GameEngineRenderUnit::SetMaterial(std::string_view _Name)
{
	Material = GameEngineMaterial::Find(_Name);

	ShaderResHelper.ResClear();

	if (nullptr == Material)
	{
		MsgBoxAssert("�������� �ʴ� �Ž��� �����Ϸ��� �߽��ϴ�.");
	}

	if (nullptr == LayOut && nullptr != Mesh)
	{
		LayOut = std::make_shared<GameEngineInputLayOut>();
		LayOut->ResCreate(Mesh->GetVertexBuffer(), Material->GetVertexShader());
	}

	// ���ؽ� ���̴��� �ȼ����̴��� �� ����ִ� ���´�.

	// �������� ���̴� ���ҽ� ���ۿ�
	// ���ؽ��� �ȼ����̴��� ���ҽ��������� ���� �޽��ϴ�.
	ShaderResHelper.ShaderResCopy(Material->GetVertexShader().get());
	ShaderResHelper.ShaderResCopy(Material->GetPixelShader().get());

	// �̰� ȸ���� ���.

	if (nullptr != ParentRenderer 
		&& ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		const TransformData& Data = ParentRenderer->Transform.GetConstTransformDataRef();
		ShaderResHelper.SetConstantBufferLink("TransformData", Data);
	}

	//	//std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", _shader);
//	//if (nullptr != Buffer)
//	//{
//	//	const TransformData& Data = DataTransform->GetConstTransformDataRef();
//	//	Buffer->ChangeData(Data);
//	//	Buffer->Setting(0);
//	//}

}