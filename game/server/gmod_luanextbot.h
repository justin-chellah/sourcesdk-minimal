#pragma once

#include "NextBot/NextBotGroundLocomotion.h"

class CLuaLocomotion : public NextBotGroundLocomotion
{
public:
    DECLARE_CLASS( CLuaLocomotion, NextBotGroundLocomotion );

    CLuaLocomotion( INextBot* bot ) : NextBotGroundLocomotion( bot ) { }
    virtual ~CLuaLocomotion() { }

    //
    // Locomotion information
    //
    virtual bool IsAbleToJumpAcrossGaps( void ) const override { return m_jumpGapsAllowed; }		// return true if this bot can jump across gaps in its path
    virtual bool IsAbleToClimb( void ) const override { return m_climbAllowed; }				// return true if this bot can climb arbitrary geometry it encounters

    virtual float GetStepHeight( void ) const override { return m_stepHeight; }			// if delta Z is greater than this, we have to jump to get up
    virtual float GetMaxJumpHeight( void ) const override { return m_jumpHeight; }		// return maximum height of a jump
    virtual float GetDeathDropHeight( void ) const override { return m_deathDropHeight; }		// distance at which we will die if we fall

    virtual float GetRunSpeed( void ) const override { return m_runSpeed; }			// get maximum running speed
    virtual float GetWalkSpeed( void ) const override { return m_walkSpeed; }			// get maximum walking speed

    virtual float GetMaxAcceleration( void ) const override { return m_acceleration; }		// return maximum acceleration of locomotor
    virtual float GetMaxDeceleration( void ) const override { return m_deceleration; }		// return maximum deceleration of locomotor

    virtual bool IsAllowedToAvoid( void ) const override { return m_avoidAllowed; }

    virtual float GetGravity( void ) const override { return m_gravity; }					// return gravity force acting on bot
    virtual float GetMaxYawRate( void ) const override { return m_maxYawRate; }				// return max rate of yaw rotation

private:
    float m_runSpeed;
    float m_walkSpeed;
    float m_acceleration;
    float m_deceleration;
    float m_stepHeight;
    float m_jumpHeight;
    float m_deathDropHeight;
    float m_maxYawRate;
    float m_gravity;

    bool m_jumpGapsAllowed;
    bool m_climbAllowed;
    bool m_avoidAllowed;

    void* m_LuaData;
    class CLuaObject* m_LuaLocomotion;
};