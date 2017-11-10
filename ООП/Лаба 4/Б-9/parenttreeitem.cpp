// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "parenttreeitem.hpp"
#include "messages.hpp"

/*****************************************************************************/

ParentTreeItem::ParentTreeItem(
	std::string const & _nodeName,
	bool _isExpanded
)
	: TreeItem(_nodeName)
	, m_expandMarker(_isExpanded)
{}

/*****************************************************************************/

TreeItem & ParentTreeItem::getTreeNodeByIndex(int _index) const
{
	if (m_expandMarker)
		return * m_nodes[_index];
	else
		throw std::logic_error(Messages::TreeItemHasNotChildren);
}

/*****************************************************************************/

int ParentTreeItem::getTreeNodesCount() const
{
	if (m_expandMarker)
		return m_nodes.size();
	else
		return 0;
}

/*****************************************************************************/
void ParentTreeItem::addNode(std::unique_ptr<TreeItem> _node)
{
	m_nodes.push_back(std::move(_node));
}

/*****************************************************************************/