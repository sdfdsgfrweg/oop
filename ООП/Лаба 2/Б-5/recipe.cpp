// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "recipe.hpp"
#include "messages.hpp"

/*****************************************************************************/

Recipe::Recipe(
	std::string const & _recipeName, 
	std::string const & _recipeDesc,
	std::string const & _authorName
)
	: m_recipeName(_recipeName)
	, m_recipeDesc(_recipeDesc)
	, m_authorName(_authorName)
{
	if (m_recipeDesc.empty())
		throw std::logic_error(Messages::EmptyRecipeDescription);

	if (m_recipeName.empty())
		throw std::logic_error(Messages::EmptyRecipeName);

	if (m_authorName.empty())
		throw std::logic_error(Messages::EmptyRecipeAuthor);
}

/*****************************************************************************/

int Recipe::getIngredientsCount() const
{
	return m_ingredients.size();
}

/*****************************************************************************/

bool Recipe::hasIngredient(std::string const & _ingredientName) const
{
	return m_ingredients.find(_ingredientName) != m_ingredients.end();
}

/*****************************************************************************/

void Recipe::addIngredient(std::string const & _ingredientName, int _weigth)
{
	auto it = m_ingredients.find(_ingredientName);
	if (it != m_ingredients.end())
		throw std::logic_error(Messages::DuplicateIngredient);

	if (_ingredientName.empty())
		throw std::logic_error(Messages::EmptyIngredientName);

	if (_weigth < 1)
		throw std::logic_error(Messages::IngredientValueMustBePositive);

	m_ingredients.insert(std::make_pair(_ingredientName, _weigth));
}

/*****************************************************************************/

void Recipe::modifyIngredient(std::string const & _ingredientName, int _newWeigth)
{
	if (_ingredientName.empty())
		throw std::logic_error(Messages::EmptyIngredientName);

	if (_newWeigth < 1)
		throw std::logic_error(Messages::IngredientValueMustBePositive);

	auto it = m_ingredients.find(_ingredientName);
	if (it == m_ingredients.end())
		throw std::logic_error(Messages::IngredientCannotBeFound);

	it->second = _newWeigth;
}

/*****************************************************************************/

int Recipe::getIngredientValue(std::string const & _ingredientName) const
{
	if (_ingredientName.empty())
		throw std::logic_error(Messages::EmptyIngredientName);

	auto it = m_ingredients.find(_ingredientName);
	if (it == m_ingredients.end())
		throw std::logic_error(Messages::IngredientCannotBeFound);

	return it->second;
}

/*****************************************************************************/

int Recipe::getCookStepsCount() const
{
	return m_cookSteps.size();
}

/*****************************************************************************/

std::string const & Recipe::getCookStep(int _index) const
{
	if (_index < 0 || _index >= m_cookSteps.size())
		throw std::logic_error(Messages::IndexOutOfRange);

	return m_cookSteps[_index];
}

/*****************************************************************************/

void Recipe::addCookStep(std::string const & _cookStep)
{
	if (_cookStep.empty())
		throw std::logic_error(Messages::EmptyCookStep);

	m_cookSteps.push_back(_cookStep);
}

/*****************************************************************************/