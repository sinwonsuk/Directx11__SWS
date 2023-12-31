#include "PreCompile.h"
#include "Boss_Arm.h"
#include "Arm_Shadow.h"
Boss_Arm::Boss_Arm()
{
}

Boss_Arm::~Boss_Arm()
{
}

void Boss_Arm::Start()
{
	Shadow = GetLevel()->CreateActor<Arm_Shadow>();
	Shadow->Off(); 

	Boss_arm = CreateComponent<GameEngineSpriteRenderer>(100);
	Boss_arm->CreateAnimation("Boss1_Punch_1", "Boss1_Punch_1", 0.1f, -1, -1, false);
	Boss_arm->CreateAnimation("Boss1_Punchup", "Boss1_Punchup", 0.1f, -1, -1, false);
	Boss_arm->AutoSpriteSizeOn();
	Boss_arm->SetAutoScaleRatio(2.0f);
	Boss_arm->ChangeAnimation("Boss1_Punch_1");
	Boss_arm->Transform.AddLocalPosition({ 0.0f,20.0f });
	//Boss_arm->AnimationPauseOn();
	Boss_arm->Off(); 

	Boss_arm_Texture = CreateComponent<GameEngineSpriteRenderer>(100);
	Boss_arm_Texture->SetSprite("Boss1_Punch_1", 0);
	Boss_arm_Texture->AutoSpriteSizeOn();
	Boss_arm_Texture->SetAutoScaleRatio(2.0f);
	Boss_arm_Texture->Off(); 
	Boss_arm_Texture->Transform.AddLocalPosition({ 0.0f,20.0f });

	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster_Weapon);
		Col->SetCollisionType(ColType::AABBBOX2D);
		Col->Transform.SetLocalScale({ 50.0f,50.0f });
	}


}

void Boss_Arm::Update(float _Delta)
{
	UpdateState(_Delta);
}

void Boss_Arm::AnimationCheck(const std::string_view& _AnimationName)
{
	Boss_arm->ChangeAnimation(_AnimationName);
}
