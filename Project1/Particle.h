#pragma once
#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace cave
{

	struct Particle
	{
		double m_x;
		double m_y;

		//double x_speed;
		//double y_speed;

		double speed;  //speed
		double direction;  //angle


	public:

		Particle();
		virtual ~Particle();
		void update(int diff);

	};



}


#endif // !PARTICLE_H_



