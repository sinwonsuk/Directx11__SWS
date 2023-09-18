#include "PreCompile.h"
#include "GameEngineShaderResHelper.h"


void GameEngineConstantBufferSetter::Setting()
{

}

void GameEngineConstantBufferSetter::Reset()
{

}

void GameEngineTextureSetter::Setting()
{

}

void GameEngineTextureSetter::Reset()
{

}

void GameEngineSamplerSetter::Setting()
{

}

void GameEngineSamplerSetter::Reset()
{

}


GameEngineShaderResHelper::GameEngineShaderResHelper() 
{
}

GameEngineShaderResHelper::~GameEngineShaderResHelper() 
{
}



void GameEngineShaderResHelper::ShaderResCheck(std::string _FunctionName, ID3DBlob* _CompileCode)
{
	if (nullptr == _CompileCode)
	{
		MsgBoxAssert("������ ���� ���� �ڵ�δ� ���̴��� ���ҽ��� �����Ҽ��� �����ϴ�.");
		return;
	}

	ID3DBlob* BinaryCode = _CompileCode;

	// ���÷����� ���ؼ� ���� ���� �ڵ� ����ü�� ������ �ǹ��Ѵ�.
	// Ŭ���� ����
	// �Լ�
	// Ŭ������ Ÿ��
	// ����� �޾Ҵ���? 
	ID3D11ShaderReflection* CompileInfo = nullptr;

	if (S_OK != D3DReflect(BinaryCode->GetBufferPointer(), BinaryCode->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo)))
	{
		MsgBoxAssert("���̴� ���������� �����߽��ϴ�.");
		return;
	}

	D3D11_SHADER_DESC Info;

	// Info
	// ���� => ����
	// �������� �̹� ������ ���ٰ� + ��尡 �ȴ�. �𸮾� ���� ��쿡�� 
	CompileInfo->GetDesc(&Info);


	

}