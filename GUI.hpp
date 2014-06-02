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
		BEGIN_SELECT,
		FINISH_SELECT
	};

	void addLayer(std::shared_ptr<GUILayer> layer);
	
	// Setter functions
	void setCurrentLayer(const int n);
	void setNavigationMode(const int mode);
	void setMousePos(const int x, const int y);
	void setSelectedWidget(const int n);

	// Getter functions
	GUILayer* getCurrentLayer(void) const;
	const int getNavigationMode(void) const;
	const int getSelectedWidget(void) const;

	virtual void renderSelector(void);
	virtual void update(double dt);

	static std::string m_buttonTheme;

private:
	GUILayerList m_layers;
	GUILayer* m_pCurrentLayer;
	int m_selectedWidget;
	int m_navMode;
	int m_mouseX, m_mouseY;

};

// ================================================ //

inline void GUI::addLayer(std::shared_ptr<GUILayer> layer){
	m_layers.push_back(layer);
}

// Setters
inline void GUI::setCurrentLayer(const int n){
	m_pCurrentLayer = m_layers[n].get();
}

inline void GUI::setNavigationMode(const int mode){
	m_navMode = mode;
}

inline void GUI::setMousePos(const int x, const int y){
	m_mouseX = x; m_mouseY = y;
}

inline void GUI::setSelectedWidget(const int n){
	if (n != Widget::NONE) m_selectedWidget = n;
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
	void parse(Config& c, const int widgetType, const std::vector<std::string>& names);

	// Getter functions
	Widget* getWidget(const int n) const;
	const int getNumWidgets(void) const;

	// Setter functions
	void setLayerName(const std::string& name);

	virtual void render(void);
	virtual void update(double dt) = 0;

private:
	WidgetList m_widgets;
	std::string m_layerName;
};

// ================================================ //

inline void GUILayer::addWidget(std::shared_ptr<Widget> widget){
	m_widgets.push_back(widget);
}

// Getters
inline Widget* GUILayer::getWidget(const int n) const{
	return m_widgets[n].get();
}

inline const int GUILayer::getNumWidgets(void) const{
	return m_widgets.size();
}

// Setters
inline void GUILayer::setLayerName(const std::string& name){
	m_layerName = name;
}

// ================================================ //

#endif

// ================================================ //