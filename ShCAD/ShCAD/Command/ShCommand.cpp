
#include "ShCommand.h"
#include "ActionHandler\ShActionHandler.h"
#include <qstring.h>
#include "Interface\ShCADWidget.h"
#include "ActionHandler\Private\ShChangeActionStrategy.h"
#include "Base\ShMath.h"

ShCommand::ShCommand(CommandType type)
	:type(type) {

}

ShCommand::~ShCommand() {

}

void ShCommand::trigger(const ShPoint3d &point,ShActionHandler *actionHandler) {

	actionHandler->trigger(point);
}

bool ShCommand::isNumber(const QString &string) {

	QString temp;
	temp = string.section('.', 2, 2);

	if (temp.length() != 0)
		return false;

	int i = 0;
	int count = string.length();

	for (i = 0; i < count; i++) {

		if (i == 0 && string[i] == '-')
			continue;
		if (string[i] == '.')
			continue;
		if (string[i] >= '0' && string[i] <= '9')
			continue;
		else
			break;
	}

	if (i == count)
		return true;

	return false;
}


//////////////////////////////////////////////////////////

ShEmptyCancelCommand::ShEmptyCancelCommand()
	:ShCommand(CommandType::Empty_Cancel) {

}

ShEmptyCancelCommand::~ShEmptyCancelCommand() {

}

void ShEmptyCancelCommand::interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command) {

	if (this->isMatched(command) == false)
		return;

	ShChangeDefaultAfterCancelingCurrentStrategy strategy;
	widget->changeAction(strategy);
}

bool ShEmptyCancelCommand::isMatched(const QString &command) {

	if (command.isEmpty() == true)
		return true;

	return false;
}


//////////////////////////////////////////////////////////////

ShAbsoluteCoordinateCommand::ShAbsoluteCoordinateCommand()
	:ShCommand(CommandType::AbsoluteCoordinate) {

}

ShAbsoluteCoordinateCommand::~ShAbsoluteCoordinateCommand() {

}

void ShAbsoluteCoordinateCommand::interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command) {

	if (this->isMatched(command) == false)
		return;

	ShPoint3d point;
	this->convertCoordinate(command, point.x, point.y);

	this->trigger(point, actionHandler);
}

bool ShAbsoluteCoordinateCommand::isMatched(const QString &command) {

	QString x, y, temp;

	if (command.count(',') != 1)
		return false;

	x = command.section(',', 0, 0);
	y = command.section(',', 1, 1);
	temp = command.section(',', 2, 2);

	if (x.length() == 0)
		return false;
	if (y.length() == 0)
		return false;
	if (temp.length() != 0)
		return false;

	if (this->isNumber(x) == false)
		return false;
	if (this->isNumber(y) == false)
		return false;

	return true;
}

void ShAbsoluteCoordinateCommand::convertCoordinate(const QString &command, double &x, double &y) {

	x = command.section(',', 0, 0).toDouble();
	y = command.section(',', 1, 1).toDouble();
}

//////////////////////////////////////////////////////////////////////

ShRelativeCoordinateCommand::ShRelativeCoordinateCommand()
	:ShCommand(CommandType::RelativeCoordinate) {

}

ShRelativeCoordinateCommand::~ShRelativeCoordinateCommand() {

}

void ShRelativeCoordinateCommand::interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command) {

	if (this->isMatched(command) == false)
		return;

	ShPoint3d point;
	this->convertCoordinate(command, point.x, point.y);

	ShPoint3d lastPickedPoint = actionHandler->getLastPickedPoint();

	point.x += lastPickedPoint.x;
	point.y += lastPickedPoint.y;

	this->trigger(point, actionHandler);
}

bool ShRelativeCoordinateCommand::isMatched(const QString &command) {

	QString x, y, temp;

	if (command.count(',') != 1)
		return false;

	x = command.section(',', 0, 0);
	y = command.section(',', 1, 1);
	temp = command.section(',', 2, 2);

	if (x.length() == 0)
		return false;
	if (y.length() == 0)
		return false;
	if (temp.length() != 0)
		return false;

	temp = x.section('@', 0, 0);
	if (temp.length() != 0)
		return false;

	temp = x.section('@', 2, 2);
	if (temp.length() != 0)
		return false;

	temp = x.section('@', 1, 1);
	if (this->isNumber(temp) == false)
		return false;
	if (this->isNumber(y) == false)
		return false;

	return true;
}

void ShRelativeCoordinateCommand::convertCoordinate(const QString &command, double &x, double &y) {

	QString tempX;
	tempX = command.section(',', 0, 0);
	
	x = tempX.section('@', 1, 1).toDouble();
	y = command.section(',', 1, 1).toDouble();
}

//////////////////////////////////////////////////////////////////////

ShDistanceCommand::ShDistanceCommand()
	:ShCommand(CommandType::Distance) {

}

ShDistanceCommand::~ShDistanceCommand() {

}

void ShDistanceCommand::interpret(ShCADWidget *widget, ShActionHandler *actionHandler, const QString &command) {

	if (this->isMatched(command) == false)
		return;

	ShPoint3d mouse = widget->getMousePoint();
	ShPoint3d lastPickedPoint = actionHandler->getLastPickedPoint();

	double angle = math::getAbsAngle(lastPickedPoint.x, lastPickedPoint.y, mouse.x, mouse.y);

	ShPoint3d point;
	math::rotate(angle, lastPickedPoint.x, lastPickedPoint.y, lastPickedPoint.x + command.toDouble(), lastPickedPoint.y, point.x, point.y);

	this->trigger(point, actionHandler);
}

bool ShDistanceCommand::isMatched(const QString &command) {

	if (this->isNumber(command) == false)
		return false;

	return true;
}