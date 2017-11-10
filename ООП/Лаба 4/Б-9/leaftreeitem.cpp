// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "leaftreeitem.hpp"
#include "messages.hpp"

/*****************************************************************************/

LeafTreeItem::LeafTreeItem(std::string const & _nodeName)
	: TreeItem(_nodeName)
{}

/*****************************************************************************/

TreeItem & LeafTreeItem::getTreeNodeByIndex(int _index) const
{
	throw std::logic_error(Messages::TreeItemHasNotChildren);
}

/*****************************************************************************/

int LeafTreeItem::getTreeNodesCount() const
{
	return 0;
}

/*****************************************************************************/