#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer;

protected:
	void Start() override;

private:
};

