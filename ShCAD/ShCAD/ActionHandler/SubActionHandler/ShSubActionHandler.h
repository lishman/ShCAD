

#ifndef _SHSUBACTIONHANDLER_H
#define _SHSUBACTIONHANDLER_H

#include "ShVariable.h"
#include "ShPoint.h"

class QMouseEvent;
class ShGraphicView;
class ShActionHandler;
class QPainter;

class ShSubActionInfo {
	friend class ShSubActionDecorator_SnapMode;
	friend class ShSubActionDecorator_Orthogonal;
	friend class ShSubLineDecorator_SnapMode_Perpendicular;

private:
	ShPoint3d point;
	bool isSnapModeOn;
	bool isSnapPointClicked;
	ObjectSnap clickedObjectSnap;
	bool isOrthogonalModeOn;
	DrawType drawType;

public:
	ShSubActionInfo();
	ShSubActionInfo(DrawType drawType);
	~ShSubActionInfo();

	inline ShPoint3d GetPoint() const { return this->point; }
	void SetPoint(const ShPoint3d& point) { this->point = point; }
	inline bool IsSnapModeOn() const { return this->isSnapModeOn; }
	inline bool IsOrthogonalModeOn() const { return this->isOrthogonalModeOn; }
	inline bool IsSnapPointClicked() const { return this->isSnapPointClicked; }
	void SetDrawType(DrawType drawType) { this->drawType = drawType; }
	inline DrawType GetDrawType() const { return this->drawType; }
	inline ObjectSnap GetClickedObjectSnap() const { return this->clickedObjectSnap; }
};

class ShSubActionDecorator;
class ShSubActionHandler {

protected:
	ShActionHandler *actionHandler;
	ShGraphicView *view;
	ShSubActionDecorator *parent;

public:
	ShSubActionHandler(ShActionHandler *actionHandler, ShGraphicView *view);
	virtual ~ShSubActionHandler() = 0;

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo &info) = 0;
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info) = 0;

	virtual void Draw(QPainter *painter) = 0;
	virtual void Decorate(ShSubActionDecorator *decorator) = 0;
	
	void SetParent(ShSubActionDecorator *parent) { this->parent = parent; }

};

//all individual subAction such as subLine,subCircle.. etc
//must inherit this class.
class ShSubIndividualAction : public ShSubActionHandler {

public:
	ShSubIndividualAction(ShActionHandler *actionHandler, ShGraphicView *view);
	virtual ~ShSubIndividualAction() = 0;

	virtual void Draw(QPainter *painter) {}
	virtual void Decorate(ShSubActionDecorator *decorator);

};

class ShSubActionDecorator : public ShSubActionHandler {

protected:
	ShSubActionHandler *child;

public:
	ShSubActionDecorator(ShActionHandler *actionHandler, ShGraphicView *view);
	virtual ~ShSubActionDecorator() = 0;
	void SetChild(ShSubActionHandler *newChild);
	inline ShSubActionHandler* GetChild() const { return this->child; }
	virtual void AddCommandEditHeadTitle() {}

};

class ShObjectSnapState;
class ShSubActionDecorator_SnapMode : public ShSubActionDecorator {

protected:
	ObjectSnap objectSnap;
	ShObjectSnapState *objectSnapState;

public:
	ShSubActionDecorator_SnapMode(ShActionHandler *actionHandler, ShGraphicView *view,
		ObjectSnap objectSnap);
	~ShSubActionDecorator_SnapMode();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo &info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info);

	virtual void Draw(QPainter *painter);
	virtual void Decorate(ShSubActionDecorator *decorator);

	
	virtual void AddCommandEditHeadTitle();

	void UpdateCommandListFail();
};

/*
class ShSubActionDecorator_SnapMode_Perpendicular : public ShSubActionDecorator_SnapMode {

public:
	ShSubActionDecorator_SnapMode_Perpendicular(ShActionHandler *actionHandler,
		ShGraphicView *view, ObjectSnap objectSnap);
	ShSubActionDecorator_SnapMode_Perpendicular(const ShSubActionDecorator_SnapMode_Perpendicular& other);
	~ShSubActionDecorator_SnapMode_Perpendicular();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo &info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info);

	virtual ShSubActionDecorator_SnapMode_Perpendicular* Clone();
};

*/

class ShSubActionDecorator_Orthogonal : public ShSubActionDecorator {

public:
	ShSubActionDecorator_Orthogonal(ShActionHandler *actionHandler, ShGraphicView *view);
	~ShSubActionDecorator_Orthogonal();

	virtual void MousePressEvent(QMouseEvent *event, ShSubActionInfo &info);
	virtual void MouseMoveEvent(QMouseEvent *event, ShSubActionInfo &info);
	virtual void Draw(QPainter *painter);
	virtual void Decorate(ShSubActionDecorator *decorator);


	
	
};

#endif //_SHSUBACTIONHANDLER_H