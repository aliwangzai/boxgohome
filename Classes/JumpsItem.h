#ifndef __JUMPSITEM_H__
#define __JUMPSITEM_H__

#include "BaseEntity.h"

class JumpsItem : public BaseEntity
{
public:
	JumpsItem();
	~JumpsItem();

	static JumpsItem* create(const ValueMap &valueMap, const ValueMap &gidProperties);

	bool init(const ValueMap &valueMap, const ValueMap &gidProperties);

	bool contactLogicBegin(PhysicsContact &contact, ContactLogic *logic);
	void contactLogicSeperate(PhysicsContact &contact, ContactLogic *logic);
};

#endif