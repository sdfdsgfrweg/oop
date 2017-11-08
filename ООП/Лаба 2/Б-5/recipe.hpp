// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _RECIPE_HPP_
#define _RECIPE_HPP_

#include <string>
#include <map>
#include <vector>

class Recipe
{

public:
	//----------------------------------------------------------------
	//������������ � ����������
	
	Recipe( std::string const & _name, std::string const & _description, std::string const & _author);
	Recipe(Recipe & _rececipe) = delete;
	Recipe(Recipe && _rececipe) = delete;
	Recipe & operator = (Recipe && _rececipe) = delete;
	Recipe & operator = (Recipe & _rececipe) = delete;
	~Recipe() = default;
	
	//----------------------------------------------------------------
	//�������
	typedef std::map<std::string, int>::const_iterator Iterator;

	//----------------------------------------------------------------
	std::string	const & getAuthor() const;
	std::string const & getName() const;
	std::string const & getDescription() const;

	bool operator == (Recipe const & _rec) const;
	bool operator != (Recipe const & _rec) const;

	Iterator beginIngredients() const;
	Iterator endIngredients() const;

	//----------------------------------------------------------------
	//��������� ������
	void addIngredient(std::string const & _ing,int _w);
	void modifyIngredient(std::string const & _ing,int _newW);
	void addCookStep(std::string const & _step);
	
	int getIngredientsCount() const;
	int getIngredientValue(std::string const & _ing) const;
	int getCookStepsCount() const;
	
	std::string const & getCookStep(int _i) const;
	bool hasIngredient(std::string const & _ing) const;

	//----------------------------------------------------------------
	
private:

	//----------------------------------------------------------------
	std::string m_nameOfAuthor;
	std::string m_nameOfRecipe;
	std::string m_descOfRecipe;
	//----------------------------------------------------------------
	std::vector<std::string> m_stepsOfCooking;
	std::map<std::string, int> m_setOfIngredients;
	//----------------------------------------------------------------
};

//----------------------------------------------------------------
//������ � ����� ������ �������� �������
inline std::string const & Recipe::getDescription() const
{
	return m_descOfRecipe;
}

//----------------------------------------------------------------
//������ � ����� ������ ����� ������
inline std::string const & Recipe::getAuthor() const
{
	return m_nameOfAuthor;
}

//----------------------------------------------------------------
//������ � ����� ������ �������� �������
inline std::string const & Recipe::getName() const
{
	return m_nameOfRecipe;
}

//----------------------------------------------------------------
//�������� ����������� ���������
inline bool Recipe::operator == (Recipe const & _rec) const
{
	return (m_nameOfAuthor == _rec.m_nameOfAuthor 
		&&  m_descOfRecipe == _rec.m_descOfRecipe 
		&& m_nameOfRecipe == _rec.m_nameOfRecipe
		&& m_setOfIngredients == _rec.m_setOfIngredients 
		&& m_stepsOfCooking == _rec.m_stepsOfCooking);
}

//----------------------------------------------------------------
//�������� ����������� �����������
inline bool Recipe::operator != (Recipe const & _rec) const
{
	return !(*this == _rec);
}

//----------------------------------------------------------------
//����������� �������� ������ ����������
inline Recipe::Iterator Recipe::beginIngredients() const
{
	return m_setOfIngredients.cbegin();
}

//----------------------------------------------------------------
//����������� �������� ����� ����������
inline Recipe::Iterator Recipe::endIngredients() const
{
	return m_setOfIngredients.cend();
}

//----------------------------------------------------------------
#endif // _RECIPE_HPP_
