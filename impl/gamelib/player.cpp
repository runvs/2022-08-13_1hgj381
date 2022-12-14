
#include "player.hpp"
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <math_helper.hpp>

void Player::doCreate()
{
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeCircle(16, textureManager());
    m_shape->setOffset(jt::OffsetMode::CENTER);
    m_position = jt::Vector2f { 300, 200 };
}

void Player::doUpdate(float const elapsed)
{
    m_shape->update(elapsed);

    float const moveSpeed = 12.0f;

    m_playerIdleTime += elapsed;
    if (getGame()->input().keyboard()->pressed(jt::KeyCode::A)
        || getGame()->input().keyboard()->pressed(jt::KeyCode::Left)) {
        m_velocity.x -= elapsed * moveSpeed;
        m_playerIdleTime = 0.0f;
    } else if (getGame()->input().keyboard()->pressed(jt::KeyCode::D)
        || getGame()->input().keyboard()->pressed(jt::KeyCode::Right)) {
        m_velocity.x += elapsed * moveSpeed;
        m_playerIdleTime = 0.0f;
    }

    if (getGame()->input().keyboard()->pressed(jt::KeyCode::W)
        || getGame()->input().keyboard()->pressed(jt::KeyCode::Up)) {
        m_velocity.y -= elapsed * moveSpeed;
        m_playerIdleTime = 0.0f;
    } else if (getGame()->input().keyboard()->pressed(jt::KeyCode::S)
        || getGame()->input().keyboard()->pressed(jt::KeyCode::Down)) {
        m_velocity.y += elapsed * moveSpeed;
        m_playerIdleTime = 0.0f;
    }

    m_velocity = 0.975f * m_velocity;

    m_position = m_position + m_velocity;

    float marginFactor = (getAge() / 10.0f) * 4.0f;
    float maxValue = 125.0f;

    if (marginFactor >= maxValue) {
        marginFactor = maxValue;
    }
    float const margin = 48.0f + marginFactor;
    if (m_position.x < margin) {
        m_position.x = margin;
    }
    if (m_position.x > GP::GetScreenSize().x - margin) {
        m_position.x = GP::GetScreenSize().x - margin;
    }

    if (m_position.y < margin) {
        m_position.y = margin;
    }
    if (m_position.y > GP::GetScreenSize().y - margin) {
        m_position.y = GP::GetScreenSize().y - margin;
    }

    m_shape->setPosition(m_position);

    m_hurtTimer -= elapsed;

    if (m_hurtTimer >= 0) {
        m_flashTimer -= elapsed;
        if (m_flashTimer <= 0) {
            m_flashTimer = 0.05f;
            if (m_shape->getColor().a == 0) {
                m_shape->setColor(GP::getPalette().getColor(0));
            } else {
                m_shape->setColor(jt::colors::Transparent);
            }
        }
    } else {
        m_shape->setColor(GP::getPalette().getColor(0));
    }
}
void Player::doDraw() const { m_shape->draw(renderTarget()); }
void Player::hurt() { m_hurtTimer = 0.6f; }
bool Player::canBeHurt() const { return m_hurtTimer <= 0.0f; }

float Player::playerIdleTime() const { return m_playerIdleTime; }
