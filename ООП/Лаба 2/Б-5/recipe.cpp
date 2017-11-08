// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "recipe.hpp"
#include "messages.hpp"

//----------------------------------------------------------------
//���������� �� ���������
Recipe::Recipe(
	std::string const & _nameOfRecipe,
	std::string const & _descOfRecipe,
	std::string const & _nameOfAuthor
)
//������������ �����������
	: m_nameOfRecipe ( _nameOfRecipe )
	, m_descOfRecipe ( _descOfRecipe )
	, m_nameOfAuthor (_nameOfAuthor )
{
	//�������� ���������� �� ������������
	if (m_descOfRecipe.empty())
		throw std::logic_error(Messages::EmptyRecipeDescription);
		
	if (m_nameOfRecipe.empty())
		throw std::logic_error(Messages::EmptyRecipeName);
		
	if (m_nameOfAuthor.empty())
		throw std::logic_error(Messages::EmptyRecipeAuthor);
}

//----------------------------------------------------------------
//����� ������������ ������ ������ ������������
int Recipe::getIngredientsCount() const
{
	return m_setOfIngredients.size();
}

//----------------------------------------------------------------
//���������� �����������
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
//��������� ���� �����������
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
//��������� ���� �����������
int Recipe::getIngredientValue(std::string const & _ing) const
{
	if (_ing.empty())
		throw std::logic_error(Messages::EmptyIngredientName);
		
	if (!hasIngredient(_ing))
		throw std::logic_error(Messages::IngredientCannotBeFound);
		
	return m_setOfIngredients.find(_ing)->second;
}

//----------------------------------------------------------------
//����� ������������ ���������� ����� �������������
int Recipe::getCookStepsCount() const
{
	return m_stepsOfCooking.size();
}

//----------------------------------------------------------------
//����� ������������ ������������ ���
std::string const & Recipe::getCookStep(int _i) const
{
	if (_i < 0 || _i >= m_stepsOfCooking.size())
		throw std::logic_error(Messages::IndexOutOfRange);
		
	return m_stepsOfCooking[_i];
}

//----------------------------------------------------------------
//���������� ���� �������������
void Recipe::addCookStep(std::string const & _step)
{
	if (_step.empty())
		throw std::logic_error(Messages::EmptyCookStep);
		
	m_stepsOfCooking.push_back(_step);
}

//----------------------------------------------------------------
//�������� ������� �����������
bool Recipe::hasIngredient(std::string const & _ing) const
{
	return m_setOfIngredients.find(_ing) != m_setOfIngredients.end();
}

//----------------------------------------------------------------