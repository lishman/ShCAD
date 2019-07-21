
#include "ShNotifyEvent.h"

ShNotifyEvent::ShNotifyEvent(Type type)
	:type(type) {

}

ShNotifyEvent::~ShNotifyEvent() {

}

////////////////////////////////////////////

ShZoomRateChangedEvent::ShZoomRateChangedEvent(const double &zoomRate)
	:ShNotifyEvent(Type::ZoomRateChanged), zoomRate(zoomRate) {

}

ShZoomRateChangedEvent::~ShZoomRateChangedEvent() {


}

////////////////////////////////////////////

ShMousePositionChangedEvent::ShMousePositionChangedEvent(const ShPoint3d &point)
	:ShNotifyEvent(Type::MousePositionChanged), point(point) {

}

ShMousePositionChangedEvent::~ShMousePositionChangedEvent() {


}

/////////////////////////////////////////////////////////////////////

ShKeyPressedEvent::ShKeyPressedEvent(QKeyEvent *event)
	:ShNotifyEvent(Type::KeyPressed), event(event) {


}

ShKeyPressedEvent::~ShKeyPressedEvent() {

}

///////////////////////////////////////////////////////////////////////

ShActivatedWidgetChangedEvent::ShActivatedWidgetChangedEvent(ShCADWidget *newWidget, ShCADWidget *previousWidget)
	:ShNotifyEvent(Type::ActivatedWidgetChanged), newWidget(newWidget), previousWidget(previousWidget) {

}

ShActivatedWidgetChangedEvent::~ShActivatedWidgetChangedEvent() {

}

///////////////////////////////////////////////////////////////////////


ShUpdateTextToCommandListEvent::ShUpdateTextToCommandListEvent(const QString &text, ShUpdateTextToCommandListEvent::UpdateType type)
	:ShNotifyEvent(Type::UpdateTextToCommandList), text(text), updateType(type) {

}

ShUpdateTextToCommandListEvent::~ShUpdateTextToCommandListEvent() {

}

/////////////////////////////////////////////////////////////////////

ShUpdateCommandHeadTitleEvent::ShUpdateCommandHeadTitleEvent(const QString &headTitle, UpdateType type)
	:ShNotifyEvent(Type::UpdateCommandHeadTitle), headTitle(headTitle), updateType(type) {

}

ShUpdateCommandHeadTitleEvent::~ShUpdateCommandHeadTitleEvent() {

}