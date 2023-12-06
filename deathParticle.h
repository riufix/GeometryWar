#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

class ParticleSystem : public sf::Drawable, public sf::Transformable {
public:	
	ParticleSystem();
	void update(sf::Time elapsed, bool scaleUp = false);
	void AddParticle(sf::Vector2f monsterPos, bool oppositeFromCenter = false, sf::Vector2f windowCenter = sf::Vector2f(0,0));
	void addParticles(int count, sf::Vector2f monsterPos);
	void ClearParticles();

private:
	void SetRandomColor();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

private:
	struct Particle {
		sf::Vector2f velocity;
		sf::Time lifetime;
		sf::Time remainingTime;
		sf::CircleShape m_circle;
	};
	std::vector<Particle> m_particles;
	sf::Vector2f m_emitter;
};