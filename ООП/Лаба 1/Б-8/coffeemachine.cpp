// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "coffeemachine.hpp"

#include <stdexcept>

/*****************************************************************************/

CoffeeMachine::CoffeeMachine(int _maxBeansNumber,int _maxWaterLiters,int _maxCoffeeCups)
{
	//��������� ������� ������
	if (_maxBeansNumber < 1 || _maxCoffeeCups < 1 || _maxWaterLiters < 1) throw std::logic_error("Incorrect initial parameters");
	
	//�������������� ����������
	maxBeansNumber = _maxBeansNumber;
	maxCoffeeCups = _maxCoffeeCups;
	maxWaterLiters = _maxWaterLiters;
	availableBeansNumber = availableWaterLiters = 0;
	availableCoffeeCups = _maxCoffeeCups;
}

/*****************************************************************************/

int CoffeeMachine::loadBeans()
{
	//�������� ������� � ��������� �����
	int diff = maxBeansNumber - availableBeansNumber;
	availableBeansNumber = maxBeansNumber;
	return diff;
}

/*****************************************************************************/

int CoffeeMachine::loadWater()
{
	//�������� ������� � ��������� ����
	int diff = maxWaterLiters - availableWaterLiters;
	availableWaterLiters = maxWaterLiters;
	return diff;
}

/*****************************************************************************/

void CoffeeMachine::cleanWaste()
{
	//������� ����� ��� �������
	availableCoffeeCups = maxCoffeeCups;
}

/*****************************************************************************/

bool CoffeeMachine::makeCoffee(Recipe _coffeeRecipe, Strength _coffeeStrength)
{
	//���� ��� ����� ��� �������, �� ���������� false
	if (availableCoffeeCups == 0) return false;
		
	switch (_coffeeRecipe)
	{
		//��������� ������� ��� ��������
	case CoffeeMachine::Espresso:
		if (availableWaterLiters - WATER_FOR_ESPRESSO < 0) return false;
		else availableWaterLiters -= WATER_FOR_ESPRESSO;
		break;
		//��������� ������� ��� ���������
	case CoffeeMachine::Americano:
		if (availableWaterLiters - WATER_FOR_AMERICANO < 0) return false;
		else availableWaterLiters -= WATER_FOR_AMERICANO;
		break;
	default:
		break;
	}

	switch (_coffeeStrength)
	{
		//��������� ���-�� ����� ��� ������ ��������
	case CoffeeMachine::Light:
		if (availableBeansNumber - BEANS_FOR_LIGHT < 0) return false;
		else availableBeansNumber -= BEANS_FOR_LIGHT;
		break;

		//��������� ���-�� ����� ��� ������� ��������
	case CoffeeMachine::Medium:
		if (availableBeansNumber - BEANS_FOR_MEDIUM < 0) return false;
		else availableBeansNumber -= BEANS_FOR_MEDIUM;
		break;

		//��������� ���-�� ����� ��� ������� ��������
	case CoffeeMachine::Strong:
		if (availableBeansNumber - BEANS_FOR_STRONG < 0) return false;
		else availableBeansNumber -= BEANS_FOR_STRONG;
		break;
	default:
		break;
	}

	//��������� ���-�� ��������� ����� ����
	availableCoffeeCups--;
	return true;
}

/*****************************************************************************/

void CoffeeMachine::washMachine()
{
	//��������� ���-�� ���� ��� �����
	if (availableWaterLiters - WATER_FOR_WASHING > 0) availableWaterLiters -= WATER_FOR_WASHING;
	else availableWaterLiters = 0;
}

/*****************************************************************************/

CoffeeMachine::operator bool () const
{
	//��������� ����� �� ������� ����� ���� ������ ���� � ����� ��������
	if (availableCoffeeCups <= 0 || availableBeansNumber < 12 || availableWaterLiters < 200) return false;
	return true;
}

/*****************************************************************************/