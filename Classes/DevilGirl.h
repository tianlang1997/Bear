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
	void SetHeroPosition(Vec2 Position);//�������ǵ�λ��
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
	bool IsInMyRegion();//�ж������Ƿ����ҵĵ���
	bool IsAttackable();//�Ƿ���Խ��й���
	int CurrentState;
	int SkinType;
	int MyRegion;//�ҵĵ���
	Point Moveable_Begin;
	Point Moveable_End;
	int Distance;
	Vec2 Hero_Position;
	int GameModel;
	float Blood_Fuller_YFixed;
	std::vector<Item*>* AliveWeapon;//��Ծ������
	PhysicsBody* body;
};

#endif