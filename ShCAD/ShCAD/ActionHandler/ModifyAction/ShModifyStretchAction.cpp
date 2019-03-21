


#include "ShModifyStretchAction.h"
#include <QKeyEvent>
#include "ShNotifyEvent.h"
#include "Strategy Pattern\ShChangeCurrentActionStrategy.h"
#include "Entity\Leaf\ShRubberBand.h"
#include "Entity\Composite\ShPreview.h"
#include "Visitor Pattern\ShStretchVisitor.h"

ShModifyStretchAction::ShModifyStretchAction(ShGraphicView *graphicView)
	:ShModifyAction(graphicView), status(SelectingEntities) {

	ShUpdateListTextEvent event("_Stretch", ShUpdateListTextEvent::UpdateType::editTextAndNewLineHeadTitleWithText);
	this->graphicView->Notify(&event);

	QString headTitle = this->GetActionHeadTitle();

	ShUpdateCommandEditHeadTitle event2(headTitle);
	this->graphicView->Notify(&event2);
}

ShModifyStretchAction::~ShModifyStretchAction() {

}

#include "Command Pattern\Entity Command\ShStretchEntityCommand.h"
#include "ActionHandler\TemporaryAction\ShDragSelectAction.h"
void ShModifyStretchAction::LMousePressEvent(QMouseEvent *event, ShActionData& data) {

	if (this->status == SelectingEntities) {

		ShPoint3d point = this->graphicView->GetCursorPoint();
		ShEntity* entity = this->graphicView->entityTable.FindEntity(point.x, point.y, this->graphicView->GetZoomRate());

		if (entity == 0) {

			if (event->modifiers() == Qt::ShiftModifier)
				this->graphicView->SetTemporaryAction(new ShModifyStretchDragSelectAction(this->graphicView, this,
					&this->list, &this->vertexList, point.x, point.y, ShDragSelectAction::Mode::UnSelectMode));
			else
				this->graphicView->SetTemporaryAction(new ShModifyStretchDragSelectAction(this->graphicView, this,
					&this->list, &this->vertexList, point.x, point.y));

			return;
		}

		this->DoFollowUpWithFoundEntity(entity, event->modifiers());

	}
	else if (this->status == FinishedSelectingEntities) {

		this->status = PickedBasePoint;
		this->base = data.GetPoint();

		this->graphicView->rubberBand = new ShRubberBand(ShLineData(this->base, data.GetNextPoint()));

		QLinkedList<ShEntity*>::iterator itr;
		for (itr = this->graphicView->selectedEntityManager.Begin();
			itr != this->graphicView->selectedEntityManager.End();
			++itr) {
			this->graphicView->preview.Add((*itr)->Clone());
		}

		ShStretchVisitor visitor(this->base, data.GetNextPoint());

		QLinkedList<VertexPoint>::iterator itrVertexPoint = this->vertexList.begin();
		QLinkedList<ShEntity*>::iterator originalItr = this->list.begin();

		for (itr = this->graphicView->preview.Begin();
			itr != this->graphicView->preview.End();
			++itr) {

			visitor.SetVertexPoint((*itrVertexPoint));
			visitor.SetOriginalEntity((*originalItr));

			++originalItr;
			++itrVertexPoint;
			(*itr)->Accept(&visitor);
		}
		

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));

		this->UpdateNextListText();
	}
	else if (this->status == PickedBasePoint) {

		ShStretchEntityCommand *command = new ShStretchEntityCommand(this->graphicView,
			this->list, this->vertexList, this->base, data.GetPoint());

		command->Execute();

		this->graphicView->undoTaker.Push(command);

		if (!this->graphicView->redoTaker.IsEmpty())
			this->graphicView->redoTaker.DeleteAll();
		

		ShChangeCurrentActionCurrentFinished strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);

	}
}

void ShModifyStretchAction::RMousePressEvent(QMouseEvent *event, ShActionData& data) {

	if (this->status == SelectingEntities) {

		if (this->graphicView->selectedEntityManager.GetSize() != 0) {

			this->status = FinishedSelectingEntities;

			this->UpdateNextListText();

			this->graphicView->setCursor(this->GetCursorShape());

		}
		else {
			ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
			this->graphicView->ChangeCurrentAction(strategy);
		}
	}


}

void ShModifyStretchAction::MouseMoveEvent(QMouseEvent *event, ShActionData& data) {

	if (this->status == PickedBasePoint) {

		this->graphicView->rubberBand->SetEnd(data.GetPoint());

		ShStretchVisitor visitor(this->base, data.GetPoint());

		QLinkedList<ShEntity*>::iterator itr;
		QLinkedList<VertexPoint>::iterator itrVertexPoint = this->vertexList.begin();
		QLinkedList<ShEntity*>::iterator originalItr = this->list.begin();

		for (itr = this->graphicView->preview.Begin();
			itr != this->graphicView->preview.End();
			++itr) {

			visitor.SetVertexPoint((*itrVertexPoint));
			visitor.SetOriginalEntity((*originalItr));

			++originalItr;
			++itrVertexPoint;
			(*itr)->Accept(&visitor);
		}

		

		data.AppendDrawType((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}
}


void ShModifyStretchAction::KeyPressEvent(QKeyEvent *event, ShActionData& data) {

	if (event->key() == Qt::Key::Key_Escape) {

		ShChangeCurrentActionCancelCurrent strategy(ActionType::ActionDefault);
		this->graphicView->ChangeCurrentAction(strategy);

	}
	else {

		ShKeyPressedEvent event2(event);
		this->graphicView->Notify(&event2);
	}
}

ActionType ShModifyStretchAction::GetType() {

	return ActionType::ActionModifyStretch;
}

#include <qpainter.h>
QCursor ShModifyStretchAction::GetCursorShape() {

	if (this->status == Status::SelectingEntities) {
		QPixmap pix(32, 32);
		pix.fill(Qt::transparent); // Otherwise you get a black background :(
		QPainter painter(&pix);
		painter.setPen(QColor(255, 255, 255));
		painter.drawRect(13, 13, 6, 6);

		return QCursor(pix);
	}

	return QCursor(Qt::CursorShape::CrossCursor);
}

QString ShModifyStretchAction::GetActionHeadTitle() {

	QString str = "";

	if (this->status == SelectingEntities) {
		str = "Stretch >> Select objects: ";
	}
	else if (this->status == FinishedSelectingEntities) {
		str = "Stretch >> Specify base point: ";
	}
	else if (this->status == PickedBasePoint) {
		str = "Stretch >> Specify second point: ";
	}

	return str;
}

void ShModifyStretchAction::IsAllowedDraftOperation(ShAllowedDraftData &data) {

	if (this->status == Status::SelectingEntities)
		return;

	if (this->status == Status::FinishedSelectingEntities) {
		data.SetAllowOrthogonal(true);
		data.SetAllowtSnap(true);

		ShPoint3d mouse = this->graphicView->GetCursorPoint();
		data.SetOrthogonalBasePoint(mouse);
		data.SetSnapBasePoint(mouse);
	}
	else if (this->status == Status::PickedBasePoint) {

		data.SetAllowOrthogonal(true);
		data.SetAllowtSnap(true);

		ShPoint3d point = this->graphicView->rubberBand->GetStart();
		data.SetOrthogonalBasePoint(point);
		data.SetSnapBasePoint(point);
	}

}

void ShModifyStretchAction::ApplyOrthogonalShape(bool on) {

	if (this->status == Status::PickedBasePoint) {

		ShPoint3d mouse = this->graphicView->GetCursorPoint();

		if (on == true) {
			ShPoint3d orth;
			ShPoint3d start = this->graphicView->rubberBand->GetStart();
			this->GetOrthogonal(start.x, start.y, mouse.x, mouse.y, orth.x, orth.y);
			this->graphicView->rubberBand->SetEnd(orth);
		}
		else
			this->graphicView->rubberBand->SetEnd(mouse);

		ShPoint3d end = this->graphicView->rubberBand->GetEnd();

		ShStretchVisitor visitor(this->base, end);

		QLinkedList<ShEntity*>::iterator itr;
		QLinkedList<VertexPoint>::iterator itrVertexPoint = this->vertexList.begin();
		QLinkedList<ShEntity*>::iterator originalItr = this->list.begin();

		for (itr = this->graphicView->preview.Begin();
			itr != this->graphicView->preview.End();
			++itr) {

			visitor.SetVertexPoint((*itrVertexPoint));
			visitor.SetOriginalEntity((*originalItr));

			++originalItr;
			++itrVertexPoint;
			(*itr)->Accept(&visitor);
		}

		this->graphicView->update((DrawType)(DrawType::DrawCaptureImage | DrawType::DrawPreviewEntities));
	}

}

void ShModifyStretchAction::UpdateNextListText() {

	ShUpdateListTextEvent event("");
	this->graphicView->Notify(&event);

	ShUpdateCommandEditHeadTitle event2(this->GetActionHeadTitle());
	this->graphicView->Notify(&event2);
}


void ShModifyStretchAction::DoFollowUpWithFoundEntity(ShEntity* foundEntity, Qt::KeyboardModifiers modifier) {

	if (modifier == Qt::Modifier::SHIFT) {

		if (foundEntity->IsSelected() == true) {
			
			int index = 0;
			QLinkedList<ShEntity*>::iterator itr = this->list.begin();
			
			while (itr != this->list.end() && (*itr) != foundEntity) {
			
				index++;
				++itr;
			}
			
			this->list.removeOne(foundEntity);

			QLinkedList<VertexPoint>::iterator vertexItr = this->vertexList.begin();
			int i = 0;
			while (i < index) {
				++vertexItr;
				i++;
			}
			this->vertexList.erase(vertexItr);
		}
	}
	else {
		if (foundEntity->IsSelected() == false) {

			VertexPoint vertexPoint;
			ShFindStretchMovePointVisitor visitor(vertexPoint);

			foundEntity->Accept(&visitor);

			this->list.append(foundEntity);
			this->vertexList.append(vertexPoint);

		}
	}


	ShModifyAction::DoFollowUpWithFoundEntity(foundEntity, modifier);

}