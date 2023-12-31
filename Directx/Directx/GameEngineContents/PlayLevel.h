#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;
	GameEngineSoundPlayer Bgm;

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	
	std::shared_ptr<class CameraCollision> Camera;
	std::shared_ptr<GameEngineCollision> Col;
	std::shared_ptr<class Random_Room> Map;
	std::shared_ptr<class Player> player;
	std::shared_ptr<class Inventory> adad;
};

