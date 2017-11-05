// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "recipe.hpp"
#include "messages.hpp"

Recipe::Recipe(std::string const & _name, std::string const & _description,std::string const & _author)
{
	m_name = _name;
	m_description = _description;
	m_author = _author;

	if (m_description.empty())
	{
		throw std::logic_error(Messages::EmptyRecipeDescription);
	}
		
	if (m_name.empty())
	{
		throw std::logic_error(Messages::EmptyRecipeName);
	}
		
	if (m_author.empty())
	{
		throw std::logic_error(Messages::EmptyRecipeAuthor);
	}
		
}

int Recipe::getIngredientsCount() const
{
	return m_ingredients.size();
}

void Recipe::addIngredient(std::string const & _ingredient_name, int _w)
{
	auto iterator = m_ingredients.find(_ingredient_name);
	if (iterator != m_ingredients.end())
	{
		throw std::logic_error(Messages::DuplicateIngredient);
	}
		
	if (_ingredient_name.empty())
	{
		throw std::logic_error(Messages::EmptyIngredientName);
	}
		
	if (_w < 1)
	{
		throw std::logic_error(Messages::IngredientValueMustBePositive);
	}
		
	m_ingredients.insert(std::make_pair(_ingredient_name, _w));
}

void Recipe::modifyIngredient(std::string const & _ingredient_name, int _newW)
{
	if (_ingredient_name.empty())
	{
		throw std::logic_error(Messages::EmptyIngredientName);
	}
		
	if (_newW < 1)
	{
		throw std::logic_error(Messages::IngredientValueMustBePositive);
	}
		
	auto iterator = m_ingredients.find(_ingredient_name);
	if (iterator == m_ingredients.end())
	{
		throw std::logic_error(Messages::IngredientCannotBeFound);
	}
		
	iterator->second = _newW;
}

int Recipe::getIngredientValue(std::string const & _ingredient_name) const
{
	if (_ingredient_name.empty())
	{
		throw std::logic_error(Messages::EmptyIngredientName);
	}
		
	auto iterator = m_ingredients.find(_ingredient_name);
	if (iterator == m_ingredients.end())
	{
		throw std::logic_error(Messages::IngredientCannotBeFound);
	}
		
	return iterator->second;
}

int Recipe::getCookStepsCount() const
{
	return m_cook_steps.size();
}

std::string const & Recipe::getCookStep(int _i) const
{
	if (_i < 0 || _i >= m_cook_steps.size())
	{
		throw std::logic_error(Messages::IndexOutOfRange);
	}
		
	return m_cook_steps[_i];
}

void Recipe::addCookStep(std::string const & _cook_step)
{
	if (_cook_step.empty())
	{
		throw std::logic_error(Messages::EmptyCookStep);
	}
		
	m_cook_steps.push_back(_cook_step);
}

bool Recipe::hasIngredient(std::string const & _ingredient_name) const
{
	return m_ingredients.find(_ingredient_name) != m_ingredients.end();
}