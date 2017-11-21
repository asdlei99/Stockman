#include <Misc/Card.h>

using namespace Logic;

Card::Card(std::string name, std::string texture, std::string description,
    std::vector<int> statusIds, DirectX::SimpleMath::Vector2 texStart,
    DirectX::SimpleMath::Vector2 texEnd, int statusType, int category)
    :   m_name(name), m_texture(texture), m_description(description),
        m_statusIds(statusIds), m_texStart(texStart), m_texEnd(texEnd),
        m_statusType(static_cast<StatusType> (statusType)), 
        m_category(static_cast<CardCategory>(category)),
        m_icon(0.0f, 0.0f, 100.0f, 150.0f, Resources::Textures::iconsheet, FloatRect(texStart, texEnd), 1.0f){

    switch (m_category)
    {
    case CardCategory::ATTACK:
        m_cardBackground = Sprite(0.0f, 0.0f, 200.0f, 250.0f, Resources::Textures::CardBackground, FloatRect({ 0.05288f, 0.0f }, { 0.34375f, 1.f }), 1.0f);
         break;
    
    case CardCategory::DEFENCE:
        m_cardBackground = Sprite(0.0f, 0.0f, 200.0f, 250.0f, Resources::Textures::CardBackground, FloatRect({ 0.345352f, 0.0f }, { 0.636217f, 1.f }), 1.0f);
        break;

    case CardCategory::UTILITY:
        m_cardBackground = Sprite(0.0f, 0.0f, 200.0f, 250.0f, Resources::Textures::CardBackground, FloatRect({ 0.637820f, 0.0f }, { 0.933493f, 1.f }), 1.0f);
        break;
    }
}

Card::~Card() { }

std::string Card::getName() const 
{ 
	return m_name; 
}
std::string Logic::Card::getTexture() const
{
	return m_texture;
}
std::string Card::getDescription() const 
{ 
	return m_description; 
}
const std::vector<int>& Card::getStatusIds() const
{ 
	return m_statusIds;
}

DirectX::SimpleMath::Vector2 Logic::Card::getTexStart() const
{
	return m_texStart;
}

DirectX::SimpleMath::Vector2 Logic::Card::getTexEnd() const
{
	return m_texEnd;
}



Card::StatusType Card::getStatusType() const
{
	return m_statusType;
}

Card::CardCategory Card::getCategory() const
{
    return m_category;
}

void Logic::Card::render() const
{
}
