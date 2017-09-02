#ifndef _Role_
#define _Role_
#include "cocos2d.h"
#include "Item.h"
USING_NS_CC;
class Role:public cocos2d::Layer//�̳���Layer�������Ժ���Ӵ���Ч��
{
	public://ֻ�����Ҫ���ȵķ���
		Role();
		virtual~Role()=0;
		virtual void AddBlood(int Goods)=0;
		virtual void SubBlood(int Hurt)=0;
		virtual int GetBlood()=0;
		virtual Sprite* GetEntity()=0;
		virtual Sprite* GetAttackEffect()=0;
		virtual float GetEntityDepth()=0;
		virtual void StopMoving()=0;
		virtual bool GetIsAttack()=0;
		virtual void BeAttacked(bool A_Direction,int AttackeType,const Item *Weapon)=0;
		virtual bool GetDirection()=0;
		virtual int GetCurrentState()=0;
		virtual std::vector<Item*>* GetAliveWeapon()=0;
	protected:
		Sprite* Entity;
		Sprite*	AttackEffect;
		int Blood;
		int CurrentState;
		bool IsAttack;//����
		bool LeftOrRight;//���� false ; ���� true
		Vec2 Current_Position;
		int Distance;
		int ForbidState;
		ProgressTimer* BloodFuller;
		Sprite* BloodFuller_BG_sprite;
	private:

};

#endif