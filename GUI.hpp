// ================================================ //

#ifndef __GUI_HPP__
#define __GUI_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Widget.hpp"

// ================================================ //

class GUILayer;

// ================================================ //

typedef std::list<std::shared_ptr<Widget>> WidgetList;
typedef std::vector<std::shared_ptr<GUILayer>> GUILayerList;

// ================================================ //
/* An object for each game state to process all GUI operations */
class GUI
{
public:
	explicit GUI(void);
	virtual ~GUI(void);

	void addLayer(std::shared_ptr<GUILayer> layer);

	// Setter functions
	void setCurrentLayer(const int n);

	// Getter functions
	GUILayer* getCurrentLayer(void) const;

	virtual void update(double dt) = 0;

private:
	GUILayerList m_layers;
	GUILayer* m_pCurrentLayer;
};

// ================================================ //

inline void GUI::addLayer(std::shared_ptr<GUILayer> layer){
	m_layers.push_back(layer);
}

inline void GUI::setCurrentLayer(const int n){
	m_pCurrentLayer = m_layers[n].get();
}

inline GUILayer* GUI::getCurrentLayer(void) const{
	return m_pCurrentLayer;
}

// ================================================ //
// ================================================ //

class GUILayer
{
public:
	explicit GUILayer(void);
	virtual ~GUILayer(void);

	void addWidget(std::shared_ptr<Widget> widget);

	virtual void render(void);
	virtual void update(double dt) = 0;

private:
	WidgetList m_widgets;
};

// ================================================ //

inline void GUILayer::addWidget(std::shared_ptr<Widget> widget){
	m_widgets.push_back(widget);
}

// ================================================ //

#endif

// ================================================ //