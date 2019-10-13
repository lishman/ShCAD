
#include "ShDimLinear.h"
#include "Entity\Private\ShVisitor.h"
#include "Base\ShMath.h"
#include "Base\ShDimensionStyle.h"
#include "Entity\Leaf\ShDot.h"
#include "Entity\Leaf\ShLine.h"

ShDimLinear::ShDimLinear(const ShDimLinearData &data, const ShPropertyData &propertyData, ShLayer *layer, ShDimensionStyle *dimensionStyle)
	:ShDim(propertyData, layer, dimensionStyle), data(data) {

	this->updateChild();
}

ShDimLinear::ShDimLinear(const ShDimLinear &other)
	: ShDim(other), data(other.data) {

	this->updateChild();
}

ShDimLinear::~ShDimLinear() {

}

ShDimLinear& ShDimLinear::operator=(const ShDimLinear &other) {

	ShDim::operator=(other);

	this->data = other.data;
	this->updateChild();

	return *this;
}

ShDimLinear* ShDimLinear::clone() {

	return new ShDimLinear(*this);
}

void ShDimLinear::accept(ShVisitor *visitor) {

	visitor->visit(this);
}

void ShDimLinear::updateChild() {

	while (!this->list.isEmpty())
		delete this->list.takeFirst();

	this->list.append(new ShDot(this->data.firstOrigin, this->propertyData, this->layer));
	this->list.append(new ShDot(this->data.secondOrigin, this->propertyData, this->layer));

	ShLine *extensionLine = const_cast<ShDimensionExtensionLineStyle&>(this->dimensionStyle->getDimensionExtensionLineStyle()).
		createExtensionLine(this->data.firstOrigin, this->data.firstDim, this->propertyData, this->layer);
	
	if (extensionLine != nullptr)
		this->list.append(extensionLine);

	extensionLine = const_cast<ShDimensionExtensionLineStyle&>(this->dimensionStyle->getDimensionExtensionLineStyle()).
		createExtensionLine2(this->data.secondOrigin, this->data.secondDim, this->propertyData, this->layer);

	if (extensionLine != nullptr)
		this->list.append(extensionLine);

	this->list.append(new ShLine(this->propertyData, ShLineData(this->data.firstDim, this->data.secondDim), this->layer));
	this->list.append(new ShLine(this->propertyData, ShLineData(this->data.firstDim, this->data.text), this->layer));
}

void ShDimLinear::setData(const ShDimLinearData &data) {

	this->data = data;
	this->updateChild();
}

double ShDimLinear::getDistance() {

	return math::getDistance(this->data.firstDim.x, this->data.firstDim.y, this->data.secondDim.x, this->data.secondDim.y);
}