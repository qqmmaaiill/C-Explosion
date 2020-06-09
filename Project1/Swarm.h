#pragma once
#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

namespace cave
{
	class Swarm
	{


	private:
		Particle *m_pParticles;

		int lasttime;

	public:

		const static int NPARTICLES = 5000;
		Swarm();
		virtual ~Swarm();

		const Particle * const getParticles()
		{
			return m_pParticles;
		}

		void update(int elapsed);

	};



}

#endif // !SWARM_H_



