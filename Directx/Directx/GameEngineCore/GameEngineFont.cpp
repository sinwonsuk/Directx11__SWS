#include "PreCompile.h"
#include "GameEngineFont.h"

IFW1Factory* GameEngineFont::Factory = nullptr;

class FontFactoryCreator
{
public:
	FontFactoryCreator()
	{
		FW1CreateFactory(FW1_VERSION, &GameEngineFont::Factory);
	}

	~FontFactoryCreator()
	{
		if (nullptr != GameEngineFont::Factory)
		{
			// �ٽ� ����Ҷ� ����ִٴ°��� �˷��ֱ� ���ؼ�
			// ���α׷��� ����ɶ� �Ǵ°�.
			GameEngineFont::Factory->Release();
			GameEngineFont::Factory = nullptr;
		}
	}
};

FontFactoryCreator InitFont;

GameEngineFont::GameEngineFont() 
{
}

GameEngineFont::~GameEngineFont() 
{
	if (nullptr != Font)
	{
		Font->Release();
		Font = nullptr;
	}
}



void GameEngineFont::ResLoad(const std::string_view& _Path)
{
	// ���� �߰��� �ʿ��ϴ�.

	std::wstring WPath = GameEngineString::AnsiToUnicode(_Path);

	if (S_OK != GameEngineFont::Factory->CreateFontWrapper(GameEngineCore::GetDevice(), WPath.c_str(), &Font))
	{
		MsgBoxAssert("��Ʈ ���� ����");
	}
}