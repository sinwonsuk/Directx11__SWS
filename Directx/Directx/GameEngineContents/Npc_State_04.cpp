#include "PreCompile.h"
#include "NPC.h"
#include "Npc_Manager.h"

#include "Emoticon.h"
#include "Shop_UI.h"
#include "Shop_Item.h"
#include "Player.h"
#include "Player_UI.h"
#include "Inventory.h"

void Npc::UpdateState_04(float _Time)
{

	switch (StateValue)
	{
	case Npc_State::Start:
		StartUpdate_04(_Time);
		break;
	case Npc_State::RightIdle:
		RightIdleUpdate_04(_Time);
		break;
	case Npc_State::LeftIdle:
		LeftIdleUpdate_04(_Time);
		break;
	case Npc_State::UpIdle:
		UpIdleUpdate_04(_Time);
		break;
	case Npc_State::DownIdle:
		DownIdleUpdate_04(_Time);
		break;
	case Npc_State::LeftMove:
		LeftMoveUpdate_04(_Time);
		break;
	case Npc_State::RightMove:
		RightMoveUpdate_04(_Time);
		break;
	case Npc_State::DownMove:
		DownMoveUpdate_04(_Time);
		break;
	case Npc_State::UpMove:
		UpMoveUpdate_04(_Time);
		break;
	default:
		break;
	}
}


void Npc::StartUpdate_04(float _Time)
{
	float4 Dir = { 695.000000,-640 };
	float4 Dir2 = { 580.5,-538 };

	float4 Dir3 = Dir - Dir2;
	Dir3.Normalize();

	Transform.AddLocalPosition({ Dir3 * _Time * Speed });

}

void Npc::RightIdleUpdate_04(float _Time)
{


}

void Npc::LeftIdleUpdate_04(float _Time)
{
	Time += _Time;

	if (Time > 1)
	{


		Time = 0;
		ChangeState(Npc_State::RightMove);
		return;
	}

}

void Npc::DownIdleUpdate_04(float _Time)
{

	Time += _Time;

	if (Time > 4.5)
	{
		Shop_UI::this_Shop_UI->Shop_Item_01->Off();

		Shop_UI::this_Shop_UI->Item_Renders[21]->item->Death();
		Shop_UI::this_Shop_UI->Font_Renders[21]->Font->Death();

		Shop_UI::this_Shop_UI->Item_Renders[21] = nullptr;
		Shop_UI::this_Shop_UI->Font_Renders[21] = nullptr;
		Time = 0;
		ChangeState(Npc_State::RightMove);
		return;
	}


	if (Col->Collision(ContentsCollisionType::Open_Col))
	{

		Number -= _Time * 2;

		npc->GetColorData().MulColor = { 1,1,1,Number };

		int a = 0;

		if (Number <= 0.2)
		{
			this->Death();
		}

	}


}

void Npc::UpIdleUpdate_04(float _Time)
{
	Col_Deal->On();

	if (Col_Deal->Collision(ContentsCollisionType::Player))
	{
		if (GameEngineInput::IsDown('E', this))
		{
			Sound = GameEngineSound::SoundPlay("shop_item_sold.wav");

			Col_Deal->Off();
			Player_UI::gold += Shop_UI::this_Shop_UI->Shop_Item_01->Get_Money();

			
			ChangeState(Npc_State::DownMove);
			return;
		}
	}


}

void Npc::RightMoveUpdate_04(float _Time)
{
	/*Col->CollisionEvent(ContentsCollisionType::NPC, { .Enter = [&](class GameEngineCollision* _This,class GameEngineCollision* _collisions)
		{
			Npc* npc2 = dynamic_cast<Npc*>(_collisions->GetActor());
			npc2->test = true;

			Npc* npc = dynamic_cast<Npc*>(_This->GetActor());

			npc->test = false;

	} });*/




	if (Transform.GetWorldPosition().X < 576)
	{
		Transform.AddLocalPosition({ float4::RIGHT * _Time * Speed });
	}

	if (Transform.GetWorldPosition().X > 576)
	{
		if (Transform.GetWorldPosition().X <= 615)
		{
			float4 Dir = { 585.9f,-485.0f };
			float4 Dir2 = { 624,-561 };
			float4 Dir3 = Dir2 - Dir;
			Dir3.Normalize();
			Transform.AddLocalPosition({ Dir3 * _Time * Speed });
		}	
	}

	if (Transform.GetWorldPosition().X > 615)
	{
		Transform.AddLocalPosition({ float4::RIGHT * _Time * Speed });
	}

	if (Transform.GetWorldPosition().X > 684)
	{
		ChangeState(Npc_State::UpIdle);
		return;
	}

	
}

void Npc::LeftMoveUpdate_04(float _Time)
{
	
	if (Check == 0)
	{
		float4 Dir = { 695,-640 };
		float4 Dir2 = { 580.5,-538 };
		float4 Dir3 = Dir2 - Dir;
		Dir3.Normalize();

		Transform.AddLocalPosition({ Dir3 * _Time * Speed });

		if (Transform.GetWorldPosition().X < 582)
		{
			Check++;
			ChangeState(Npc_State::UpMove);
			return;
		}

	}




	if (Check == 1)
	{
		Transform.AddLocalPosition({ float4::LEFT * _Time * Speed });

		if (Transform.GetWorldPosition().X < 480)
		{
			std::shared_ptr<Emoticon> Object = GetLevel()->CreateActor<Emoticon>();
			Object->Transform.SetWorldPosition({ Transform.GetWorldPosition().X + 30,Transform.GetWorldPosition().Y + 40.0f });

			ChangeState(Npc_State::DownIdle);
			return;
		}
	}

	
}

void Npc::DownMoveUpdate_04(float _Time)
{
	Transform.AddLocalPosition({ float4::DOWN * _Time * Speed });

	if (Transform.GetWorldPosition().Y < -640)
	{
		ChangeState(Npc_State::DownIdle);
		return;
	}

}

void Npc::UpMoveUpdate_04(float _Time)
{
	Transform.AddLocalPosition({ float4::UP * _Time * Speed });

	if (Transform.GetWorldPosition().Y > -438)
	{
		ChangeState(Npc_State::LeftMove);
		return;
	}
}