
#ifndef _SHCADWIDGETEVENTFILTER_H
#define _SHCADWIDGETEVENTFILTER_H

class ShCADWidget;
class ShNotifyEvent;
class ShCADWidgetEventFilterStrategy;

class ShCADWidgetEventFilter {

private:
	ShCADWidgetEventFilterStrategy *strategy;

public:
	ShCADWidgetEventFilter(ShCADWidget *widget, ShNotifyEvent *event);
	~ShCADWidgetEventFilter();

	void update();

};

////////////////////////////////////////////////////

class ShCADWidgetEventFilterStrategy {

protected:
	ShNotifyEvent *event;
	ShCADWidget *widget;

public:
	ShCADWidgetEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event);
	virtual ~ShCADWidgetEventFilterStrategy() = 0;

	virtual void update() = 0;

};

///////////////////////////////////////////////////

class ShCADWidgetKeyPressedEventFilterStrategy : public ShCADWidgetEventFilterStrategy {

public:
	ShCADWidgetKeyPressedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event);
	~ShCADWidgetKeyPressedEventFilterStrategy();

	virtual void update();

};

////////////////////////////////////////////////////

class ShCADWidgetCurrentColorChangedEventFilterStrategy : public ShCADWidgetEventFilterStrategy {

public:
	ShCADWidgetCurrentColorChangedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event);
	~ShCADWidgetCurrentColorChangedEventFilterStrategy();

	virtual void update();

};

////////////////////////////////////////////////////

class ShCADWidgetCurrentLineStyleChangedEventFilterStrategy : public ShCADWidgetEventFilterStrategy {

public:
	ShCADWidgetCurrentLineStyleChangedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event);
	~ShCADWidgetCurrentLineStyleChangedEventFilterStrategy();

	virtual void update();

};

////////////////////////////////////////////////////

class ShCADWidgetCurrentLayerChangedEventFilterStrategy : public ShCADWidgetEventFilterStrategy {

public:
	ShCADWidgetCurrentLayerChangedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event);
	~ShCADWidgetCurrentLayerChangedEventFilterStrategy();

	virtual void update();

};

/////////////////////////////////////////////////////

class ShCADWidgetLayerDataChangedEventFilterStrategy : public ShCADWidgetEventFilterStrategy {

public:
	ShCADWidgetLayerDataChangedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event);
	~ShCADWidgetLayerDataChangedEventFilterStrategy();

	virtual void update();

private:
	void changeLayerColor();
	void changeLayerLineStyle();
	void changeLayerName();
	void changeLayerTurn();

};

////////////////////////////////////////////////////////

class ShCADWidgetLayerCreatedEventFilterStrategy : public ShCADWidgetEventFilterStrategy {

public:
	ShCADWidgetLayerCreatedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event);
	~ShCADWidgetLayerCreatedEventFilterStrategy();

	virtual void update();
};

/////////////////////////////////////////////////////////

class ShCADWidgetLayerDeletedEventFilterStrategy : public ShCADWidgetEventFilterStrategy {

public:
	ShCADWidgetLayerDeletedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event);
	~ShCADWidgetLayerDeletedEventFilterStrategy();

	virtual void update();

};


/////////////////////////////////////////////////////////

class ShCADWidgetCurrentDimensionStyleChangedEventFilterStrategy : public ShCADWidgetEventFilterStrategy {

public:
	ShCADWidgetCurrentDimensionStyleChangedEventFilterStrategy(ShCADWidget *widget, ShNotifyEvent *event);
	~ShCADWidgetCurrentDimensionStyleChangedEventFilterStrategy();

	virtual void update();

};
#endif //_SHCADWIDGETEVENTFILTER_H