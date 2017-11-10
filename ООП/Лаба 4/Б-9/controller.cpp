// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "leaftreeitem.hpp"
#include "treeitem.hpp"
#include "parenttreeitem.hpp"

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::startParentNode(std::string const & _text)
{
	if (_text.empty())
		throw std::logic_error(Messages::EmptyDescriptionText);

	auto item = std::make_unique<ParentTreeItem>(_text);
	ParentTreeItem * pItem = item.get();
	if (m_currNode.empty())
		m_roots.push_back(std::move(item));
	else
		m_currNode.back()->addNode(std::move(item));

	m_currNode.push_back(pItem);
}

/*****************************************************************************/

void Controller::addLeafNode(std::string const & _text)
{
	if (_text.empty())
		throw std::logic_error(Messages::EmptyDescriptionText);

	auto item = std::make_unique<LeafTreeItem>(_text);
	if (m_currNode.empty())
		m_roots.push_back(std::move(item));
	else
		m_currNode.back()->addNode(std::move(item));
}

/*****************************************************************************/

void Controller::endParentNode()
{
	if (m_currNode.empty())
		throw std::logic_error(Messages::DidNotOpenParentPreviously);
	
	m_currNode.pop_back();
}

/*****************************************************************************/

std::string Controller::getNodeDescription(NodePath const & _path) const
{
	return getNode(_path)->getName();
}

/*****************************************************************************/
int Controller::getNodeChildrenCount(NodePath const & _path) const
{
	return getNode(_path)->getTreeNodesCount();
}

/*****************************************************************************/
void Controller::makeInvisible(NodePath const & _path)
{
	getNode(_path)->setVisibility(false);
}

/*****************************************************************************/

void Controller::makeVisible(NodePath const & _path)
{
	getNode(_path)->setVisibility(true);
}

/*****************************************************************************/

void Controller::expand(NodePath const & _path)
{
	auto item = dynamic_cast<ParentTreeItem *>(getNode(_path));
	if (item)
		item->setExpandMarker(true);
}

/*****************************************************************************/

void Controller::collapse(NodePath const & _path)
{
	auto item = dynamic_cast<ParentTreeItem *>(getNode(_path));
	if (item)
		item->setExpandMarker(false);
}

/*****************************************************************************/

bool Controller::isVisible(NodePath const & _path) const
{
	return getNode(_path)->isVisible();
}

/*****************************************************************************/

bool Controller::isExpanded(NodePath const & _path) const
{
	auto item = dynamic_cast<ParentTreeItem *>(getNode(_path));
	if (item)
		return item->isExpanded();

	return false;
}

/*****************************************************************************/

bool Controller::isLeaf(NodePath const & _path) const
{
	auto item = dynamic_cast<LeafTreeItem *>(getNode(_path));
	return item != nullptr;
}

/*****************************************************************************/

void Controller::show(std::ostream & _o)
{
	for (auto const & node : m_roots)
		node->show(_o,0);
}

/*****************************************************************************/

TreeItem * Controller::getNode(NodePath const & _path) const
{
	if (_path.getIndexAtLevel(0) <= 0 || m_roots.size() < _path.getIndexAtLevel(0))
		throw std::logic_error(Messages::NodePathUnresolved);

	auto item = m_roots.at(_path.getIndexAtLevel(0) - 1).get();
	for (int i = 1; i < _path.getLevelsCount(); i++)
	{
		if (item->getTreeNodesCount() < _path.getIndexAtLevel(i) || _path.getIndexAtLevel(i) <= 0)
			throw std::logic_error(Messages::NodePathUnresolved);

		item = &item->getTreeNodeByIndex(_path.getIndexAtLevel(i) - 1);
	}

	return item;
}

/*****************************************************************************/