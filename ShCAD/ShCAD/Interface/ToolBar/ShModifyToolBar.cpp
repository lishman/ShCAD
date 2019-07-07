

#include "ShModifyToolBar.h"
#include "Interface\Item\ShIcon.h"

ShModifyToolBar::ShModifyToolBar(const QString &title, QWidget *parent)
	:ShAbstractToolBar(title, parent) {

	this->setIconSize(QSize(20, 20));

	QAction *action;

	action = this->addAction(ShIcon(":/Image/Modify/Erase.png"), "Erase");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::eraseActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Copy.png"), "Copy");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::copyActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Mirror.png"), "Mirror");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::mirrorActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Move.png"), "Move");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::moveActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Rotate.png"), "Rotate");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::rotateActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Scale.png"), "Scale");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::scaleActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Stretch.png"), "Stretch");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::stretchActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Extend.png"), "Extend");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::extendActionClicked);

	action = this->addAction(ShIcon(":/Image/Modify/Trim.png"), "Trim");
	connect(action, &QAction::triggered, this, &ShModifyToolBar::trimActionClicked);


}

ShModifyToolBar::~ShModifyToolBar() {


}

void ShModifyToolBar::eraseActionClicked() {


}

void ShModifyToolBar::copyActionClicked() {


}

void ShModifyToolBar::mirrorActionClicked() {


}

void ShModifyToolBar::moveActionClicked() {


}

void ShModifyToolBar::rotateActionClicked() {


}

void ShModifyToolBar::scaleActionClicked() {


}

void ShModifyToolBar::stretchActionClicked() {


}

void ShModifyToolBar::extendActionClicked() {


}

void ShModifyToolBar::trimActionClicked() {


}