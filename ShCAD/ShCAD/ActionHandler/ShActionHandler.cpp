
#include "ShActionHandler.h"
#include <qpainter.h>
#include "KeyHandler\ShKeyHandler.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "Manager\ShCommandLogManager.h"
#include "Command\ShAvailableCommands.h"
#include "Base\ShCursorShape.h"

ShActionHandler::ShActionHandler(ShCADWidget *widget)
	:widget(widget), keyHandler(nullptr), availableCommands(nullptr) {

}

ShActionHandler::~ShActionHandler() {

	if (this->keyHandler != nullptr)
		delete this->keyHandler;

	if (this->availableCommands != nullptr)
		delete this->availableCommands;
}

void ShActionHandler::mouseLeftPressEvent(ShActionData &data) {

}

void ShActionHandler::mouseMidPressEvent(ShActionData &data) {

}

void ShActionHandler::mouseRightPressEvent(ShActionData &data) {

}

void ShActionHandler::mouseMoveEvent(ShActionData &data) {

}

void ShActionHandler::mouseReleaseEvent(ShActionData &data) {

}


void ShActionHandler::keyPressEvent(ShActionData &data) {

	if (this->keyHandler != nullptr)
		this->keyHandler->keyPressEvent(data.keyEvent);
}

void ShActionHandler::draw(QPainter *painter) {

}

ActionType ShActionHandler::getTypeIgnoringTemp() {

	return this->getType();
}

QCursor ShActionHandler::getCursorShape() {

	return ShCursorShape::getCursor(ShCursorShape::CursorType::Default);
}

//*Template method pattern.
void ShActionHandler::updateCommandEditHeadTitle() {

	shCommandLogManager->replaceHeadTitle(this->getHeadTitle());
}

ShAvailableDraft ShActionHandler::getAvailableDraft() {

	return ShAvailableDraft();
}

void ShActionHandler::invalidate(ShPoint3d &point) {

}

void ShActionHandler::interpret(const QString &command) {

	if (this->availableCommands != nullptr)
		this->availableCommands->interpret(command);
}

ShPoint3d ShActionHandler::getLastBasePoint() {

	return this->widget->getLastBasePoint();
}

ShPoint3d ShActionHandler::getCurrentAboutToPickPoint() {

	ShPoint3d point;

	if (this->widget->getRubberBand().isExist() == true)
		point = this->widget->getRubberBand().getEnd();
	else
		point = this->widget->getMousePoint();

	return point;
}

void ShActionHandler::triggerSucceeded() {

	shCommandLogManager->appendListEditTextWith("");
	this->updateCommandEditHeadTitle();
}

void ShActionHandler::triggerFailed(ShActionTriggerFailureReason reason) {

	if (reason == ShActionTriggerFailureReason::ValueMustBeGreaterThanZero) {
	
		shCommandLogManager->appendListEditTextWith("");
		shCommandLogManager->appendList(shGetLanValue_command("Command/Value must be greater than zero") + ".");
		this->updateCommandEditHeadTitle();
	}
	else if (reason == ShActionTriggerFailureReason::InvalidPoint) {
	
		shCommandLogManager->appendListEditTextWith("");
		shCommandLogManager->appendList(shGetLanValue_command("Command/Invalid point") + ".");
		this->updateCommandEditHeadTitle();
	}
	else if (reason == ShActionTriggerFailureReason::NoEdgeInThatDirection) {
	
		shCommandLogManager->appendListEditTextWith("");
		shCommandLogManager->appendList(shGetLanValue_command("Command/No edge in that direction") + ".");
		this->updateCommandEditHeadTitle();
	}
	else if (reason == ShActionTriggerFailureReason::NoIntersectWithCuttingEdge) {
	
		shCommandLogManager->appendListEditTextWith("");
		shCommandLogManager->appendList(shGetLanValue_command("Command/Does not intersect with the cutting edge") + ".");
		this->updateCommandEditHeadTitle();
	}
}

void ShActionHandler::trigger(const ShPoint3d &point) {

}

void ShActionHandler::actionCanceled() {

	ShChangeDefaultAfterCancelingCurrentStrategy strategy;
	this->widget->changeAction(strategy);
}

void ShActionHandler::actionFinished() {

	ShChangeDefaultAfterFinishingCurrentStrategy strategy;
	this->widget->changeAction(strategy);
}

void ShActionHandler::setLastBasePoint(const ShPoint3d &point) {

	this->widget->setLastBasePoint(point);
}