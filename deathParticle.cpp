#include "deathParticle.h"

ParticleSystem::ParticleSystem()
{

}

void ParticleSystem::update(sf::Time elapsed, bool scaleUp)
{
    std::vector<Particle>::iterator it = m_particles.begin();
    
    while(it != m_particles.end())
    {
        // update the particle lifetime
        Particle& p = *it;
        p.remainingTime -= elapsed;

        if (p.remainingTime.asSeconds() <= 0) {
            it = m_particles.erase(it);
        }
        else {
            // update the position of the corresponding vertex
            p.m_circle.move(p.velocity * elapsed.asSeconds());

            // update the size and transparency of the particle according to its lifetime
            if (scaleUp)
            {
                float ratio = (p.remainingTime.asSeconds() / p.lifetime.asSeconds());
                p.m_circle.setScale(100 * (1 - ratio), 100 * (1 -ratio));
                p.m_circle.setFillColor(sf::Color(p.m_circle.getFillColor().r,
                                                  p.m_circle.getFillColor().g,
                                                  p.m_circle.getFillColor().b,
                                                  static_cast<sf::Uint8>(ratio * 255)));
            }
            it++;
        }
              
    }

    SetRandomColor();
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // our particles don't use a texture
    states.texture = NULL;

    // draw the vertex array
    for (int i = 0; i < m_particles.size(); i++) {
        target.draw(m_particles[i].m_circle);
    }
}

void ParticleSystem::AddParticle(sf::Vector2f monsterPos, bool oppositeFromCenter, sf::Vector2f windowCenter)
{
    Particle p;
    // give a random velocity (or give a velocity away from center) to the particle

    float speed = (std::rand() % 50) + 50.f;
    if (oppositeFromCenter) {

        //Calculate Direction from Center of Window to Particle and assign it as velocity
        sf::Vector2f vectorParticleCenter = sf::Vector2f(
            monsterPos.x - windowCenter.x,
            monsterPos.y - windowCenter.y
        );
        float vectorParticleCenterMagnitude = sqrt((vectorParticleCenter.x * vectorParticleCenter.x) + (vectorParticleCenter.y * vectorParticleCenter.y));
        vectorParticleCenter = sf::Vector2f(
            (vectorParticleCenter.x / vectorParticleCenterMagnitude),
            (vectorParticleCenter.y / vectorParticleCenterMagnitude)
        );
        p.velocity = sf::Vector2f(vectorParticleCenter.x * speed * 50, vectorParticleCenter.y * speed * 50);

    }
    else {
        float angle = (std::rand() % 360) * 3.14f / 180.f;
        p.velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    }
    // give a random lifetime to the particle
    p.lifetime = sf::milliseconds((std::rand() % 2000) + 1000);
    p.remainingTime = p.lifetime;

    p.m_circle.setPointCount(16);
    p.m_circle.setPosition(monsterPos);
    p.m_circle.setRadius(5.f);
    p.m_circle.setOrigin(p.m_circle.getRadius(), p.m_circle.getRadius());
    m_particles.push_back(p);

}

void ParticleSystem::addParticles(int count, sf::Vector2f monsterPos) {
    for (int i = 0; i < count; i++) {
        AddParticle(monsterPos);
    }
}

void ParticleSystem::SetRandomColor()
{
    for (int i = 0; i < m_particles.size(); i++) {
        m_particles[i].m_circle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, m_particles[i].m_circle.getFillColor().a));
    }
}

void ParticleSystem::ClearParticles()
{
    m_particles.clear();
}