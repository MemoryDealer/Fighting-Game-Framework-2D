// ================================================ //

#ifndef __GUI_HPP__
#define __GUI_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Widget.hpp"

// ================================================ //

class GUILayer;
class Config;

// ================================================ //

typedef std::vector<std::shared_ptr<Widget>> WidgetList;
typedef std::vector<std::shared_ptr<GUILayer>> GUILayerList;
typedef std::vector<std::string> StringList;

// ================================================ //
/* An object for each game state to process all GUI operations */
class GUI
{
public:
	explicit GUI(void);
	virtual ~GUI(void) = 0;

	enum NavMode{
		MOUSE = 0,
		SELECTOR
	};

	enum Action{
		NAVIGATE = 0,
		BEGIN_PRESS,
		FINISH_PRESS
	};

	void addLayer(std::shared_ptr<GUILayer> layer);
	void clearSelector(void);
	
	// Setter functions
	void setCurrentLayer(const int n);
	void setNavigationMode(const int mode);
	void setMousePos(const int x, const int y);
	void setLeftMouseDown(const bool down);
	void setRightMouseDown(const bool down);
	void setSelectedWidget(const int n);

	// Getter functions
	GUILayer* getCurrentLayer(void) const;
	const int getNavigationMode(void) const;
	const int getSelectedWidget(void) const;

	virtual void update(double dt);

	// Static strings to store theme data across all GUI states (useful within GUILayer::parse())
	static std::shared_ptr<SDL_Texture> ButtonTexture[3];

private:
	GUILayerList m_layers;
	GUILayer* m_pCurrentLayer;
	int m_selectedWidget, m_lastSelectedWidget;
	int m_navMode;
	int m_mouseX, m_mouseY;
	bool m_leftMouseDown, m_rightMouseDown;
};

// ================================================ //

inline void GUI::addLayer(std::shared_ptr<GUILayer> layer){
	m_layers.push_back(layer);
}

// Setters
inline void GUI::setNavigationMode(const int mode){
	m_navMode = mode;
}

inline void GUI::setMousePos(const int x, const int y){
	m_mouseX = x; m_mouseY = y;
}

inline void GUI::setLeftMouseDown(const bool down){
	m_leftMouseDown = down;
}

inline void GUI::setRightMouseDown(const bool down){
	m_rightMouseDown = down;
}

// Getters
inline GUILayer* GUI::getCurrentLayer(void) const{
	return m_pCurrentLayer;
}

inline const int GUI::getNavigationMode(void) const{
	return m_navMode;
}

inline const int GUI::getSelectedWidget(void) const{
	return m_selectedWidget;
}

// ================================================ //
// ================================================ //

class GUILayer
{
public:
	explicit GUILayer(void);
	virtual ~GUILayer(void);

	void addWidget(std::shared_ptr<Widget> widget);

	template<typename T>
	void parse(Config& c, const int widgetType, const StringList& names);

	// Getter functions
	const int getID(void) const;
	Widget* getWidget(const int n) const;
	const int getNumWidgets(void) const;

	// Setter functions
	void setID(const int id);
	void setLayerName(const std::string& name);

	virtual void render(void);
	virtual void update(double dt) = 0;

private:
	int m_id;
	WidgetList m_widgets;
	std::string m_layerName;
};

// ================================================ //

inline void GUILayer::addWidget(std::shared_ptr<Widget> widget){
	m_widgets.push_back(widget);
}

// Getters
inline const int GUILayer::getID(void) const{
	return m_id;
}

inline Widget* GUILayer::getWidget(const int n) const{
	return m_widgets[n].get();
}

inline const int GUILayer::getNumWidgets(void) const{
	return m_widgets.size();
}

// Setters
inline void GUILayer::setID(const int id){
	m_id = id;
}

inline void GUILayer::setLayerName(const std::string& name){
	m_layerName = name;
}

// ================================================ //

#endif

// ================================================ //