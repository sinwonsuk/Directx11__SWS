#pragma once
#include <GameEngineCore/AStartPathFinder.h>

// ���� :
class TileMap : public GameEngineActor
{
public:
	static TileMap* Map;
	// constrcuter destructer
	TileMap();
	~TileMap();

	// delete Function
	TileMap(const TileMap& _Other) = delete;
	TileMap(TileMap&& _Other) noexcept = delete;
	TileMap& operator=(const TileMap& _Other) = delete;
	TileMap& operator=(TileMap&& _Other) noexcept = delete;

	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 }, std::string_view _Name = {});
	GameEngineColor Player_GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 }, std::string_view _Name = {});

	float4 ConvertWorldPosToTilePoint(float4 _Pos);

	float4 ConvertTilePointToWorldPos(PathPoint _Point);

     bool IsBlock(float4 _Pos, std::string_view _Name);
	 bool test(int X, int Y);
	 bool IsBlock(int X, int Y, std::string_view _Name);

	 std::list<float4> GetPath(const float4& Start, const float4& End,std::string_view _Name);

	std::list<float4> GetPath(int _StartX, int _StartY, int _EndX, int _EndY, std::string_view _Name);

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	
	AStartPathFinder PathFind;
	std::string name = {};
	std::shared_ptr<class GameEngineSpriteRenderer> Pixel;
	std::vector<std::vector<bool>> Tile_Maps;
	std::vector<bool> Tile_Map;

};