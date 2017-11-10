// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "treeitem.hpp"

/*****************************************************************************/

TreeItem::TreeItem(
	std::string const & _nodeName
)
	: m_nodeName(_nodeName)
	, m_visibilityMarker(true)
{}

/*****************************************************************************/

TreeItem::~TreeItem() = default;

/*****************************************************************************/

void TreeItem::show(std::ostream & _s, int _level) const
{
	if (m_visibilityMarker)
	{
		for (int i = 0; i < _level; i++)
			_s << "\t";

		_s << m_nodeName << std::endl;
		
		for (int i = 0; i < getTreeNodesCount(); i++)
			getTreeNodeByIndex(i).show(_s, _level + 1);
	}
}

/*****************************************************************************/