#include "testslib.hpp"
#include "flowering_houseplant.hpp"
#include "foliar_houseplant.hpp"
#include "fruiting_houseplant.hpp"
#include "artificial_houseplant.hpp"
#include "room.hpp"
#include "message.hpp"
#include "house_owner.hpp"

DECLARE_OOP_TEST(test_foliar_houseplant)
{
	//��������� �� ������ ���
	ASSERT_THROWS(
		FoliarHouseplant fh("",1,1),
		Messages::EmptyHouseplantName
	);
	//��������� �� ������������ ������ ������
	ASSERT_THROWS(
		FoliarHouseplant fh("Plant",0,1),
		Messages::InvalidWateringNumber
	);
	//��������� �� ������������� ������
	ASSERT_THROWS(
		FoliarHouseplant fh("Plant",1,-1),
		Messages::InvalidBeginningHeight
	);

	//���������� �������� ���������� ������ : ���������� ����������� ������������ ������
	//�������� � ����� ������ ���� 2
	{
		Room r;
		r.
		PlantOwner po(&r);
		FoliarHouseplant fh("Plant", 1, 245);

		fh.setPlantOwner(&po);
		r.addHouseplant(std::make_unique<FoliarHouseplant>(fh));

		assert(r.�ountHouseplants() == 1);
		for (int i = 0; i < 6; i++)
		{
			fh.daySkip();
			fh.water();
		}
		assert(r.�ountHouseplants() == 2);
	}
	
	//���������� �������� � ���������� �������, ����� �������� ����� ���� ��������
	//����� �������� ��� ����������, �� � ����� ������ �������� 2 ��������
	{
		Room r;
		PlantOwner po(&r);
		FoliarHouseplant fh("Plant", 2, 245);

		fh.setPlantOwner(&po);
		r.addHouseplant(std::make_unique<FoliarHouseplant>(fh));

		assert(r.�ountHouseplants() == 1);
		for (int i = 0; i < 6; i++)
		{
			fh.daySkip();
			fh.water();
		}
		assert(r.�ountHouseplants() == 2);
	}

	//�������� � ������ �������
	//����������� ����� ������
	//�������� ������ �������� ���� � �� �������
	{
		Room r;
		PlantOwner po(&r);
		FoliarHouseplant fh("Plant", 3, 245);

		fh.setPlantOwner(&po);
		r.addHouseplant(std::make_unique<FoliarHouseplant>(fh));

		assert(r.�ountHouseplants() == 1);
		for (int i = 0; i < 6; i++)
		{
			fh.daySkip();
			fh.water();
		}
		assert(r.�ountHouseplants() == 1);
	}
}

DECLARE_OOP_TEST(test_artificial_houseplant)
{
	//��������� �� ������ ���
	ASSERT_THROWS(
		ArtificialHouseplant ah("", 7),
		Messages::EmptyHouseplantName
	);
	//��������� �� ������������ ������ ������
	ASSERT_THROWS(
		ArtificialHouseplant ah("Plant", 0),
		Messages::InvalidWateringNumber
	);
	Room r;
	ArtificialHouseplant ah("Plant", 2);

	r.addHouseplant(std::make_unique<ArtificialHouseplant>(ah));
	//�������� ������ ������������� �������� : ������ �������� ������ �� �������
	ah.water();
}

DECLARE_OOP_TEST(test_fruiting_houseplant_functional)
{
	//��������� �������� ������ ������������ :
	// - ������ ���
	// - ������������ ������ ������
	// - ������������ ������ ������������
	// - ������ ��� �����
	{
		ASSERT_THROWS(
			FruitingHouseplant f1("", "lemon", 0, 0),
			Messages::EmptyHouseplantName
		);
		ASSERT_THROWS(
			FruitingHouseplant f2("lemon tree", "lemon", 0, 2),
			Messages::InvalidWateringNumber
		);
		ASSERT_THROWS(
			FruitingHouseplant f3("lemon tree", "lemon", 1, 0),
			Messages::InvalidFruitingPeriod
		);
		ASSERT_THROWS(
			FruitingHouseplant f4("lemon tree", "", 2, 2),
			Messages::EmptyFruitName
		);
	}

	//������� �����
	//���������� ��������, ����� ��� ���������� ������
	//������ ������� ���� ( ����� ) � ��������� ��������� �� ������
	{
		Room r;
		FruitingHouseplant fh("lemon tree", "lemon", 1, 5);
		r.addHouseplant(std::make_unique<FruitingHouseplant>(fh));
		for (int i = 0; i < 7; i++)
		{
			fh.daySkip();
			fh.water();
		}
	}
	
	//���������� ��������, ����� ����� ����� ������������
	//�������� : ���� �� ������ �������
	{
		Room r;
		FruitingHouseplant fh("lemon tree", "lemon", 1, 5);
		r.addHouseplant(std::make_unique<FruitingHouseplant>(fh));
		for (int i = 0; i < 7; i++)
		{
			fh.nDaysPassed(2);
			fh.water();
		}
	}
}

DECLARE_OOP_TEST(test_flowering_houseplant_functional)
{
	//��������� �������� ������ ������������ :
	// - ������ ���
	// - ������������ ������ ������
	// - ������������ ������ ��������
	// - ������������ ���-�� ���������� ������
	{
		ASSERT_THROWS(
			FloweringHouseplant fh("", 0, 0, 0),
			Messages::EmptyHouseplantName
		);
		ASSERT_THROWS(
			FloweringHouseplant fh("Flower", 0, 0, 0),
			Messages::InvalidWateringNumber
		);
		ASSERT_THROWS(
			FloweringHouseplant fh("Flower", 1, 0, 2),
			Messages::InvalidBloomingDuration
		);
		ASSERT_THROWS(
			FloweringHouseplant fh("Flower", 1, 1, 0),
			Messages::InvalidNeedWatering
		);
	}

	//���������� ��������, ����� ����� ������ ���������
	//� ������ �������� ����������
	{
		Room r;
		FloweringHouseplant fl("Flower", 1, 5, 5);
		r.addHouseplant(std::make_unique<FloweringHouseplant>(fl));
		for (int i = 0; i < 10; i++)
		{
			fl.daySkip();
			fl.water();
		}
		for (int i = 0; i < 10; i++)
		{
			fl.nDaysPassed(2);
			fl.water();
		}
	}

	//���������� �������� ����� ������
	//�������� �������� 9 ���� , ������ �������� �� 2 ��� � �������� �������
	//��������� ��������� : ������ �� ����� �������� �� �����
	{
		Room r;
		FloweringHouseplant fl("Flower", 1, 5, 5);

		r.addHouseplant(std::make_unique<FloweringHouseplant>(fl));

		for (int i = 0; i < 9; i++)
		{
			fl.daySkip();
			fl.water();
		}

		fl.nDaysPassed(2);
		fl.water();
	}
}