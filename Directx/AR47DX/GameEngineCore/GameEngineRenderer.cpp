#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineVertex.h"

#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineVertexShader.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineConstantBuffer.h"

GameEngineRenderer::GameEngineRenderer() 
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::Start()
{
	// ����ī�޶� ����.
	SetViewCameraSelect(0);

	// ī�޶� ã�Ƽ� ���� �մϴ�.
	// ī�޸� ã������? GameEngineLevel
	// Level���� ã�ƾ���.
	// Level���� ��� ����? ���� ��� �ִ� Actor�� ��� �־�.
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	std::shared_ptr<GameEngineCamera> Camera = Level->GetCamera(_Order);

	if (nullptr == Camera)
	{
		MsgBoxAssert("ī�޶� �������� �ʴµ� �������� �������� �߽��ϴ�.");
		return;
	}

	Camera->Renderers[_Order].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
	ViewInfo[Camera.get()] = _Order;
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	ResSetting();
	Draw();
}

void GameEngineRenderer::ResSetting()
{

	{
		float4x4 WorldViewProjection = Transform.GetWorldViewPorjectionMatrix();

		// ��ǲ�����1 ���ؽ� ���� ����
		std::shared_ptr<GameEngineVertexBuffer> VertexBuffer = GameEngineVertexBuffer::Find("Rect");
		if (nullptr != VertexBuffer)
		{
			VertexBuffer->Setting();
		}


		std::shared_ptr<GameEngineVertexShader> VertexShader = GameEngineVertexShader::Find("ColorShader_VS");

		if (nullptr != VertexShader && nullptr != VertexBuffer && nullptr == LayOut)
		{
			LayOut = std::make_shared<GameEngineInputLayOut>();
			LayOut->ResCreate(VertexBuffer, VertexShader);
		}

		std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData");

		if (nullptr != Buffer)
		{
			const TransformData& Data = Transform.GetConstTransformDataRef();
			Buffer->ChangeData(Data);
			Buffer->Setting();
		}



		if (nullptr != LayOut)
		{
			LayOut->Setting();
		}

		// ���ؽ� ���̴� ����
		if (nullptr != VertexShader)
		{
			VertexShader->Setting();
		}


		std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Find("Rect");
		if (nullptr != IndexBuffer)
		{
			IndexBuffer->Setting();
		}

		// �ε������۸� ��� ����� ���̳Ŀ� ���� �ɼ��̴�.
		// �ﰢ���� �迭�� ���� �׷���.
		// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		// ���� �迭�� ���� �׷���.
		// D3D11_PRIMITIVE_TOPOLOGY_LINELIST
		GameEngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		// ���߿� �ƿ�ǲ ���� ������ �׷����ϴ�.
		D3D11_VIEWPORT ViewPort = {};

		// ���� ���� �־�� �ϴµ� �װ� ���̷�Ʈ�� �˾Ƽ� ���ش�.
		// �츮 viewport�� 
		ViewPort.Width = GameEngineCore::MainWindow.GetScale().X;
		ViewPort.Height = GameEngineCore::MainWindow.GetScale().Y;
		ViewPort.MinDepth = 0.0f;
		ViewPort.MaxDepth = 1.0f;
		ViewPort.TopLeftX = 0.0f;
		ViewPort.TopLeftY = 0.0f;

		GameEngineCore::GetContext()->RSSetViewports(1, &ViewPort);


		std::shared_ptr<GameEngineRasterizer> Rasterizer = GameEngineRasterizer::Find("EngineRasterizer");
		if (nullptr != Rasterizer)
		{
			Rasterizer->Setting();
		}

		std::shared_ptr<GameEnginePixelShader> PixelShader = GameEnginePixelShader::Find("ColorShader_PS");
		if (nullptr != PixelShader)
		{
			PixelShader->Setting();
		}

		std::shared_ptr<class GameEngineRenderTarget> BackBufferRenderTarget = GameEngineCore::GetBackBufferRenderTarget();
		if (nullptr != BackBufferRenderTarget)
		{
			BackBufferRenderTarget->Setting();
		}




		// ���õ� ���ؽ� ���۷� �׷���.
		// �׸��ٶ�� ��ư�� �������� ������.
		// �̰� ��� ��ư�̴�.

		// �װ� �ٽ� �ɼ��� �ټ� �ִµ�.
		// �ε������۸� ����ϴ� ��� �M���ϴ� DRAW�Լ��̴�.
	}
}


void GameEngineRenderer::Draw()
{
	std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Find("Rect");
	if (nullptr == IndexBuffer)
	{
		return;
	}
	GameEngineCore::GetContext()->DrawIndexed(IndexBuffer->GetIndexCount(), 0, 0);
}