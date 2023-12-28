#pragma once

#include "Includes.h"

class Object
{
	RectangleShape object;
	Vector2f size = Vector2f(0, 0);
	Texture texture;

	Vector2f position = Vector2f(0, 0);
	Vector2f speed = Vector2f(0, 0);
	Vector2f acceleration = Vector2f(0, 0);

public:

	Object(Vector2f size, Texture& texture, Vector2f position, Vector2f speed, Vector2f acceleration):
	size(size), texture(texture), position(position), speed(speed), acceleration(acceleration)
	{
		object.setSize(size);

		object.setTexture(&texture);

		object.setPosition(position);
	}

	Object() = default;

	void setSize(double sizeX, double sizeY)
	{
		size = Vector2f(sizeX, sizeY);

		object.setSize(size);
	}

	void setSize(Vector2f s)
	{
		size = s;

		object.setSize(size);
	}

	void setSizeX(double sizeX)
	{
		size.x = sizeX;

		object.setSize(size);
	}

	void setSizeY(double sizeY)
	{
		size.y = sizeY;

		object.setSize(size);
	}

	void setTexture(Texture& t)
	{
		texture = t;

		object.setTexture(&texture);
	}

	void setPosition(double positionX, double positionY)
	{
		position = Vector2f(positionX, positionY);

		object.setPosition(position);
	}

	void setPosition(Vector2f p)
	{
		position = p;

		object.setPosition(position);
	}

	void setPositionX(double positionX)
	{
		position.x = positionX;

		object.setPosition(position);
	}

	void setPositionY(double positionY)
	{
		position.y = positionY;

		object.setPosition(position);
	}

	void setSpeed(double speedX, double speedY)
	{
		speed = Vector2f(speedX, speedY);
	}

	void setSpeed(Vector2f s)
	{
		speed = s;
	}

	void setAcceleration(double accelerationX, double accelerationY)
	{
		acceleration = Vector2f(accelerationX, accelerationY);
	}

	void setAcceleration(Vector2f a)
	{
		acceleration = a;
	}

	void setSpeedX(double speedX)
	{
		speed.x = speedX;
	}

	void setSpeedY(double speedY)
	{
		speed.y = speedY;
	}

	void setAccelerationX(double accelerationX)
	{
		acceleration.x = accelerationX;
	}

	void setAccelerationY(double accelerationY)
	{
		acceleration.y = accelerationY;
	}


	RectangleShape getShape()
	{
		return object;
	}

	Vector2f getSize()
	{
		return size;
	}

	double getSizeX()
	{
		return size.x;
	}

	double getSizeY()
	{
		return size.y;
	}

	Vector2f getPosition()
	{
		return position;
	}

	Vector2f getMaxPosition()
	{
		return Vector2f(position.x + size.x, position.y + size.y);
	}

	double getPositionX()
	{
		return position.x;
	}

	double getMaxPositionX()
	{
		return position.x + size.x;
	}

	double getPositionY()
	{
		return position.y;
	}

	double getMaxPositionY()
	{
		return position.y + size.y;
	}

	Vector2f getSpeed()
	{
		return speed;
	}

	double getSpeedX()
	{
		return speed.x;
	}

	double getSpeedY()
	{
		return speed.y;
	}

	Vector2f getAcceleration()
	{
		return acceleration;
	}

	double getAccelerationX()
	{
		return acceleration.x;
	}

	double getAccelerationY()
	{
		return acceleration.y;
	}


	void move()
	{
		position += speed;

		speed += acceleration;

		object.setPosition(position);
	}
};