#include "PreCompile.h"
#include "Random_Room.h"
#include "Map_Manager.h"

#include "Player.h"
#include "Dungeon_Map_01.h"
#include "Monster_Place.h"
#include "Boss_Map.h"









std::vector<std::vector<Room_State>> Random_Room::Rooms;

Random_Room::Random_Room()
{
}

Random_Room::~Random_Room()
{
	


}

void Random_Room::Monsers()
{

}

void Random_Room::Start()
{
	Rooms = Rooms;

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
				Rooms[x][y].Room_Number = {static_cast<float>(x),static_cast<float>(y)};
			}
			

		}
	}

	// ���� �־ ������ 
	for (size_t x = 0; x < 9; x++)
	{
		Rooms[x][0].Pos.X += 1280 * static_cast<float>(x);
		Rooms[x][0].Room_Number = { static_cast<float>(x),static_cast<float>(0) };
	}


	




	GameEngineRandom Start_Random;

	Start_Random.SetSeed(5000);
	srand((unsigned)time(NULL));

	//int Start = Start_Random.RandomInt(0, 8); 
	int Start = (rand() % 9);


	//srand((unsigned)time(NULL));
	GameEngineRandom End_Random;
	End_Random.SetSeed(1000);
	//int End = End_Random.RandomInt(0, 8);
	int End = (rand() % 9);

	Rooms[Start][End].RoomCheck = true;




	Player::this_Player->Transform.SetLocalPosition({ Rooms[Start][End].Pos.X,Rooms[Start][End].Pos.Y });
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition({ Rooms[Start][End].Pos.X,Rooms[Start][End].Pos.Y,-1000.0f });


	

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







	// 10�� ����� 
	for (size_t i = 0; i < 10; i++)
	{

		// map ������ ������ 
		Number = Random_Map_Arr[Map_Order];

		/*if (Map_Order == 10)
		{
			Map_Order = 0;
		}*/


		// ��� �波�� �پ��ִ°͵� ���� üũ�� 
		// ù������ �⺻�� �Ѱ��� �������� ������ Rooms[3][8].RoomCheck = true; �̰� ����

		for (size_t x = 0; x < Rooms.size(); x++)
		{
			for (size_t y = 0; y < Rooms[x].size(); y++)
			{
				if (Rooms[x][y].RoomCheck == true) // ������ 
				{
					if (x >= 1) // �迭 ����� �ʰ� �ϱ� ���� ���ǹ� 
					{
						if (Rooms[x - 1][y].RoomCheck == true) //���ʹ�� �����ʹ� �Ѵ� �ִٸ� �������� 
						{
							Rooms[x][y].Arr[static_cast<int>(RandomDir::Left)] = check;
							Rooms[x - 1][y].Arr[static_cast<int>(RandomDir::Right)] = check;
						}
					}
					if (x <= Rooms.size() - 2) //�迭 ����� �ʰ� �ϱ� ���ǹ� 
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
					if (y >= 1)
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
		Start_Random.SetSeed(time(nullptr));


		srand((unsigned)time(NULL));

		int Random = (rand() % RandomCheck);
		//int Random = Random_Map.RandomInt(0, RandomCheck-1);
		RandomCheck = 0;


		// �� �Ѱ� ���� 
		float4 Arr = int_Check[Random];
		Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].RoomCheck = true;

		// ������ �Ǵ� �� 
		if (One_Check == false)
		{
			Map = GetLevel()->CreateActor<Dungeon_Map_01>();
			Map->Map_floor->SetSprite("Floor_01", 0);
			Map->Transform.SetLocalPosition({ Rooms[Start][End].Pos.X,Rooms[Start][End].Pos.Y });
			Map->Pixel_Name = "Dungeon_Map_Pixel_00.png";
			Map->SetArr({ static_cast<float>(Start),static_cast<float>(End) });
			Maps.push_back(Map);
			One_Check = true;
		}






		{
			Map = GetLevel()->CreateActor<Dungeon_Map_01>();
			Map->Map_floor->SetSprite("Floor_01", Number);

			std::string numberStr = std::to_string(Number);
			result = "Dungeon_Map_Pixel_0" + numberStr + ".png";



			Map->Pixel_Name = result.c_str();
			Map->Map_Number += 1;
			Map->Transform.SetLocalPosition(Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].Pos);
			Map->SetArr({ Arr.X,Arr.Y });


			float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();
			GameEngineRandom NewRanadom;

			std::shared_ptr<Monster_Place> Object = GetLevel()->CreateActor<Monster_Place>(ContentsObjectType::Monster);
			Object->sd = { Rooms[static_cast<int>(Arr.X)][static_cast<int>(Arr.Y)].Pos };
			Object->Name = result.c_str();
			Monser_Seed += 1;

			/*	Object->Random_A = Monser_Seed;
				Object->Random_B = Monser_Seed;
				Object->Random_C = Monser_Seed;*/
			Maps.push_back(Map);
		}





		// �ٸ��� �������� ���ؼ� 
		Map_Order++;
	}


	for (size_t i = 1; i < Maps.size(); i++)
	{
		Maps[i]->ReturnCheck = true;
	}

	delete check;

	for (size_t x = 0; x < 9; x++)
	{
		for (size_t y = 0; y < 9; y++)
		{
			if (Rooms[y][x].RoomCheck == true)
			{
				std::shared_ptr<Boss_Map> Object = GetLevel()->CreateActor<Boss_Map>(ContentsObjectType::Monster);
				Object->Transform.SetLocalPosition({ Rooms[y][x].Pos.X, Rooms[y][x].Pos.Y+1143 });
				//Player::this_Player->Transform({ Rooms[y][x].Pos.X, Rooms[y][x].Pos.Y + 1143 });
				/*Player::this_Player->Transform.SetLocalPosition({ Rooms[y][x].Pos.X, Rooms[y][x].Pos.Y + 200 });
				Player::this_Player->Camera = CameraType::BossMap;
				GetLevel()->GetMainCamera()->Transform.SetLocalPosition({ Rooms[y][x].Pos.X, Rooms[y][x].Pos.Y + 500});*/
				return;
			}
			
		}
	}

	

	
}

void Random_Room::Update(float _Delta)
{
	

	
	for (size_t i = 0; i < Maps.size(); i++)
	{
		if (Maps[i]->Door_Left_Collison_Check == true)
		{		
			for (size_t j = 0; j < Maps.size(); j++)
			{
				if (Maps[j]->GetArr().X == Maps[i]->GetArr().X - 1)
				{
					if (Maps[j]->GetArr().Y == Maps[i]->GetArr().Y)
					{
						Maps[j]->ReturnCheck = false;
					}
				}
			}
		}

		if (Maps[i]->Door_Right_Collison_Check == true)
		{
			for (size_t j = 0; j < Maps.size(); j++)
			{
				if (Maps[i]->GetArr().X + 1 == Maps[j]->GetArr().X && Maps[i]->GetArr().Y == Maps[j]->GetArr().Y)
				{
	
					Maps[j]->ReturnCheck = false;
				}
			}
		}

		if (Maps[i]->Door_Top_Collison_Check == true)
		{
			for (size_t j = 0; j < Maps.size(); j++)
			{
				if (Maps[j]->GetArr().Y == Maps[i]->GetArr().Y -1)
				{
					if (Maps[j]->GetArr().X == Maps[i]->GetArr().X)
					{
					

						Maps[j]->ReturnCheck = false;
					}
				}
			}
		}

		if (Maps[i]->Door_Bottom_Collison_Check == true)
		{
			for (size_t j = 0; j < Maps.size(); j++)
			{
				if (Maps[j]->GetArr().Y == Maps[i]->GetArr().Y + 1)
				{
					if (Maps[j]->GetArr().X == Maps[i]->GetArr().X)
					{
						Maps[j]->ReturnCheck = false;
					}
				}
			}
		}
		
	}










	
}

