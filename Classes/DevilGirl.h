#ifndef _DEVIL_GIRL_
#define _DEVIL_GIRL_
#include "Role.h"
class DevilGirl:public Role
{
public:
	bool init();
	CREATE_FUNC(DevilGirl);
	DevilGirl();
	~DevilGirl();
	void FireAttack();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Wander();
	void BeAttacked(bool A_Direction,int AttackeType,const Item* Weapon);

	void FireAttackEnd();
	void MoveUpEnd();
	void MoveDownEnd();
	void MoveLeftEnd();
	void MoveRightEnd();
	void WanderEnd();
	void BeAttackedEnd();

	void SetRegion(const Point& Begin,const Point& End);
	void AddBlood(int Goods);
	void SubBlood(int Hurt);
	int GetBlood();
	void SetSkin(int SkinType);
	void Run();
	void SetHeroPosition(Vec2 Position);//设置主角的位置
	Sprite* GetEntity();
	float GetEntityDepth();
	Sprite* GetAttackEffect();
	void StopMoving();
	bool GetIsAttack();
	void SetGameModel(int Model);
	bool GetDirection();
	int GetCurrentState();
	std::vector<Item*>* GetAliveWeapon();
	void LaunchFire();
protected:
	void InitEntity(int EnemyState);
	void update(float dt) override;
	void SetDistance();
	void SetCurrent_Position();	
	bool IsInMyRegion();//判断主角是否在我的地盘
	bool IsAttackable();//是否可以进行攻击
	int CurrentState;
	int SkinType;
	int MyRegion;//我的地盘
	Point Moveable_Begin;
	Point Moveable_End;
	int Distance;
	Vec2 Hero_Position;
	int GameModel;
	float Blood_Fuller_YFixed;
	std::vector<Item*>* AliveWeapon;//活跃的武器
	PhysicsBody* body;
};

#endif