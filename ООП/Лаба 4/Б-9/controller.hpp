// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "nodepath.hpp"

#include <string>
#include <ostream>
#include <memory>

/*****************************************************************************/

class TreeItem;
class ParentTreeItem;

class Controller
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Controller();

	Controller(const Controller &) = delete;

	Controller & operator = (const Controller &) = delete;

	~Controller();

	/*-----------------------------------------------------------------*/

	void startParentNode(std::string const & _text);

	void addLeafNode(std::string const & _text);

	void endParentNode();

	/*-----------------------------------------------------------------*/

	std::string getNodeDescription(NodePath const & _path) const;

	int getNodeChildrenCount(NodePath const & _path) const;

	/*-----------------------------------------------------------------*/

	void makeInvisible(NodePath const & _path);

	void makeVisible(NodePath const & _path);

	void expand(NodePath const & _path);

	void collapse(NodePath const & _path);

	/*-----------------------------------------------------------------*/

	bool isVisible(NodePath const & _path) const;

	bool isExpanded(NodePath const & _path) const;

	bool isLeaf(NodePath const & _path) const;

	/*-----------------------------------------------------------------*/

	void show(std::ostream & _o);

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	TreeItem * getNode(NodePath const & _path) const;

	std::vector<std::unique_ptr<TreeItem> > m_roots;
	
	std::vector<ParentTreeItem *> m_currNode;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _CONTROLLER_HPP_