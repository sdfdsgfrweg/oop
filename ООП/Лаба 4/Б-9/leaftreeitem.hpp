// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _LEAFTREEITEM_HPP_
#define _LEAFTREEITEM_HPP_

/*****************************************************************************/

#include "treeitem.hpp"

/*****************************************************************************/

class LeafTreeItem
	: public TreeItem
{

	/*-----------------------------------------------------------------*/
public:

	LeafTreeItem(std::string const & _nodeName);

	~LeafTreeItem() = default;

	TreeItem & getTreeNodeByIndex(int _index) const override;

	int getTreeNodesCount() const override;
		
	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _LEAFTREEITEM_HPP_