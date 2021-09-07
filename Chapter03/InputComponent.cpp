// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner,Vector2 velocity,float mass)
:MoveComponent(owner,velocity,mass)
,mForwardKey(0)
,mBackKey(0)
,mClockwiseKey(0)
,mCounterClockwiseKey(0)
{
	
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	// Calculate forward speed for MoveComponent
	float forwardSpeed = 0.0f;

	Vector2 force = Vector2::Zero;
	if (keyState[mForwardKey])
	{
		//forwardSpeed += mMaxForwardSpeed;
		force = Vector2(50.0f, 50.0f);
	}
	if (keyState[mBackKey])
	{
		//forwardSpeed -= mMaxForwardSpeed;
		force = Vector2(-10.0f, -10.0f);
	}
	//SetForwardSpeed(forwardSpeed);
	AddForce(force);

	// Calculate angular speed for MoveComponent
	float angularSpeed = 0.0f;
	if (keyState[mClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);
}
