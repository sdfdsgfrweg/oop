// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "recipe.hpp"
#include "messages.hpp"

//----------------------------------------------------------------
//констуктор по умолчанию
Recipe::Recipe(
	std::string const & _nameOfRecipe,
	std::string const & _descOfRecipe,
	std::string const & _nameOfAuthor
)
//делегирующий конструктор
	: m_nameOfRecipe ( _nameOfRecipe )
	, m_descOfRecipe ( _descOfRecipe )
	, m_nameOfAuthor (_nameOfAuthor )
{
	//проверка переменных на корректность
	if (m_descOfRecipe.empty())
		throw std::logic_error(Messages::EmptyRecipeDescription);
		
	if (m_nameOfRecipe.empty())
		throw std::logic_error(Messages::EmptyRecipeName);
		
	if (m_nameOfAuthor.empty())
		throw std::logic_error(Messages::EmptyRecipeAuthor);
}

//----------------------------------------------------------------
//метод возвращающий размер набора ингредиентов
int Recipe::getIngredientsCount() const
{
	return m_setOfIngredients.size();
}

//----------------------------------------------------------------
//добавление ингредиента
void Recipe::addIngredient(std::string const & _ing, int _w)
{
	if (hasIngredient(_ing))
		throw std::logic_error(Messages::DuplicateIngredient);
		
	if (_ing.empty())
		throw std::logic_error(Messages::EmptyIngredientName);
		
	if (_w < 1)
		throw std::logic_error(Messages::IngredientValueMustBePositive);
		
	m_setOfIngredients.insert(std::make_pair(_ing, _w));
}

//----------------------------------------------------------------
//изменение веса ингредиента
void Recipe::modifyIngredient(std::string const & _ing, int _newW)
{
	if (_ing.empty())
		throw std::logic_error(Messages::EmptyIngredientName);
		
	if (_newW < 1)
		throw std::logic_error(Messages::IngredientValueMustBePositive);

	if (!hasIngredient(_ing))
		throw std::logic_error(Messages::IngredientCannotBeFound);

	m_setOfIngredients.find(_ing)->second = _newW;
}

//----------------------------------------------------------------
//получение веса ингредиента
int Recipe::getIngredientValue(std::string const & _ing) const
{
	if (_ing.empty())
		throw std::logic_error(Messages::EmptyIngredientName);
		
	if (!hasIngredient(_ing))
		throw std::logic_error(Messages::IngredientCannotBeFound);
		
	return m_setOfIngredients.find(_ing)->second;
}

//----------------------------------------------------------------
//метод возвращающие количество шагов приготовления
int Recipe::getCookStepsCount() const
{
	return m_stepsOfCooking.size();
}

//----------------------------------------------------------------
//метод возвращающий определенный шаг
std::string const & Recipe::getCookStep(int _i) const
{
	if (_i < 0 || _i >= m_stepsOfCooking.size())
		throw std::logic_error(Messages::IndexOutOfRange);
		
	return m_stepsOfCooking[_i];
}

//----------------------------------------------------------------
//добавление шага приготовления
void Recipe::addCookStep(std::string const & _step)
{
	if (_step.empty())
		throw std::logic_error(Messages::EmptyCookStep);
		
	m_stepsOfCooking.push_back(_step);
}

//----------------------------------------------------------------
//проверка наличия ингредиента
bool Recipe::hasIngredient(std::string const & _ing) const
{
	return m_setOfIngredients.find(_ing) != m_setOfIngredients.end();
}

//----------------------------------------------------------------