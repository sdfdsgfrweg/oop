// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _RECIPE_HPP_
#define _RECIPE_HPP_

#include <string>
#include <unordered_map>
#include <vector>

class Recipe
{

public:

	Recipe( std::string const & _name, std::string const & _description, std::string const & _author);
	Recipe(Recipe & _recipe) = delete;
	Recipe(Recipe && _recipe) = delete;
	Recipe & operator = (Recipe && _recipe) = delete;
	Recipe & operator = (Recipe & _recipe) = delete;
	~Recipe() = default;
	std::string	const & getAuthor() const;
	std::string const & getName() const;
	std::string const & getDescription() const;
	int getIngredientsCount() const;
	std::unordered_map<std::string, int>::const_iterator beginIngredients() const;
	std::unordered_map<std::string, int>::const_iterator endIngredients() const;
	bool hasIngredient(std::string const & _ingredient_name) const;
	void addIngredient(std::string const & _ingredient_name,int _weigth);
	void modifyIngredient(std::string const & _ingredient_name,int _newWeigth);
	int getIngredientValue(std::string const & _ingredient_name) const;
	int getCookStepsCount() const;
	std::string const & getCookStep(int _index) const;
	void addCookStep(std::string const & _cook_step);
	bool operator == (Recipe const & _r) const;
	bool operator != (Recipe const & _r) const;

private:
	std::string m_author;
	std::string m_name;
	std::string m_description;
	std::vector<std::string> m_cook_steps;
	std::unordered_map<std::string, int> m_ingredients;

};

inline std::string const &
Recipe::getDescription() const
{
	return m_description;
}

inline std::string const &
Recipe::getAuthor() const
{
	return m_author;
}

inline std::string const &
Recipe::getName() const
{
	return m_name;
}

inline bool Recipe::operator == (Recipe const & _r) const
{
	if (m_author == _r.m_author && m_description == _r.m_description && m_name == _r.m_name
		&& m_ingredients == _r.m_ingredients && m_cook_steps == _r.m_cook_steps)
		return true;
	else
		return false;
}

inline bool Recipe::operator != (Recipe const & _r) const
{
	return !(*this == _r);
}

inline std::unordered_map<std::string, int>::const_iterator
Recipe::beginIngredients() const
{
	return m_ingredients.cbegin();
}

inline std::unordered_map<std::string, int>::const_iterator
Recipe::endIngredients() const
{
	return m_ingredients.cend();
}

#endif // _RECIPE_HPP_
