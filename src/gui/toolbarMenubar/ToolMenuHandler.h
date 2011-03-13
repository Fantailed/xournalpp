/*
 * Xournal Extended
 *
 * Part of the customizable toolbars
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */

#ifndef EDITABLETOOLBAR_H_
#define EDITABLETOOLBAR_H_

#include <gtk/gtk.h>

#include "../../util/ListIterator.h"
#include "../../control/Actions.h"
#include "../../control/ZoomControl.h"
#include "../../util/String.h"
#include "../GladeGui.h"
#include <vector>
#include "ToolbarEntry.h"
#include "../../control/ToolHandler.h"

class ToolbarData {
public:
	ToolbarData(bool predefined);

public:
	String getName();
	String getId();

	void load(GKeyFile * config, const char * group);

	bool isPredefined();
private:
	String id;
	String name;
	std::vector<ToolbarEntry> contents;

	bool predefined;

	friend class ToolMenuHandler;
};

class AbstractToolItem;
class ToolButton;
class ToolPageSpinner;
class ToolPageLayer;
class FontButton;


class ToolMenuHandler {
public:
	ToolMenuHandler(ActionHandler * listener, ZoomControl * zoom, GladeGui * gui, ToolHandler * toolHandler);
	virtual ~ToolMenuHandler();

public:
	bool parse(const char * file, bool predefined);

	ListIterator<ToolbarData *> iterator();

	void unloadToolbar(GtkWidget * tBunload);
	void freeToolbar();

	void load(ToolbarData * d, GtkWidget * toolbar, const char * toolbarName, bool horizontal);

	void registerMenupoint(GtkWidget * widget, ActionType type);
	void registerMenupoint(GtkWidget * widget, ActionType type, ActionGroup group);

	void initToolItems();

	void setUndoDescription(String description);
	void setRedoDescription(String description);

	GtkWidget * getPageSpinner();
	void setPageText(String text);

	int getSelectedLayer();
	void setLayerCount(int count, int selected);

	void setFontButtonFont(XojFont & font);
	XojFont getFontButtonFont();


	void setTmpDisabled(bool disabled);

	const char * getColorName(const char * color);


private:
	void addToolItem(AbstractToolItem * it);
	void parseGroup(GKeyFile * config, const char * group, bool predefined);
	void parseColors(GKeyFile * config, const char * group);

	void initEraserToolItem();

private:
	GList * toolbars;
	GList * toolbarColorItems;

	GList * toolItems;
	GList * menuItems;

	ToolButton * undoButton;
	ToolButton * redoButton;

	ToolPageSpinner * toolPageSpinner;
	ToolPageLayer * toolPageLayer;
	FontButton * fontButton;

	ActionHandler * listener;
	ZoomControl * zoom;
	GladeGui * gui;
	ToolHandler * toolHandler;

	GHashTable * colorNameTable;
};

#endif /* EDITABLETOOLBAR_H_ */
