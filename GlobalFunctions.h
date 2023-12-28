#pragma once

#include "Includes.h"
#include "Classes.h"


int randomValue(int lower, int upper)
{
	return lower + rand() % (upper - lower + 1);
}


string getObjectStats(Object& object)
{
	return " size:\n"
		" x: " + to_string(object.getSizeX()) + "\n" +
		" y: " + to_string(object.getSizeY()) + "\n" +

		" \n" +

		" position:\n" +
		" x: " + to_string(object.getPositionX()) + "\n" +
		" y: " + to_string(object.getPositionY()) + "\n" +

		" \n" +

		" speed:\n" +
		" x: " + to_string(object.getSpeedX()) + "\n" +
		" y: " + to_string(object.getSpeedY()) + "\n" +

		" \n" +

		" acceleration:\n" +
		" x: " + to_string(object.getAccelerationX()) + "\n" +
		" y: " + to_string(object.getAccelerationY()) + "\n";
}


bool checkForCollision(Object& player, Object& object)
{
	double minX = min(player.getPositionX(), object.getPositionX());
	double minY = min(player.getPositionY(), object.getPositionY());
	double maxX = max(player.getMaxPositionX(), object.getMaxPositionX());
	double maxY = max(player.getMaxPositionY(), object.getMaxPositionY());

	double sizeX = maxX - minX;
	double sizeY = maxY - minY;

	return player.getSizeX() + object.getSizeX() > sizeX && player.getSizeY() + object.getSizeY() > sizeY;
}


bool checkForCollision(Object& player, vector<Object>& objects)
{
	for (Object object : objects)
	{
		if (checkForCollision(player, object))
		{
			return true;
		}
	}

	return false;
}