
#ifndef _SHCOMMANDLOGMANAGER_H
#define _SHCOMMANDLOGMANAGER_H


#define shCommandLogManager ShCommandLogManager::getInstance()

class ShCommandDock;
class QString;
class ShCommandLogManager {

private:
	static ShCommandLogManager instance;
	ShCommandDock *commandDock;

private:
	ShCommandLogManager();
	~ShCommandLogManager();

public:
	static ShCommandLogManager* getInstance();

public:
	void registerInterface(ShCommandDock *commandDock) { this->commandDock = commandDock; }

public:
	void appendHeadTitle(const QString &headTitle);
	void replaceHeadTitle(const QString &headTitle);
	void appendList(const QString &text);
	void appendListEditTextWith(const QString &text);
	void appendListEditTextAndNewLineWith(const QString &text);
};

#endif //_SHCOMMANDLOGMANAGER_H