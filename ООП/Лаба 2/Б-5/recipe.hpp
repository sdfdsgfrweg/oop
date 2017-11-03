// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _RECIPE_HPP_
#define _RECIPE_HPP_

/*****************************************************************************/

#include <string>
#include <map>
#include <vector>

/*****************************************************************************/


class Recipe
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Recipe(
		std::string const & _recipeName,
		std::string const & _recipeDesc,
		std::string const & _authorName
	);

	Recipe(Recipe const & _recipe) = delete;

	Recipe(Recipe && _recipe) = delete;

	Recipe & operator = (Recipe && _recipe) = delete;

	Recipe & operator = (Recipe const & _recipe) = delete;

	~Recipe() = default;

	std::string	const & getAuthor() const;

	std::string const & getName() const;

	std::string const & getDescription() const;

	int getIngredientsCount() const;

	//------------------------------------------

	typedef std::map<std::string, int>::const_iterator Iterator;

	Iterator beginIngredients() const;

	Iterator endIngredients() const;

	bool hasIngredient(std::string const & _ingredientName) const;

	void addIngredient(
		std::string const & _ingredientName,
		int _weigth
	);

	void modifyIngredient(
		std::string const & _ingredientName,
		int _newWeigth
	);

	int getIngredientValue(std::string const & _ingredientName) const;

	int getCookStepsCount() const;

	std::string const & getCookStep(int _index) const;

	void addCookStep(std::string const & _cookStep);

	bool operator == (Recipe const & _r) const;

	bool operator != (Recipe const & _r) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string m_authorName;

	std::string m_recipeName;

	std::string m_recipeDesc;

	std::vector<std::string> m_cookSteps;

	std::map<std::string /* name */, int /*weigth*/> m_ingredients;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const & Recipe::getDescription() const
{
	return m_recipeDesc;
}

/*****************************************************************************/

inline
std::string	const & Recipe::getAuthor() const
{
	return m_authorName;
}

/*****************************************************************************/

inline
std::string const & Recipe::getName() const
{
	return m_recipeName;
}

/*****************************************************************************/

inline
bool Recipe::operator == (Recipe const & _r) const
{
	return m_authorName == _r.m_authorName
		&& m_recipeDesc == _r.m_recipeDesc
		&& m_recipeName == _r.m_recipeName
		&& m_ingredients == _r.m_ingredients
		&& m_cookSteps == _r.m_cookSteps;
}

/*****************************************************************************/

inline
bool Recipe::operator != (Recipe const & _r) const
{
	return !(*this == _r);
}

/*****************************************************************************/

inline
Recipe::Iterator Recipe::beginIngredients() const
{
	return m_ingredients.cbegin();
}

/*****************************************************************************/

inline
Recipe::Iterator Recipe::endIngredients() const
{
	return m_ingredients.cend();
}

/*****************************************************************************/


#endif // _RECIPE_HPP_
