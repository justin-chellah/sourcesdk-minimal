#pragma once

#include "NextBotGroundLocomotion.h"
#include "NextBotBodyInterface.h"
#include "NextBot.h"
#include "NextBotBehavior.h"

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

class CLuaNextBotBody : public IBody
{
public:
    CLuaNextBotBody( INextBot* bot );
    virtual ~CLuaNextBotBody() { }

    virtual void Update( void ) override;

    /**
     * Begin an animation activity, return false if we cant do that right now.
     */
    virtual bool StartActivity( Activity act, unsigned int flags = 0 ) override;

    virtual Activity GetActivity( void ) const override;							// return currently animating activity
    virtual bool IsActivity( Activity act ) const override;						    // return true if currently animating activity matches the given one

    virtual float GetHullWidth( void ) const override;							    // width of bot's collision hull in XY plane
    virtual float GetHullHeight( void ) const override;							    // height of bot's current collision hull based on posture
    virtual float GetStandHullHeight( void ) const override;					    // height of bot's collision hull when standing
    virtual const Vector& GetHullMins( void ) const override;					    // return current collision hull minimums based on actual body posture
    virtual const Vector& GetHullMaxs( void ) const override;					    // return current collision hull maximums based on actual body posture

    virtual unsigned int GetSolidMask( void ) const override;					    // return the bot's collision mask (hack until we get a general hull trace abstraction here or in the locomotion interface)
    virtual unsigned int GetCollisionGroup( void ) const override;
};

class CLuaNextBotVision : public IVision
{
public:
    CLuaNextBotVision( CLuaNextBot* bot );
    virtual ~CLuaNextBotVision() { }

    virtual float GetMaxVisionRange( void ) const;

    virtual void SetMaxVisionRange( float );
};

class CLuaNextBot : public NextBotCombatCharacter
{
public:
    DECLARE_CLASS( CLuaNextBot, NextBotCombatCharacter );
    DECLARE_SERVERCLASS();

    CLuaNextBot();
    virtual ~CLuaNextBot();

    virtual bool ShouldCollide( int collisionGroup, int contentsMask ) const;

    virtual void Spawn( void );

    virtual bool KeyValue( const char* szKeyName, const char* szValue );

    virtual int	ObjectCaps( void );
    virtual bool AcceptInput( const char* szInputName, CBaseEntity* pActivator, CBaseEntity* pCaller, variant_t Value, int outputID );

    virtual void OnRestore();

    virtual void TraceAttack( const CTakeDamageInfo& info, const Vector& vecDir, trace_t* ptr, CDmgAccumulator* pAccumulator = NULL );
    virtual int OnTakeDamage( const CTakeDamageInfo& info );

    virtual void UpdateOnRemove( void );

    virtual bool UsesLua();
    virtual void SetUseType( int );
    virtual const char* GetLuaScriptName();
    virtual void InitializeScriptedEntity( const char* );
    virtual void Lua_OnEntityInitialized();
    virtual CLuaNextBot* GetNextBot();
    virtual void* Lua_GetLuaClass();
    virtual void GMOD_CreateBoneFollowers( int, const char** );
    virtual void GMOD_UpdateBoneFollowers();
    virtual void GMOD_DestroyBoneFollowers();
    virtual CBoneFollowerManager* GMOD_GetBoneFollowerMgr();

    virtual void HandleAnimEvent( animevent_t* pEvent );

    virtual bool IsRemovedOnReset( void ) const;

    // INextBot
    DECLARE_INTENTION_INTERFACE( CLuaNextBot )
    virtual CLuaLocomotion *GetLocomotionInterface( void ) const;
    virtual CLuaNextBotBody *GetBodyInterface( void ) const;
    virtual CLuaNextBotVision *GetVisionInterface( void ) const;
};

inline CLuaNextBotVision::CLuaNextBotVision( CLuaNextBot* bot ) : IVision( bot )
{
}