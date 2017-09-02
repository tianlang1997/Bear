#include "Role.h"
#include "define.h"
Role::Role(){
	Blood=FULLBLOOD;
	Current_Position=Vec2(0,0);
	LeftOrRight=false;
	ForbidState=RoleState::NONE;
	IsAttack=false;
	CurrentState=RoleState::NONE;
}
Role::~Role(){}