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

void GameEngineFont::FontDraw(const std::string& _Text, float _FontScale,const float4& _Pos, const float4& _Color, FW1_TEXT_FLAG _Flag)
{
	std::wstring Text = GameEngineString::AnsiToUnicode(_Text);

	FontDraw(Text, _FontScale, _Pos, _Color, _Flag);
}

void GameEngineFont::FontDraw(const std::wstring& _Text, float _FontScale, const float4& _Pos, const float4& _Color, FW1_TEXT_FLAG _Flag)
{
	Font->DrawString(GameEngineCore::GetContext(), _Text.c_str(), _FontScale, _Pos.X, _Pos.Y, _Color.ColorToUint(), _Flag);
}