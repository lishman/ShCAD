
#ifndef _SHMODIFYACTION_H
#define _SHMODIFYACTION_H

#include "ActionHandler\ShActionHandler.h"

class ShModifyAction : public ShActionHandler {

public:
	ShModifyAction(ShCADWidget *widget);
	virtual ~ShModifyAction() = 0;

	virtual void finishSelectingEntities() = 0;

protected:
	virtual void triggerSelectingEntities(QMouseEvent *event);

protected:
	virtual void selectFoundEntity(ShEntity *foundEntity, Qt::KeyboardModifiers modifier);

};

#endif //_SHMODIFYACTION_H