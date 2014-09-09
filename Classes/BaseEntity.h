#ifndef __WALLSPRITE_H__
#define __WALLSPRITE_H__

#include "cocos2d.h"
USING_NS_CC;

enum EntityType
{
	Type_Normal,
	Type_Broken,
	Type_Brokable,
	Type_Yellow,
	Type_Flag,
	Type_Wood,
	Type_Enemy,
	Type_Item_Jump_3
};

class ContactLogic;
class BaseEntity: public Sprite
{
public:
	BaseEntity();
	virtual ~BaseEntity();

	bool initWithMap(const ValueMap &valueMap );

	void setContactTestBitmask(int mask);
	void setCategoryBitmask(int mask);
	void setCollisionBitmask(int mask);

	virtual bool contactLogicBegin(PhysicsContact &contact, ContactLogic *logic){ return true; };
	virtual void contactLogicSeperate(PhysicsContact &contact, ContactLogic *logic){};

	EntityType getEntityType() const { return m_entityType; }

	void setEntityType(EntityType typ);
	void setPositionAndRotation();
protected:
	int			 m_nGid;
	int			 m_nType;
	std::string	 m_sName;
	Point		 m_initPos;
	float		 m_rotation;
	EntityType     m_entityType;
};

#endif