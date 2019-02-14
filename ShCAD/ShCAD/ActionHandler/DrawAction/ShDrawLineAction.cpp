
/*--
**
**   This file is part of the ShCAD project, a 2D CAD Program
**
**    Copyright (C) 2019, Seungho Ha  (sh.ha1018@gmail.com)
**
**
**   This program is free software; you can redistribute it and/or modify it
**   under the terms of the GNU Lesser General Public License as published by
**   the Free Software Foundation; either version 2.1 of the License, or (at
**   your option) any later version.
**
**   This program is distributed in the hope that it will be useful, but
**   WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
**   General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public License
**   along with this program; if not, write to the Free Software Foundation,
**   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
**
**
--*/

#include "ShDrawLineAction.h"
#include <QMouseEvent>
#include "ShNotifyEvent.h"
#include "ActionHandler\DrawAction\SubActionHandler\ShSubDrawLineAction.h"

ShDrawLineAction::ShDrawLineAction(ShGraphicView *graphicView)
	:ShDrawAction(graphicView) {

	this->status = PickedNothing;
	this->subDrawLineAction = new ShDrawLineMethod_Default(this, this->graphicView);
	
}

ShDrawLineAction::~ShDrawLineAction() {

	if (this->subDrawLineAction != 0)
		delete this->subDrawLineAction;
}


void ShDrawLineAction::MousePressEvent(QMouseEvent *event) {
	
	ShPoint3d point;
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
	this->subDrawLineAction->SetPoint(point);

	this->subDrawLineAction->MousePressEvent(event);
}

void ShDrawLineAction::MouseMoveEvent(QMouseEvent *event) {

	DrawType drawType = DrawType::DrawCaptureImage;
	
	ShPoint3d point;
	this->graphicView->ConvertDeviceToEntity(event->x(), event->y(), point.x, point.y);
	this->subDrawLineAction->SetPoint(point);

	this->subDrawLineAction->MouseMoveEvent(event, drawType);

	this->graphicView->update(drawType);

}

void ShDrawLineAction::KeyPressEvent(QKeyEvent *event) {

	if (event->key() == Qt::Key::Key_Escape) {
	
		this->graphicView->ChangeCurrentAction(ActionType::ActionDefault);
	}


	else {
	
		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}

}


void ShDrawLineAction::SetObjectSnap(ObjectSnap objectSnap) {

	//if (this->subDrawLineAction != 0)
		//delete this->subDrawLineAction;

	this->subDrawLineAction->Decorate(new ShDrawLineDecorator_SnapMode(this, this->graphicView, objectSnap));
}

ActionType ShDrawLineAction::GetType() {

	return ActionType::ActionDrawLine;
}

void ShDrawLineAction::Draw(QPainter *painter) {

	this->subDrawLineAction->Draw(painter);
	
}

void ShDrawLineAction::ChangeSubAction(ShSubDrawLineAction *current) {

	if (this->subDrawLineAction != 0)
		delete this->subDrawLineAction;

	this->subDrawLineAction = current;
}