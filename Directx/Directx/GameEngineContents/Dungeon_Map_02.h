#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Map_Manager.h"

class Dungeon_Map_02 : public GameEngineActor, public Map_Manager
{
public:
	// constrcuter destructer
	Dungeon_Map_02();
	~Dungeon_Map_02();

	// delete Function
	Dungeon_Map_02(const Dungeon_Map_02& _Other) = delete;
	Dungeon_Map_02(Dungeon_Map_02&& _Other) noexcept = delete;
	Dungeon_Map_02& operator=(const Dungeon_Map_02& _Other) = delete;
	Dungeon_Map_02& operator=(Dungeon_Map_02&& _Other) noexcept = delete;




protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float Map_Number = 0.0f;
	std::shared_ptr<class GameEngineSpriteRenderer> BackGround;
	std::shared_ptr<class GameEngineSpriteRenderer> Map_floor_01;
	std::shared_ptr<class GameEngineSpriteRenderer> LeftDoor;
	std::shared_ptr<class GameEngineSpriteRenderer> RightDoor;
	std::shared_ptr<class GameEngineSpriteRenderer> Scroll;
	std::shared_ptr<GameEngineCollision> Right_Collision_Door;

};
