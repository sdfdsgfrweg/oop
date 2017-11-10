// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _PARENTTREEITEM_HPP_
#define _PARENTTREEITEM_HPP_

/*****************************************************************************/

#include "treeitem.hpp"
#include <memory>
#include <vector>

/*****************************************************************************/

class ParentTreeItem
	: public TreeItem
{

	/*-----------------------------------------------------------------*/
 
public:

	ParentTreeItem(
		std::string const & _nodeName,
		bool _isOpen = true
	);

	~ParentTreeItem() = default;

	TreeItem & getTreeNodeByIndex(int _index) const override;

	int getTreeNodesCount() const override;

	void addNode(std::unique_ptr<TreeItem>_node);

	void setExpandMarker(bool _state);

	bool isExpanded() const;

private:

	std::vector<std::unique_ptr<TreeItem> > m_nodes;

	bool m_expandMarker;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline
bool ParentTreeItem::isExpanded() const
{
	return m_expandMarker == true;
}

/*****************************************************************************/

inline
void ParentTreeItem::setExpandMarker(bool _state)
{
	m_expandMarker = _state;
}

/*****************************************************************************/

#endif // _PARENTTREEITEM_HPP_