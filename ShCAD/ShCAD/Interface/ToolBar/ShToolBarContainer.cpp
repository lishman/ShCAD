

#include "ShToolBarContainer.h"
#include "Interface\ShCAD.h"
#include <qmenu.h>
#include "ShDrawToolBar.h"
#include "ShLayerToolBar.h"
#include "ShPropertyToolBar.h"
#include "ShModifyToolBar.h"
#include "ShObjectSnapToolBar.h"

ShToolBarContainer::ShToolBarContainer(ShCAD *parent)
	:parent(parent) {

	this->toolBarMenu = new QMenu("ToolBars");

	this->createToolBars();

	QList<ShAbstractToolBar*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr) {

		this->parent->addToolBar(Qt::ToolBarArea::TopToolBarArea, (*itr));
		this->toolBarMenu->addAction((*itr)->GetMenuAction());
		(*itr)->hide();
	}


}

ShToolBarContainer::~ShToolBarContainer() {

	if (this->toolBarMenu != nullptr)
		delete this->toolBarMenu;

}

void ShToolBarContainer::createToolBars() {

	this->drawToolBar = new ShDrawToolBar("Draw", this->parent);
	this->list.append(this->drawToolBar);

	this->propertyToolBar = new ShPropertyToolBar("Property", this->parent);
	this->list.append(this->propertyToolBar);

	this->modifyToolBar = new ShModifyToolBar("Modify", this->parent);
	this->list.append(this->modifyToolBar);

	this->layerToolBar = new ShLayerToolBar("Layer", this->parent);
	this->list.append(this->layerToolBar);

	this->objectSnapToolBar = new ShObjectSnapToolBar("ObjectSnap", this->parent);
	this->list.append(this->objectSnapToolBar);


}

void ShToolBarContainer::activate() {

	QList<ShAbstractToolBar*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		(*itr)->activate();

}

void ShToolBarContainer::deactivate() {

	QList<ShAbstractToolBar*>::iterator itr;
	for (itr = this->list.begin(); itr != this->list.end(); ++itr)
		(*itr)->deactivate();

}