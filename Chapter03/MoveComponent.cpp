// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MoveComponent.h"
#include "Actor.h"


MoveComponent::MoveComponent(Actor* owner, Vector2 velocityLimit, float mass, int updateOrder) 
	:Component(owner, updateOrder)
, mAngularSpeed(0.0f)
, mForwardSpeed(0.0f)
, mMass(mass)
, mVelocityLimit(velocityLimit)
{

}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rot);
	}
	
	if (!Math::NearZero(mForwardSpeed))
	{
		// 力の合計から加速度
		mAcceleration = mSumOfForce * (1.0f / mMass);
		// 加速度から速度
		mVelocity += mAcceleration * deltaTime;
		//力の合計リセット
		mSumOfForce = Vector2::Zero;

		//速度上限を超えないようにする
		if (sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y) > sqrt(mVelocityLimit.x * mVelocityLimit.x + mVelocityLimit.y * mVelocityLimit.y)) {
			mVelocity = mVelocityLimit;
		}

		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mVelocity * deltaTime;
		
		// (Screen wrapping code only for asteroids)
		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		mOwner->SetPosition(pos);
	}
}

void MoveComponent::AddForce(Vector2 force)
{
	mSumOfForce += force;
}

