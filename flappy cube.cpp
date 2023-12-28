#include "Includes.h"
#include "GlobalFunctions.h"
#include "FlappyCubeFunctions.h"
#include "Classes.h"


int main()
{
	srand(time(NULL));

	long long score = 0;
	long long jump_count = 0;

	bool ability_to_increase_score = true;
	bool ability_to_control = true;
	bool noclip = false;
	bool collision = false;
	bool stats_output = true;
	bool detailed_stats_output = false;

	high_resolution_clock::time_point start;
	high_resolution_clock::time_point end;

	Font font;
	Text text;

	if (!font.loadFromFile("Fonts/arial.ttf"))
	{
		return 0;
	}

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(Color(0, 0, 0));

	double winX = 1000, winY = 750;

	double space_size = 0.5 * winY;
	double tube_speed = 2 * (randomValue(0, 1) ? 1 : -1);


	Vector2f player_size = Vector2f(100, 100);
	Texture player_texture; player_texture.loadFromFile("Textures/cube.png");
	Vector2f player_position = Vector2f(0.2 * winX, 0.5 * winY - player_size.y / 2);
	Vector2f player_speed = Vector2f(0, 0);
	Vector2f player_acceleration = Vector2f(0, 0);

	Vector2f upper_tube_size = Vector2f(100, winY - space_size);
	Texture upper_tube_texture; upper_tube_texture.loadFromFile("Textures/tube.png");
	Vector2f upper_tube_position = Vector2f(winX, randomValue(-upper_tube_size.y, 0));
	Vector2f upper_tube_speed = Vector2f(0, tube_speed);
	Vector2f upper_tube_acceleration = Vector2f(0, 0);

	Vector2f lower_tube_size = Vector2f(100, winY - space_size);
	Texture lower_tube_texture; lower_tube_texture.loadFromFile("Textures/tube.png");
	Vector2f lower_tube_position = Vector2f(winX, upper_tube_position.y + upper_tube_size.y + space_size);
	Vector2f lower_tube_speed = Vector2f(0, tube_speed);
	Vector2f lower_tube_acceleration = Vector2f(0, 0);


	RectangleShape background;
	Texture background_texture; background_texture.loadFromFile("Textures/background.png");

	background.setSize(Vector2f(winX, winY));
	background.setTexture(&background_texture);
	background.setPosition(Vector2f(0, 0));


	RenderWindow window(VideoMode(winX, winY), "flappy cube");
	View view(Vector2f(winX / 2, winY / 2), Vector2f(winX, winY));


	Object player(player_size, player_texture, player_position, player_speed, player_acceleration);
	Object upper_tube(upper_tube_size, upper_tube_texture, upper_tube_position, upper_tube_speed, upper_tube_acceleration);
	Object lower_tube(lower_tube_size, lower_tube_texture, lower_tube_position, lower_tube_speed, lower_tube_acceleration);


	while (window.isOpen())
	{
		start = high_resolution_clock::now();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::KeyPressed && ability_to_control)
			{
				switch (event.key.scancode)
				{
				case Keyboard::Scan::Space:

					if (jump_count == 0)
					{
						player.setSpeedX(10);

						player.setAcceleration(0.001, 1);
					}

					player.setSpeedY(-20);

					jump_count++;

					break;


				case Keyboard::Scan::D:
					
					detailed_stats_output = (detailed_stats_output ? false : true);

					stats_output = (stats_output ? false : true);
					
					break;


				case Keyboard::Scan::LShift:

					player.getSpeedX() < 10 ? player.setSpeedX(10) : player.setSpeedX(0);

					break;


				case Keyboard::Scan::N:

					noclip = (noclip ? false : true);

					break;


				default:
					
					break;
				}
			}
		}

		window.setView(view);


		window.clear();


		window.draw(background);

		window.draw(upper_tube.getShape());

		window.draw(lower_tube.getShape());

		window.draw(player.getShape());


		string stats_text;

		if (detailed_stats_output)
		{
			stats_text = getObjectStats(player);
		}
		else if (stats_output)
		{
			stats_text = " score: " + to_string(score) + "\n jump count: " + to_string(jump_count) + (noclip ? "\n noclip: true" : "");
		}

		text.setString(stats_text);

		text.setPosition(player.getPositionX() - player_position.x, 0);

		window.draw(text);

		
		window.display();


		vector<Object> objects{ upper_tube, lower_tube };
		if ((checkForCollision(player, objects) || player.getPositionY() < 0 || player.getMaxPositionY() > winY) && collision == false && noclip == false)
		{
			player.setSpeed(Vector2f(0, 0));
			player.setAccelerationX(0);

			stats_output = false;
			detailed_stats_output = false;
			ability_to_control = false;
			collision = true;
			noclip = false;
		}


		view.move(player.getSpeedX(), 0);

		background.move(player.getSpeedX(), 0);

		player.move();

		if (upper_tube.getMaxPositionY() + upper_tube.getSpeedY() < 0 || lower_tube.getPositionY() + lower_tube.getSpeedY() > winY)
		{
			upper_tube.setSpeedY(-upper_tube.getSpeedY());
			lower_tube.setSpeedY(-lower_tube.getSpeedY());
		}

		upper_tube.move();
		lower_tube.move();


		// increase score
		if ((player.getPositionX() > upper_tube.getMaxPositionX()) && ability_to_increase_score)
		{
			score++;

			ability_to_increase_score = false;
		}

		// "new" tubes
		if (player.getPositionX() - player_position.x >= upper_tube.getMaxPositionX())
		{
			upper_tube.setPosition(player.getPositionX() + winX - player_position.x, randomValue(-upper_tube.getSizeY(), 0));
			lower_tube.setPosition(player.getPositionX() + winX - player_position.x, upper_tube.getMaxPositionY() + space_size);

			if (randomValue(0, 1))
			{
				upper_tube.setSpeedY(-upper_tube.getSpeedY());
				lower_tube.setSpeedY(-lower_tube.getSpeedY());
			}

			ability_to_increase_score = true;
		}


		this_thread::sleep_for(chrono::milliseconds(1));


		end = high_resolution_clock::now();


		double fps = 1e9f / duration_cast<chrono::nanoseconds>(end - start).count();

		string title = "flappy cube FPS[" + to_string(fps) + "]";
		window.setTitle(title.c_str());

		// after collision
		if (player.getPositionY() > winY + player.getSizeY() && collision == true)
		{
			this_thread::sleep_for(chrono::milliseconds(500));

			window.close();

			//ifstream ifile;
			//
			//ifile.open("best score.txt");
			//
			//if (ifile.is_open())
			//{
			//	string line;
			//	getline(ifile, line);
			//	ifile.close();
			//
			//	if (score > stoll(line))
			//	{
			//		text.setString(" score: " + to_string(score) + "\n best score: " + to_string(score) + "\n Esc to exit" + "\n R to restart");
			//
			//		changeBestScore(score);
			//	}
			//	else
			//	{
			//		text.setString(" score: " + to_string(score) + "\n best score: " + line + "\n Esc to exit" + "\n R to restart");
			//	}
			//}
			//else
			//{
			//	ifile.close();
			//
			//	text.setString(" score: " + to_string(score) + "\n best score: " + to_string(score) + "\n Esc to exit" + "\n R to restart");
			//
			//	changeBestScore(score);
			//}
			//
			//text.setCharacterSize(50);
			//text.setPosition(Vector2f(view.getCenter().x - view.getSize().x * 0.2, view.getCenter().y - view.getSize().y * 0.2));
			//
			//window.clear(background_color);
			//window.draw(text);
			//
			//
			//
			//window.display();
			//
			//
			//while (true)
			//{
			//	if (window.pollEvent(event))
			//	{
			//		if (event.type == Event::Closed)
			//		{
			//			window.close();
			//
			//			break;
			//		}
			//
			//		// exit
			//		if (event.type == Event::KeyPressed && event.key.scancode == Keyboard::Scan::Escape)
			//		{
			//			window.close();
			//
			//			break;
			//		}
			//
			//		// restart
			//		if (event.type == Event::KeyPressed && event.key.scancode == Keyboard::Scan::R)
			//		{
			//			trail.clear();
			//			trail_length = 0;
			//
			//			score = 0;
			//			jump_count = 0;
			//
			//			ability_to_increase_score = true;
			//			ability_to_control = true;
			//			noclip = false;
			//			collision = false;
			//			stats_output = true;
			//			detailed_stats_output = false;
			//
			//			text.setCharacterSize(20);
			//
			//			trail_element.setPosition(player_position);
			//
			//
			//			view.setCenter(Vector2f(winX / 2, winY / 2));
			//
			//
			//			setObjectStats(player, player_size, player_color, player_position, player_speed, player_acceleration);
			//
			//			setObjectStats(upper_tube, upper_tube_size, upper_tube_color, upper_tube_position, upper_tube_speed, upper_tube_acceleration);
			//
			//			setObjectStats(lower_tube, lower_tube_size, lower_tube_color, lower_tube_position, lower_tube_speed, lower_tube_acceleration);
			//
			//			break;
			//		}
			//	}
			//}
		}
	}
}