#include "deathParticle.h"

ParticleSystem::ParticleSystem()
{

}

void ParticleSystem::update(sf::Time elapsed)
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

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio = p.remainingTime.asSeconds() / p.lifetime.asSeconds();
            //p.m_circle.setFillColor.a = static_cast<sf::Uint8>(ratio * 255);
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

void ParticleSystem::AddParticle(sf::Vector2f monsterPos)
{
    Particle p;
    // give a random velocity and lifetime to the particle
    float angle = (std::rand() % 360) * 3.14f / 180.f;
    float speed = (std::rand() % 50) + 50.f;
    p.velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    p.lifetime = sf::milliseconds((std::rand() % 2000) + 1000);
    p.remainingTime = p.lifetime;
    p.m_circle.setPointCount(16);
    p.m_circle.setPosition(monsterPos);
    p.m_circle.setRadius(5.f);
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
        m_particles[i].m_circle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    }
}