#ifndef _BEAR_
#define	_BEAR_
#include "Role.h"
class Hero :public Role{
public:
	bool init();
	CREATE_FUNC(Hero);
	Hero();
	~Hero();
	void HandAttack();
	void FootAttack();
	void ThrowAttack();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void JumpUp();
	void SitDown();
	void BeAttacked(bool A_Direction,int AttackeType,const Item *Weapon);

	void HandAttackEnd();
	void FootAttackEnd();
	void ThrowAttackEnd();
	void MoveUpEnd();
	void MoveDownEnd();
	void MoveLeftEnd();
	void MoveRightEnd();
	void JumpUpEnd();
	void SitDownEnd();
	void BeAttackedEnd();

	void SetRegion(const Point& Begin,const Point& End);
	void AddBlood(int Goods);
	void SubBlood(int Hurt);
	int GetBlood();
	Sprite* GetEntity();
	float GetEntityDepth();
	Sprite* GetAttackEffect();
	void StopMoving();
	bool GetIsAttack();
	bool GetDirection();
	int GetCurrentState();
	void AddWeaponList(int WeaponNo);
	void SubWeaponList(int WeaponNo);
	const std::map<int, int>& GetWeaponList();
	bool GotWeapon(int WeaponNo);
	std::vector<Item*>* GetAliveWeapon();
	void LaunchStone();
protected:
	void InitEntity(int HeroState);
	void SetDistance();
	Point Moveable_Begin;
	Point Moveable_End;
	std::map<int, int> WeaponList;
	Label* StoneCount;
	std::vector<Item*>* AliveWeapon;//»îÔ¾µÄÎäÆ÷
};
#endif