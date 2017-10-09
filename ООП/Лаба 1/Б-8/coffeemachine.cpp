// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "coffeemachine.hpp"

#include <stdexcept>

/*****************************************************************************/

// TODO ...

/*****************************************************************************/

CoffeeMachine::CoffeeMachine(
	int _maxBeansAmount,
	int _maxWaterVolume,
	int _maxCoffeePortions
)
	: m_maxBeansAmount(_maxBeansAmount)
	, m_maxCoffeePortions(_maxCoffeePortions)
	, m_maxWaterVolume(_maxWaterVolume)
	, m_currentBeansAmount(0)
	, m_currentCoffeePortions(_maxCoffeePortions)
	, m_currentWaterVolume(0)
{
	if (m_maxBeansAmount < 1 || m_maxCoffeePortions < 1 || m_maxWaterVolume < 1)
		throw std::logic_error("Incorrect initial parameters");
}

int CoffeeMachine::loadBeans()
{
	int difference = m_maxBeansAmount - m_currentBeansAmount;
	m_currentBeansAmount = m_maxBeansAmount;
	return difference;
}

int CoffeeMachine::loadWater()
{
	int difference = m_maxWaterVolume - m_currentWaterVolume;
	m_currentWaterVolume = m_maxWaterVolume;
	return difference;
}

void CoffeeMachine::cleanWaste()
{
	m_currentCoffeePortions = m_maxCoffeePortions;
}

bool CoffeeMachine::makeCoffee(Recipe _r, Strength _s)
{
	if (m_currentCoffeePortions == 0)
		return false;

	switch (_r)
	{
	case CoffeeMachine::Espresso:
		if (m_currentWaterVolume - WATER_FOR_ESPRESSO < 0)
			return false;
		else
			m_currentWaterVolume -= WATER_FOR_ESPRESSO;
		break;
	case CoffeeMachine::Americano:
		if (m_currentWaterVolume - WATER_FOR_AMERICANO < 0)
			return false;
		else
			m_currentWaterVolume -= WATER_FOR_AMERICANO;
		break;
	default:
		break;
	}

	switch (_s)
	{
	case CoffeeMachine::Light:
		if (m_currentBeansAmount - BEANS_FOR_LIGHT < 0)
			return false;
		else
			m_currentBeansAmount -= BEANS_FOR_LIGHT;
		break;
	case CoffeeMachine::Medium:
		if (m_currentBeansAmount - BEANS_FOR_MEDIUM < 0)
			return false;
		else
			m_currentBeansAmount -= BEANS_FOR_MEDIUM;
		break;
	case CoffeeMachine::Strong:
		if (m_currentBeansAmount - BEANS_FOR_STRONG < 0)
			return false;
		else
			m_currentBeansAmount -= BEANS_FOR_STRONG;
		break;
	default:
		break;
	}

	m_currentCoffeePortions--;

	return true;
}

void CoffeeMachine::washMachine()
{
	if (m_currentWaterVolume - WATER_FOR_WASHING > 0)
		m_currentWaterVolume -= WATER_FOR_WASHING;
	else
		m_currentWaterVolume = 0;
}

CoffeeMachine::operator bool () const
{
	if (m_currentCoffeePortions <= 0 || m_currentBeansAmount < 12 || m_currentWaterVolume < 200) return false;
	
	return true;
}