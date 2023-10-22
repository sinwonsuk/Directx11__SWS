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

	// 9x9 ���� ���� 
	for (size_t x = 0; x < 9; x++)
	{
		Rooms.reserve(9);
		Rooms.push_back(Room_state);


	    for (size_t y = 0; y< 9; y++)
		{
			Rooms[x].reserve(9); 
			Rooms[x].push_back(state);
		}
	}
	
	// �迭���� transform �� �־��ִ��� 
	for (size_t x = 0; x < 9; x++)
	{

		for (size_t y = 1; y < 9; y++)
		{
			
			Rooms[x][y].Pos.Y += -720*static_cast<float>(y);
			
			if (x >= 1)
			{
				Rooms[x][y].Pos.X += 1280* static_cast<float>(x);
			}
			

		}
	}

	// ���� �־ ������ 
	for (size_t x = 0; x < 9; x++)
	{
		Rooms[x][0].Pos.X += 1280 * static_cast<float>(x);
	}

	// �⺻ ���۸� ��ġ 
	base_Map = GetLevel()->CreateActor<Dungeon_Map_01>();
	base_Map->Transform.SetLocalPosition({ 4480,-6120 }); 
	Rooms[3][8].RoomCheck = true; 


	// nullptr ������ ���� check 
	Room_State* check = new Room_State(); 


	//  �ߺ����� ������ ���� �� �ߺ����� �ϱ� ���� 
	{
		int i, j;
		srand((unsigned)time(NULL));

		for (i = 0; i < 10; i++) 
		{	
			Random_Map_Arr[i] = (rand() % 10) + 1;

			for (j = 0; j < i; j++)
			{
				if (Random_Map_Arr[i] == Random_Map_Arr[j])
				{
					i--;
				}
			}
		}
	}







	// 9�� ����� 
	for (size_t i = 0; i < 9; i++)
	{		

		// map ������ ������ 
		Map = static_cast<RandomMap>(Random_Map_Arr[Map_Order]);



		// ��� �波�� �پ��ִ°͵� ���� üũ�� 
		// ù������ �⺻�� �Ѱ��� �������� ������ Rooms[3][8].RoomCheck = true; �̰� ����

		for (size_t x = 0; x < Rooms.size(); x++)
		{	
			for (size_t y = 0; y < Rooms[x].size(); y++)
			{
				if (Rooms[x][y].RoomCheck == true) // ������ 
				{
					if (x >= 1 ) // �迭 ����� �ʰ� �ϱ� ���� ���ǹ� 
					{
						if (Rooms[x - 1][y].RoomCheck == true) //���ʹ�� �����ʹ� �Ѵ� �ִٸ� �������� 
						{
							Rooms[x][y].Arr[static_cast<int>(RandomDir::Left)] = check;
							Rooms[x - 1][y].Arr[static_cast<int>(RandomDir::Right)] = check;
						}
					}
					if (x <= Rooms.size()-2) //�迭 ����� �ʰ� �ϱ� ���ǹ� 
					{
						if (Rooms[x + 1][y].RoomCheck == true) //���ʹ�� �����ʹ� �Ѵ� �ִٸ� �������� 
						{
							Rooms[x][y].Arr[static_cast<int>(RandomDir::Right)] = check;
							Rooms[x + 1][y].Arr[static_cast<int>(RandomDir::Left)] = check;
						}
					}
						
					
					if (y <= Rooms.size() - 2)
					{
						if (Rooms[x][y + 1].RoomCheck == true)
						{
							Rooms[x][y].Arr[static_cast<int>(RandomDir::Bottom)] = check;
							Rooms[x][y + 1].Arr[static_cast<int>(RandomDir::Top)] = check;
						}
					}
					if(y >= 1)
					{	
						if (Rooms[x][y - 1].RoomCheck == true)
						{
							Rooms[x][y].Arr[static_cast<int>(RandomDir::Top)] = check;
							Rooms[x][y - 1].Arr[static_cast<int>(RandomDir::Bottom)] = check;
						}
					}
				}
			
			}
		}

		// �� ã���Ŀ� nullptr �� �̿��ؼ� 
		// ��� ã�� 

		for (size_t i = 0; i < Rooms.size(); i++)
		{
			for (size_t j = 0; j < Rooms[i].size(); j++)
			{
				if (Rooms[i][j].RoomCheck == true) // ��� �迭�� ���� �ִ°� ã�� 
				{
					
					if (Rooms[i][j].Arr[0] == nullptr) // ���� �������� 4���� nullptr üũ 
					{
						if (i >= 1) // �迭 ����� �ʱ� ���� ���ǹ� 
						{
							if (Rooms[i - 1][j].RoomCheck == false) // ���� �������� nullptr üũ�� �� 
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
					if (Rooms[i][j].RoomCheck == false) // Ȥ�� ���� �ٽ� �� üũ 
					{
						int_Check[RandomCheck] = { static_cast<float>(i) , static_cast<float>(j) };
						RandomCheck++;
					}
				}
			}
		}
		// ��� ���� �������� ���� ��� �߿��� ���� ���� 
		
		GameEngineRandom Random_Map; 
		int Random = Random_Map.RandomInt(0, RandomCheck-1);
		RandomCheck = 0;
		
	
	   // �� �Ѱ� ���� 
		float4 Arr = int_Check[Random]; 
		Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].RoomCheck = true;
		
		

		if (Map == RandomMap::Map_01)
		{
			Map_01 = GetLevel()->CreateActor<Dungeon_Map_01>();
			Map_01->Transform.SetLocalPosition(Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].Pos);
		}
		else if (Map == RandomMap::Map_02)
		{
			Map_02 = GetLevel()->CreateActor<Dungeon_Map_02>();
			Map_02->Transform.SetLocalPosition(Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].Pos);
		}
		else if (Map == RandomMap::Map_03)
		{
			Map_03 = GetLevel()->CreateActor<Dungeon_Map_03>();
			Map_03->Transform.SetLocalPosition(Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].Pos);
		}
		else if (Map == RandomMap::Map_04)
		{
			Map_04 = GetLevel()->CreateActor<Dungeon_Map_04>();
			Map_04->Transform.SetLocalPosition(Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].Pos);
		}

		else if (Map == RandomMap::Map_05)
		{
			Map_05 = GetLevel()->CreateActor<Dungeon_Map_05>();
			Map_05->Transform.SetLocalPosition(Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].Pos);
		}
		else if (Map == RandomMap::Map_06)
		{
			Map_06 = GetLevel()->CreateActor<Dungeon_Map_06>();
			Map_06->Transform.SetLocalPosition(Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].Pos);
		}

		else if (Map == RandomMap::Map_07)
		{
			Map_07 = GetLevel()->CreateActor<Dungeon_Map_07>();
			Map_07->Transform.SetLocalPosition(Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].Pos);
			
		}
		else if (Map == RandomMap::Map_08)
		{
			Map_08 = GetLevel()->CreateActor<Dungeon_Map_08>();
			Map_08->Transform.SetLocalPosition(Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].Pos);
		
		}
		else if (Map == RandomMap::Map_09)
		{
			Map_09 = GetLevel()->CreateActor<Dungeon_Map_09>();
			Map_09->Transform.SetLocalPosition(Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].Pos);
	
		}

		else if (Map == RandomMap::Map_10)
		{
			Map_10 = GetLevel()->CreateActor<Dungeon_Map_10>();
			Map_10->Transform.SetLocalPosition(Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].Pos);
		
		}	
		// �ٸ��� �������� ���ؼ� 
		Map_Order++;

	}

	delete check;

}

void Random_Room::Update(float _Delta)
{
	//for (size_t x = 0; x < 9; x++)
	//{

	//	for (size_t y = 1; y < 9; y++)
	//	{
	//		//Rooms[x][y];
	//	}
	//}
	//int a = 0; 
}
