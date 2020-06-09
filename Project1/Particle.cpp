#include "Particle.h"
#include<stdlib.h>
#include<cmath>


const double M_PI = 3.1415;

namespace cave
{

	Particle::Particle(): m_x(0),m_y(0)
	{

		//m_x = ((2.0 * rand()) / RAND_MAX) - 1;
		//m_y = ((2.0 * rand()) / RAND_MAX) - 1;

		//x_speed = 0.001 * ((2.0 * rand()) / RAND_MAX - 1);
		//y_speed = 0.001 * ((2.0 * rand()) / RAND_MAX - 1);

		direction = (2 * M_PI *  rand()) / RAND_MAX;  //for radiants
		speed = (0.0001* rand()) / RAND_MAX;


	}


	Particle::~Particle()
	{
	}

	void Particle::update(int diff) //to move the particles in some way;
	{

		double x_speed = speed * cos(direction);
		double y_speed = speed * sin(direction);

		m_x += x_speed * diff;
		m_y += y_speed * diff;

		//const double speed = 0.01;
		/*m_x += x_speed;
		m_y += y_speed; 

		if (m_x <= -1.0 || m_x >= 1.0)
		{
			x_speed = -x_speed;
		}
		if (m_y <= -1.0 || m_y >= 1.0)
		{
			y_speed = -y_speed;
		}*/
	
	}

}
