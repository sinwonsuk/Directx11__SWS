#include "PreCompile.h"
#include "Player.h"
#include "Spear.h"

void Player::ChangeState(PlayerState _State)
{
	PlayerState NextState = _State;
	PlayerState PrevState = StateValue;

	StateValue = NextState;

	switch (NextState)
	{
	case PlayerState::Start:
		AnimationCheck("Start");
		break;
	case PlayerState::Start_Stop:
		break;
	case PlayerState::RightIdle:
		AnimationCheck("RightIdle");
		break;
	case PlayerState::LeftIdle:
		AnimationCheck("LeftIdle");
		break;
	case PlayerState::UpIdle:
		AnimationCheck("UpIdle");
		break;
	case PlayerState::DownIdle:
		AnimationCheck("DownIdle");
		break;
	case PlayerState::LeftMove:
		AnimationCheck("LeftMove");
		break;
	case PlayerState::RightMove:
		AnimationCheck("RightMove");
		break;
	case PlayerState::DownMove:
		AnimationCheck("DownMove");
		break;
	case PlayerState::UpMove:
		AnimationCheck("UpMove");
		break;
	case PlayerState::RollDown:
		AnimationCheck("Roll_Down");
		break;
	case PlayerState::RollUp:
		AnimationCheck("Roll_Up");
		break;
	case PlayerState::RollRight:
		AnimationCheck("Roll_Right");
		break;
	case PlayerState::RollLeft:
		AnimationCheck("Roll_Left");
		break;
	case PlayerState::Spear_Down_Attack_01:
		AnimationCheck("Spear_Down_Attack_01");
		break;
	case PlayerState::Spear_Down_Attack_02:
		AnimationCheck("Spear_Down_Attack_02");
		break;
	case PlayerState::Spear_Down_Attack_03:
		AnimationCheck("Spear_Down_Attack_03");
		break;
	case PlayerState::Spear_Left_Attack_01:
		AnimationCheck("Spear_Left_Attack_01");
		break;
	case PlayerState::Spear_Left_Attack_02:
		AnimationCheck("Spear_Left_Attack_02");
		break;
	case PlayerState::Spear_Left_Attack_03:
		AnimationCheck("Spear_Left_Attack_03");
		break;
	case PlayerState::Spear_Right_Attack_01:
		AnimationCheck("Spear_Right_Attack_01");
		break;
	case PlayerState::Spear_Right_Attack_02:
		AnimationCheck("Spear_Right_Attack_02");
		break;
	case PlayerState::Spear_Right_Attack_03:
		AnimationCheck("Spear_Right_Attack_03");
		break;
	case PlayerState::Spear_Up_Attack_01:
		AnimationCheck("Spear_Up_Attack_01");
		break;
	case PlayerState::Spear_Up_Attack_02:
		AnimationCheck("Spear_Up_Attack_02");
		break;
	case PlayerState::Spear_Up_Attack_03:
		AnimationCheck("Spear_Up_Attack_03");
		break;


	}

}

void Player::UpdateState(float _Time)
{

	switch (StateValue)
	{
	case PlayerState::Start:
		StartUpdate(_Time);
		break;
	case PlayerState::Start_Stop:
		StopUpdate(_Time);
		break;
	case PlayerState::RightIdle:
		RightIdleUpdate(_Time);
		break;
	case PlayerState::LeftIdle:
		LeftIdleUpdate(_Time);
		break;
	case PlayerState::UpIdle:
		UpIdleUpdate(_Time);
		break;
	case PlayerState::DownIdle:
		DownIdleUpdate(_Time);
		break;
	case PlayerState::LeftMove:
		LeftMoveUpdate(_Time);
		break;
	case PlayerState::RightMove:
		RightMoveUpdate(_Time);
		break;
	case PlayerState::DownMove:
		DownMoveUpdate(_Time);
		break;
	case PlayerState::UpMove:
		UpMoveUpdate(_Time);
		break;
	case PlayerState::RollDown:
	     Roll_DownUpdate(_Time);
		break;
	case PlayerState::RollUp:
		Roll_UpUpdate(_Time);
		break;
	case PlayerState::RollRight:
		Roll_RightUpdate(_Time);
		break;
	case PlayerState::RollLeft:
		Roll_LeftUpdate(_Time);
		break;
	case PlayerState::Spear_Down_Attack_01:
		Spear_Down_AttackUpdate_01(_Time);
		break;
	case PlayerState::Spear_Down_Attack_02:
		Spear_Down_AttackUpdate_02(_Time);
		break;
	case PlayerState::Spear_Down_Attack_03:
		Spear_Down_AttackUpdate_03(_Time);
		break;
	case PlayerState::Spear_Left_Attack_01:
		Spear_Left_AttackUpdate_01(_Time);
		break;
	case PlayerState::Spear_Left_Attack_02:
		Spear_Left_AttackUpdate_02(_Time);
		break;
	case PlayerState::Spear_Left_Attack_03:
		Spear_Left_AttackUpdate_03(_Time);
		break;
	case PlayerState::Spear_Right_Attack_01:
		Spear_Right_AttackUpdate_01(_Time);
		break;
	case PlayerState::Spear_Right_Attack_02:
		Spear_Right_AttackUpdate_02(_Time);
		break;
	case PlayerState::Spear_Right_Attack_03:
		Spear_Right_AttackUpdate_03(_Time);
		break;
	case PlayerState::Spear_Up_Attack_01:
		Spear_Up_AttackUpdate_01(_Time);
		break;
	case PlayerState::Spear_Up_Attack_02:
		Spear_Up_AttackUpdate_02(_Time);
		break;
	case PlayerState::Spear_Up_Attack_03:
		Spear_Up_AttackUpdate_03(_Time);
		break;

	default:
		break;
	}
}
void Player::StartUpdate(float _Time)
{

	Transform.AddLocalPosition(float4::RIGHT * _Time * StartSpeed);
}

void Player::RightIdleUpdate(float _Time)
{
	if (GameEngineInput::IsPress('A', this))
	{
		ChangeState(PlayerState::LeftMove);
		return; 
	}

	if (GameEngineInput::IsPress('D', this))
	{
		ChangeState(PlayerState::RightMove);
		return;
	}

	if (GameEngineInput::IsPress('W', this))
	{
		ChangeState(PlayerState::UpMove);
		return;
	}

	if (GameEngineInput::IsPress('S', this))
	{
		ChangeState(PlayerState::DownMove);
		return;
	}

	if (GameEngineInput::IsDown('J', this))
	{
		std::shared_ptr<Spear> Object = GetLevel()->CreateActor<Spear>(-100);
		Object->ChangeState(Spear_State::Spear_Right_01);
		ChangeState(PlayerState::Spear_Right_Attack_01);
		return;
	}

	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(PlayerState::RollRight);
		return;
	}
	
}

void Player::LeftIdleUpdate(float _Time)
{
	if (GameEngineInput::IsPress('A', this))
	{
		ChangeState(PlayerState::LeftMove);
		return;
	}

	if (GameEngineInput::IsPress('D', this))
	{
		ChangeState(PlayerState::RightMove);
		return;
	}

	if (GameEngineInput::IsPress('W', this))
	{
		ChangeState(PlayerState::UpMove);
		return;
	}

	if (GameEngineInput::IsPress('S', this))
	{
		ChangeState(PlayerState::DownMove);
		return;
	}

	if (GameEngineInput::IsDown('J', this))
	{
		std::shared_ptr<Spear> Object = GetLevel()->CreateActor<Spear>();
		Object->ChangeState(Spear_State::Spear_Left_01);
		ChangeState(PlayerState::Spear_Left_Attack_01);
		return;
	}
	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(PlayerState::RollLeft);
		return;
	}

}

void Player::DownIdleUpdate(float _Time)
{
	if (GameEngineInput::IsPress('A', this))
	{
		ChangeState(PlayerState::LeftMove);
		return;
	}

	if (GameEngineInput::IsPress('D', this))
	{
		ChangeState(PlayerState::RightMove);
		return;
	}

	if (GameEngineInput::IsPress('W', this))
	{
		ChangeState(PlayerState::UpMove);
		return;
	}

	if (GameEngineInput::IsPress('S', this))
	{
		ChangeState(PlayerState::DownMove);
		return;
	}

	if (GameEngineInput::IsDown('J', this))
	{
		std::shared_ptr<Spear> Object = GetLevel()->CreateActor<Spear>();
		ChangeState(PlayerState::Spear_Down_Attack_01);
		return;
	}
	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(PlayerState::RollDown);
		return;
	}

}

void Player::UpIdleUpdate(float _Time)
{
	if (GameEngineInput::IsPress('A', this))
	{
		ChangeState(PlayerState::LeftMove);
		return;
	}

	if (GameEngineInput::IsPress('D', this))
	{
		ChangeState(PlayerState::RightMove);
		return;
	}

	if (GameEngineInput::IsPress('W', this))
	{
		ChangeState(PlayerState::UpMove);
		return;
	}

	if (GameEngineInput::IsPress('S', this))
	{
		ChangeState(PlayerState::DownMove);
		return;
	}
	if (GameEngineInput::IsDown('J', this))
	{
		std::shared_ptr<Spear> Object = GetLevel()->CreateActor<Spear>();
		Object->ChangeState(Spear_State::Spear_Up_01);
		ChangeState(PlayerState::Spear_Up_Attack_01);
		return;
	}
	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(PlayerState::RollUp);
		return;
	}

}

void Player::RightMoveUpdate(float _Time)
{
	Move(_Time);

	if (GameEngineInput::IsUp('D', this))
	{
		ChangeState(PlayerState::RightIdle);
		return; 
	}

	if (GameEngineInput::IsDown('W', this))
	{
		ChangeState(PlayerState::UpMove);
		return;
	}
	if (GameEngineInput::IsDown('S', this))
	{
		ChangeState(PlayerState::DownMove);
		return;
	}
	if (GameEngineInput::IsDown('A', this))
	{
		ChangeState(PlayerState::LeftMove);
		return;
	}

	if (GameEngineInput::IsDown('J', this))
	{
		std::shared_ptr<Spear> Object = GetLevel()->CreateActor<Spear>();
		Object->ChangeState(Spear_State::Spear_Right_01);
		ChangeState(PlayerState::Spear_Right_Attack_01);
		return;
	}
	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(PlayerState::RollRight);
		return;
	}


}

void Player::LeftMoveUpdate(float _Time)
{


	Move(_Time);

	if (GameEngineInput::IsDown('D', this))
	{
		ChangeState(PlayerState::RightMove);
		return;
	}
	if (GameEngineInput::IsDown('W', this))
	{
		ChangeState(PlayerState::UpMove);
		return;
	}
	if (GameEngineInput::IsDown('S', this))
	{
		ChangeState(PlayerState::DownMove);
		return;
	}
	if (GameEngineInput::IsUp('A', this))
	{
		ChangeState(PlayerState::LeftIdle);
		return;
	}

	if (GameEngineInput::IsDown('J', this))
	{
		std::shared_ptr<Spear> Object = GetLevel()->CreateActor<Spear>();
		Object->ChangeState(Spear_State::Spear_Left_01);
		ChangeState(PlayerState::Spear_Left_Attack_01);
		return;
	}

	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(PlayerState::RollLeft);
		return;
	}
}

void Player::DownMoveUpdate(float _Time)
{
	Move(_Time);

	if (GameEngineInput::IsDown('D', this))
	{
		ChangeState(PlayerState::RightMove);
		return;
	}
	if (GameEngineInput::IsDown('W', this))
	{
		ChangeState(PlayerState::UpMove);
		return;
	}
	if (GameEngineInput::IsUp('S', this))
	{
		ChangeState(PlayerState::DownIdle);
		return;
	}
	if (GameEngineInput::IsDown('A', this))
	{
		ChangeState(PlayerState::LeftMove);
		return;
	}

	if (GameEngineInput::IsDown('J', this))
	{
		std::shared_ptr<Spear> Object = GetLevel()->CreateActor<Spear>();
		ChangeState(PlayerState::Spear_Down_Attack_01);
		return;
	}

	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(PlayerState::RollDown);
		return;
	}
}

void Player::UpMoveUpdate(float _Time)
{
	Move(_Time); 

	if (GameEngineInput::IsDown('D', this))
	{
		ChangeState(PlayerState::DownIdle);
		return;
	}
	if (GameEngineInput::IsUp('W', this))
	{
		ChangeState(PlayerState::UpIdle);
		return;
	}
	if (GameEngineInput::IsDown('S', this))
	{
		ChangeState(PlayerState::DownMove);
		return;
	}
	if (GameEngineInput::IsDown('A', this))
	{
		ChangeState(PlayerState::LeftMove);
		return;
	}

	if (GameEngineInput::IsDown('J', this))
	{
		std::shared_ptr<Spear> Object = GetLevel()->CreateActor<Spear>();
		Object->ChangeState(Spear_State::Spear_Up_01);
		ChangeState(PlayerState::Spear_Up_Attack_01);
		return;
	}
	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(PlayerState::RollUp);
		return;
	}

}

void Player::Roll_RightUpdate(float _Time)
{
	Transform.AddLocalPosition({ float4::RIGHT * Roll_Speed * _Time });

	if (player->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::RightIdle);
		return; 
	}

}

void Player::Roll_LeftUpdate(float _Time)
{
	if (LeftMove == false)
	{
		Transform.AddLocalPosition({ float4::LEFT * Roll_Speed * _Time });
	}
	

	if (player->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::LeftIdle);
		return;
	}
}

void Player::Roll_DownUpdate(float _Time)
{
	if (DownMove == false)
	{
		Transform.AddLocalPosition({ float4::DOWN * Roll_Speed * _Time });
	}
	

	if (player->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::DownIdle);
		return;
	}
}

void Player::Roll_UpUpdate(float _Time)
{
	if (UpMove == false)
	{
		Transform.AddLocalPosition({ float4::UP * Roll_Speed * _Time });
	}
	
	
	

	if (player->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::UpIdle);
		return;
	}
}

void Player::Spear_Down_AttackUpdate_01(float _Time)
{
	WeaponManager(Spear_State::Spear_Down_02, PlayerState::Spear_Down_Attack_02, PlayerState::DownIdle); 
}

void Player::Spear_Down_AttackUpdate_02(float _Time)
{
	WeaponManager(Spear_State::Spear_Down_03, PlayerState::Spear_Down_Attack_03, PlayerState::DownIdle);	
}

void Player::Spear_Down_AttackUpdate_03(float _Time)
{

	if (player->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::DownIdle);
		return;
	}

}

void Player::Spear_Left_AttackUpdate_01(float _Time)
{
	WeaponManager(Spear_State::Spear_Left_02, PlayerState::Spear_Left_Attack_02, PlayerState::LeftIdle);

}

void Player::Spear_Left_AttackUpdate_02(float _Time)
{
	WeaponManager(Spear_State::Spear_Left_03, PlayerState::Spear_Left_Attack_03, PlayerState::LeftIdle);

}

void Player::Spear_Left_AttackUpdate_03(float _Time)
{

	if (player->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::LeftIdle);
		return;
	}


}

void Player::Spear_Right_AttackUpdate_01(float _Time)
{
	WeaponManager(Spear_State::Spear_Right_02, PlayerState::Spear_Right_Attack_02, PlayerState::RightIdle);

}

void Player::Spear_Right_AttackUpdate_02(float _Time)
{
	WeaponManager(Spear_State::Spear_Right_03, PlayerState::Spear_Right_Attack_03, PlayerState::RightIdle);

}

void Player::Spear_Right_AttackUpdate_03(float _Time)
{

	if (player->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::RightIdle);
		return;
	}

}

void Player::Spear_Up_AttackUpdate_01(float _Time)
{
	WeaponManager(Spear_State::Spear_Up_02, PlayerState::Spear_Up_Attack_02, PlayerState::UpIdle);

}

void Player::Spear_Up_AttackUpdate_02(float _Time)
{
	WeaponManager(Spear_State::Spear_Up_03, PlayerState::Spear_Up_Attack_03, PlayerState::UpIdle);
}

void Player::Spear_Up_AttackUpdate_03(float _Time)
{

	if (player->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::UpIdle);
		return;
	}

}

void Player::WeaponManager(Spear_State _SpearState, PlayerState state , PlayerState _playstate)
{
	


	if (player->GetCurIndex() > 1)
	{
		if (GameEngineInput::IsDown('J', this))
		{
			AttackCheck = true;
		}
	}


	if (AttackCheck == true && player->IsCurAnimationEnd())
	{
		std::shared_ptr<Spear> Object = GetLevel()->CreateActor<Spear>();
		Object->ChangeState(_SpearState);
		AttackCheck = false;
		ChangeState(state);
		return;
	}

	else if (player->IsCurAnimationEnd())
	{
		ChangeState(_playstate);
		return;
	}


}





void Player::Move(float _Delta)
{
	switch (Camera)
	{
	case CameraType::None:

		if (GameEngineInput::IsPress('A', this) && LeftMove == true)
		{
			Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
		}

		if (GameEngineInput::IsPress('D', this) && RightMove == true)
		{
			Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
		}

		if (GameEngineInput::IsPress('W', this) && UpMove == true)
		{
			Transform.AddLocalPosition(float4::UP * _Delta * Speed);
		}

		if (GameEngineInput::IsPress('S', this) && DownMove == true)
		{
			Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
		}
		break;

	case CameraType::Town:

		if (GameEngineInput::IsPress('A', this) && LeftMove == true)
		{
			Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);

			if (Transform.GetLocalPosition().X >= 0 && Transform.GetLocalPosition().X <= 1280)
			{
				GetLevel()->GetMainCamera()->Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
			}
		}

		if (GameEngineInput::IsPress('D', this) && RightMove == true)
		{
			Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);

			   if (Transform.GetLocalPosition().X <= 1280 && Transform.GetLocalPosition().X >= 0)
			   {
			   	GetLevel()->GetMainCamera()->Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
			   }

		}

		if (GameEngineInput::IsPress('W', this) && UpMove == true)
		{
			Transform.AddLocalPosition(float4::UP * _Delta * Speed);

			if (Transform.GetLocalPosition().Y <= 330 && Transform.GetLocalPosition().Y >= -1043)
			{
				GetLevel()->GetMainCamera()->Transform.AddLocalPosition(float4::UP * _Delta * Speed);
			}

		}

		if (GameEngineInput::IsPress('S', this) && DownMove == true)
		{
			Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);

			
			if (Transform.GetLocalPosition().Y >= -1043 && Transform.GetLocalPosition().Y <= 330)
			{
			   GetLevel()->GetMainCamera()->Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
			}	
		}



		break;
	case CameraType::Dungeon_Entrance:
	{
		if (GameEngineInput::IsPress('A', this) && LeftMove == true)
		{
			Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);

			//GetLevel()->GetMainCamera()->Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
			if (Transform.GetLocalPosition().X >= 649 && Transform.GetLocalPosition().X <= 1745)
			{
				GetLevel()->GetMainCamera()->Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
			}
		}

		if (GameEngineInput::IsPress('D', this) && RightMove == true)
		{
			Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);

			//GetLevel()->GetMainCamera()->Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);

			if (Transform.GetLocalPosition().X <= 1745 && Transform.GetLocalPosition().X >= 649)
			{
				GetLevel()->GetMainCamera()->Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
			}

		}

		if (GameEngineInput::IsPress('W', this) && UpMove == true)
		{
			Transform.AddLocalPosition(float4::UP * _Delta * Speed);

			//GetLevel()->GetMainCamera()->Transform.AddLocalPosition(float4::UP * _Delta * Speed);

			if (Transform.GetLocalPosition().Y <= -485 && Transform.GetLocalPosition().Y >= -1599)
			{
				GetLevel()->GetMainCamera()->Transform.AddLocalPosition(float4::UP * _Delta * Speed);
			}

		}

		if (GameEngineInput::IsPress('S', this) && DownMove == true)
		{
			Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
			//GetLevel()->GetMainCamera()->Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
			if (Transform.GetLocalPosition().Y >= -1599 && Transform.GetLocalPosition().Y <= -485)
			{
				GetLevel()->GetMainCamera()->Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
			}
		}
	}
		break;
	default:
		break;
	}
		

		
	
}




void Player::StopUpdate(float _Time)
{
	if (player->IsCurAnimationEnd())
	{
		ChangeState(PlayerState::RightIdle);
		return; 
	}
}