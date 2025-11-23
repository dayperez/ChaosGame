// Include important C++ libraries here
//Name: Dayanna Perez

#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{

	srand(static_cast<unsigned>(time(nullptr)));

	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	
	Font font;
		if (!font.loadFromFile("Marxiana.ttf")) {
			cout << "Error loading font.." << endl;
		}
	
	Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(Color::Magenta);
	text.setPosition(20.f, 20.f);
	text.setString(" Welcome . . . click   3   vertices,   then   a   starting   point!");
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;


	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
				
				Vector2f clickPos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
				
			    if(vertices.size() < 3)
			    {
				vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
				points.push_back(clickPos);
				cout << "Starting point: (" << clickPos.x << ", " << clickPos.y << ")" << endl;
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(points.size() > 0)
		{
		    ///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
			int framePoints = 100;

			for (int i = 0; i < framePoints; i++){
				int index = rand() % 3;
				Vector2f vertex = vertices[index];
				Vector2f lastPoint = points.back();

				Vector2f newPoint;
				newPoint.x = (lastPoint.x + vertex.x) / 2.0;
				newPoint.y = (lastPoint.y + vertex.y) / 2.0;

				points.push_back(newPoint);
			}
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Green);
			rect.setOrigin(5,5);
		    window.draw(rect);
		}
		for (int i = 0; i < points.size(); i++){
			CircleShape circ;
			circ.setRadius(1);
			circ.setPosition(Vector2f(points[i].x, points[i].y));
		    circ.setFillColor(Color::Magenta);
			circ.setOrigin(1,1);
		    window.draw(circ);
		}
		///TODO:  Draw points
		window.draw(text);
		window.display();
	}
}
