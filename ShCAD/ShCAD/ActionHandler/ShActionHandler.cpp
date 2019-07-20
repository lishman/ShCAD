
#include "ShActionHandler.h"
#include <qpainter.h>
#include "KeyHandler\ShKeyHandler.h"

ShActionHandler::ShActionHandler(ShCADWidget *widget)
	:widget(widget), keyHandler(nullptr) {

}

ShActionHandler::~ShActionHandler() {

	if (this->keyHandler != nullptr)
		delete this->keyHandler;
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


QCursor ShActionHandler::getCursorShape() {

	QPixmap pix(48, 48);
	pix.fill(Qt::transparent);
	QPainter painter(&pix);
	painter.setPen(QColor(255, 255, 255));

	painter.drawLine(24, 0, 24, 48);
	painter.drawLine(0, 24, 48, 24);

	painter.drawRect(21, 21, 6, 6);

	return QCursor(pix);
}