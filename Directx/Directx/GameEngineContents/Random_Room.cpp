#include "PreCompile.h"
#include "Random_Room.h"
#include "Map_Manager.h"

#include "Dungeon_Map_01.h"
#include "Dungeon_Map_02.h"
#include "Dungeon_Map_03.h"
#include "Dungeon_Map_04.h"
#include "Dungeon_Map_05.h"
#include "Dungeon_Map_06.h"
#include "Dungeon_Map_07.h"
#include "Dungeon_Map_08.h"
#include "Dungeon_Map_09.h"
#include "Dungeon_Map_10.h"
Random_Room::Random_Room()
{
}

Random_Room::~Random_Room()
{
}

void Random_Room::Start()
{
	Room_State state;
	for (size_t x = 0; x < 9; x++)
	{
		
		Rooms.push_back(Room_state);

	    for (size_t y = 0; y< 9; y++)
		{
			Rooms[x].push_back(state);
		}
	}

	Rooms[0][8].RoomCheck = true; 


	
	Room_State* check = new Room_State(); 



	for (size_t i = 0; i < 9; i++)
	{
		// �ϴ� �������� �� ������ 
		
			GameEngineRandom random;
			int d = random.RandomInt(0, 9);
			Map = static_cast<RandomMap>(0);
			switch (Map)
			{
			case RandomMap::Map_01:
			{
				Map_01 = GetLevel()->CreateActor<Dungeon_Map_01>(); 
				break;
			}
			case RandomMap::Map_02:
				Map_02 = GetLevel()->CreateActor<Dungeon_Map_02>();
				break;
			case RandomMap::Map_03:
				Map_03 = GetLevel()->CreateActor<Dungeon_Map_03>();
				break;
			case RandomMap::Map_04:
				Map_04 = GetLevel()->CreateActor<Dungeon_Map_04>();
				break;
			case RandomMap::Map_05:
				Map_05 = GetLevel()->CreateActor<Dungeon_Map_05>();
				break;
			case RandomMap::Map_06:
				Map_06 = GetLevel()->CreateActor<Dungeon_Map_06>();
				break;
			case RandomMap::Map_07:
				Map_07 = GetLevel()->CreateActor<Dungeon_Map_07>();
				break;
			case RandomMap::Map_08:
				Map_08 = GetLevel()->CreateActor<Dungeon_Map_08>();
				break;
			case RandomMap::Map_09:
				Map_09 = GetLevel()->CreateActor<Dungeon_Map_09>();
				break;
			case RandomMap::Map_10:
				Map_10 = GetLevel()->CreateActor<Dungeon_Map_10>();
				break;
			default:
				break;
			}
		

		// ��� �波�� �پ��ִ°͵� ���� üũ�� 
		for (size_t i = 0; i < Rooms.size(); i++)
		{	
			

			for (size_t j = 0; j < Rooms[i].size(); j++)
			{
				if (Rooms[i][j].RoomCheck == true)
				{
					if (i >= 1 )
					{
						if (Rooms[i - 1][j].RoomCheck == true)
						{
							Rooms[i][j].Arr[static_cast<int>(RandomDir::Left)] = check;
							Rooms[i - 1][j].Arr[static_cast<int>(RandomDir::Right)] = check;
						}
					}
					if (i <= Rooms.size()-2)
					{
						if (Rooms[i + 1][j].RoomCheck == true)
						{
							Rooms[i][j].Arr[static_cast<int>(RandomDir::Right)] = check;
							Rooms[i + 1][j].Arr[static_cast<int>(RandomDir::Left)] = check;
						}
					}
						
					
					if (j <= Rooms.size() - 2)
					{
						if (Rooms[i][j + 1].RoomCheck == true)
						{
							Rooms[i][j].Arr[static_cast<int>(RandomDir::Bottom)] = check;
							Rooms[i][j + 1].Arr[static_cast<int>(RandomDir::Top)] = check;
						}
					}
					if(j >= 1)
					{	
						if (Rooms[i][j - 1].RoomCheck == true)
						{
							Rooms[i][j].Arr[static_cast<int>(RandomDir::Top)] = check;
							Rooms[i][j - 1].Arr[static_cast<int>(RandomDir::Bottom)] = check;
						}
					}
				}
			
			}
		}

		// ���� �پ��ִ°� ã���� 
		// �׷��� �پ��ִ� ���߿� ��� �˼� ���� 
		for (size_t i = 0; i < Rooms.size(); i++)
		{
			for (size_t j = 0; j < Rooms[i].size(); j++)
			{
				if (Rooms[i][j].RoomCheck == true)
				{
					
					if (Rooms[i][j].Arr[0] == nullptr)
					{
						if (i >= 1)
						{
							if (Rooms[i - 1][j].RoomCheck == false)
							{
								Rooms[i - 1][j].Null_Check = true;
							}
						}
					
					}
					if (Rooms[i][j].Arr[1] == nullptr)
					{
						if (i <= 7)
						{
							if (Rooms[i + 1][j].RoomCheck == false)
							{
								Rooms[i + 1][j].Null_Check = true;
							}
						}
						
					}
					if (Rooms[i][j].Arr[2] == nullptr)
					{
						if (j >= 1)
						{
							if (Rooms[i][j - 1].RoomCheck == false)
							{
								Rooms[i][j - 1].Null_Check = true;
							}
						}
						
					}
					if (Rooms[i][j].Arr[3] == nullptr)
					{
						if (j <= 7)
						{
							if (Rooms[i][j + 1].RoomCheck == false)
							{
								Rooms[i][j + 1].Null_Check = true;
							}
						}
						
					}			
				}
			}
		}

		// �پ��ִ°��� ��� ã������ ������ �������� �Ѱ� ���ؾ��� 

		for (size_t i = 0; i < Rooms.size(); i++)
		{

			for (size_t j = 0; j < Rooms[i].size(); j++)
			{
				if (Rooms[i][j].Null_Check == true)
				{
					if (Rooms[i][j].RoomCheck == false)
					{
						int_Check[RandomCheck] = { static_cast<float>(i) , static_cast<float>(j) };
						RandomCheck++;
					}
				}
			}
		}
		// �پ��ִ¹� ���� �������� ���� ���� ���� 
		GameEngineRandom Random_Map; 

		int Random = Random_Map.RandomInt(0, RandomCheck-1);

		RandomCheck = 0;

		// �迭�� �� �Ѱ� ���� 
		float4 Arr = int_Check[Random]; 

		Rooms[Arr.X][Arr.Y].RoomCheck = true; 
		
		// 9x9 �迭���� �������� �߳��� ���� 9x9 �迭���� transform�� ���� ������ 

	

	}

	delete check;
	int a = 0;
}

void Random_Room::Update(float _Delta)
{
}
