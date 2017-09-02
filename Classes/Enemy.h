#ifndef _ENEMY_
#define	_ENEMY_
#include "Role.h"
class Enemy :public Role{
public:
	bool init();
	CREATE_FUNC(Enemy);
	Enemy();
	~Enemy();
	void HandAttack();
	void FootAttack();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Wander();
	void BeAttacked(bool A_Direction,int AttackeType,const Item* Weapon);

	void HandAttackEnd();
	void FootAttackEnd();
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
protected:
	void InitEntity(int EnemuState);
	void update(float dt) override;
	void SetDistance();
	void SetCurrent_Position();	
	bool IsInMyRegion();//�ж������Ƿ����ҵĵ���
	bool IsAttackable();//�Ƿ���Խ��й���
	int SkinType;
	int MyRegion;//�ҵĵ���
	Point Moveable_Begin;
	Point Moveable_End;
	int Distance;
	Vec2 Hero_Position;
	int GameModel;
	float Blood_Fuller_YFixed;
};
#endif