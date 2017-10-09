// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _COFFEEMACHINE_HPP_
#define _COFFEEMACHINE_HPP_

/*****************************************************************************/


class CoffeeMachine
{

/*-----------------------------------------------------------------*/

public:

/*------------------------------------------------------------------*/

	enum Recipe { Espresso, Americano };

	enum Strength { Light, Medium, Strong };

	static const int WATER_FOR_ESPRESSO = 120, WATER_FOR_AMERICANO = 200;
	static const int WATER_FOR_WASHING = 500;
	static const int BEANS_FOR_LIGHT = 4, BEANS_FOR_MEDIUM = 8, BEANS_FOR_STRONG = 12;

public:

	CoffeeMachine(
		int _maxBeansAmount,
		int _maxWaterVolume,
		int _maxCoffeePortions
	);

	~CoffeeMachine() = default;

	int getBeansWeight() const;

	int getWaterVolume() const;

	int getFreeWastePortions() const;

	int loadBeans();

	int loadWater();

	void cleanWaste();

	bool makeCoffee(Recipe _r, Strength _s);

	void washMachine();

	operator bool () const;

/*------------------------------------------------------------------*/

private:

	int m_maxBeansAmount;
	int m_currentBeansAmount;

	int m_maxWaterVolume;
	int m_currentWaterVolume;

	int m_maxCoffeePortions;
	int m_currentCoffeePortions;
/*------------------------------------------------------------------*/

};


inline int CoffeeMachine::getBeansWeight() const
{
	return m_currentBeansAmount;
}

inline int CoffeeMachine::getWaterVolume() const
{
	return m_currentWaterVolume;
}

inline int CoffeeMachine::getFreeWastePortions() const
{
	return m_currentCoffeePortions;
}

/*****************************************************************************/

#endif //  _COFFEEMACHINE_HPP_
