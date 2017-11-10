// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TREEITEM_HPP_
#define _TREEITEM_HPP_

/*****************************************************************************/

#include <string>

/*****************************************************************************/

class TreeItem
{

	/*-----------------------------------------------------------------*/
public:

	TreeItem(std::string const & _nodeName);

	virtual ~TreeItem();

	virtual int getTreeNodesCount() const = 0;

	virtual TreeItem & getTreeNodeByIndex(int _index) const = 0;
	
	void show(std::ostream & _s, int _level) const;

	std::string const & getName() const;

	bool isVisible() const;

	void setVisibility(bool _state);

private:

	std::string m_nodeName;

	bool m_visibilityMarker;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline
std::string const &
TreeItem::getName() const
{
	return m_nodeName;
}

/*****************************************************************************/

inline
bool TreeItem::isVisible() const
{
	return m_visibilityMarker;
}

/*****************************************************************************/

inline
void TreeItem::setVisibility(bool _state)
{
	m_visibilityMarker = _state;
}

/*****************************************************************************/

#endif // _TREEITEM_HPP_