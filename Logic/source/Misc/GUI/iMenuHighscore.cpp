#include <Misc\GUI\iMenuHighscore.h>
#include <comdef.h>

using namespace Logic;

#define ENTRY_POS_EDIT      false

#define ENTRY_POS_X         0.301f
#define ENTRY_POS_Y         0.167f
#define ENTRY_POS_Y_OFFSET  0.068f
#define COLUMN_2_OFFSET     0.074
#define COLUMN_3_OFFSET     0.299
#define COLUMN_4_OFFSET     0.466

#define FIRST_PLACE_COLOR   DirectX::SimpleMath::Color(1, 0.843137, 0, 1)
#define SECOND_PLACE_COLOR  DirectX::SimpleMath::Color(0.745098, 0.745098, 0.745098, 1)
#define THIRD_PLACE_COLOR   DirectX::SimpleMath::Color(0.545098, 0.270588, 0.0745098, 1)
#define OTHER_PLACE_COLOR   DirectX::SimpleMath::Color(1, 1, 1, 1)

iMenuHighscore::iMenuHighscore(iMenu::MenuGroup group)
    : iMenu(group) 
{
    buildHighscore();
}

iMenuHighscore::~iMenuHighscore() 
{
    clearEntries();
}

void iMenuHighscore::clearEntries()
{
    for (size_t i = 0; i < m_entry.size(); i++)
    {
        delete m_entry[i];
        m_entry[i] = nullptr;
    }
    m_entry.clear();
}

void iMenuHighscore::buildHighscore()
{
    clearEntries();
    std::vector<HighScoreManager::HighScore> entries = m_highscoreManager.getHighScores();
    for (size_t i = 0; i < entries.size(); i++)
        buildEntry(i, entries[i]);
}

void iMenuHighscore::buildEntry(int position, HighScoreManager::HighScore stat)
{
    // Setup of the entry
    Entry* entry    = newd Entry();
    entry->stats    = stat;
    entry->name = L"Stockman sucks";// _bstr_t(stat.name.c_str());
    entry->placing  = std::to_wstring(position + 1);
    entry->time     = std::to_wstring(9999) + L" Seconds";
    entry->score    = std::to_wstring(stat.score) + L" Points";

    // Entry Placing Render Texture
    if      (position == 0) entry->renderInfoPlacing.color  = FIRST_PLACE_COLOR;
    else if (position == 1) entry->renderInfoPlacing.color  = SECOND_PLACE_COLOR;
    else if (position == 2) entry->renderInfoPlacing.color  = THIRD_PLACE_COLOR;
    else                    entry->renderInfoName.color     = OTHER_PLACE_COLOR;
    entry->renderInfoPlacing.font       = Resources::Fonts::KG18;
    entry->renderInfoPlacing.position   = DirectX::SimpleMath::Vector2(ENTRY_POS_X * WIN_WIDTH, (ENTRY_POS_Y + (ENTRY_POS_Y_OFFSET * position)) * WIN_HEIGHT);
    entry->renderInfoPlacing.text       = entry->placing.c_str();
   
    // Entry Name Render Texture
    entry->renderInfoName.color         = OTHER_PLACE_COLOR;
    entry->renderInfoName.font          = Resources::Fonts::KG18;
    entry->renderInfoName.position      = DirectX::SimpleMath::Vector2((ENTRY_POS_X + COLUMN_2_OFFSET) * WIN_WIDTH, (ENTRY_POS_Y + (ENTRY_POS_Y_OFFSET * position)) * WIN_HEIGHT);
    entry->renderInfoName.text          = entry->name.c_str();

    // Entry Score Render Texture
    entry->renderInfoScore.color        = OTHER_PLACE_COLOR;
    entry->renderInfoScore.font         = Resources::Fonts::KG18;
    entry->renderInfoScore.position     = DirectX::SimpleMath::Vector2((ENTRY_POS_X + COLUMN_3_OFFSET)* WIN_WIDTH, (ENTRY_POS_Y + (ENTRY_POS_Y_OFFSET * position)) * WIN_HEIGHT);
    entry->renderInfoScore.text         = entry->score.c_str();

    // Entry Time Render Texture
    entry->renderInfoTime.color         = OTHER_PLACE_COLOR;
    entry->renderInfoTime.font          = Resources::Fonts::KG18;
    entry->renderInfoTime.position      = DirectX::SimpleMath::Vector2((ENTRY_POS_X + COLUMN_4_OFFSET) * WIN_WIDTH, (ENTRY_POS_Y + (ENTRY_POS_Y_OFFSET * position)) * WIN_HEIGHT);
    entry->renderInfoTime.text          = entry->time.c_str();

    m_entry.push_back(entry);
}

void iMenuHighscore::update(int x, int y, float deltaTime)
{
    iMenu::update(x, y, deltaTime);

// Debugging purposes
#if ENTRY_POS_EDIT
    static float posx, posy, posYoffset, col2, col3, col4;
    if (ImGui::Begin("Edit"))
    {
        ImGui::DragFloat("X", &posx, 0.0001f, 0, 1);
        ImGui::DragFloat("Y", &posy, 0.0001f, 0, 1);
        ImGui::DragFloat("Offset", &posYoffset, 0.0001f, 0, 1);
        ImGui::DragFloat("Col 2 Offset", &col2, 0.0001f, 0, 1);
        ImGui::DragFloat("Col 3 Offset", &col3, 0.0001f, 0, 1);
        ImGui::DragFloat("Col 4 Offset", &col4, 0.0001f, 0, 1);
        ImGui::End();
    }
    for (size_t i = 0; i < entries.size(); i++)
    {
        m_entry[i].renderInfoPlacing.position = DirectX::SimpleMath::Vector2(posx * WIN_WIDTH, (posy + (posYoffset * i)) * WIN_HEIGHT);
        m_entry[i].renderInfoName.position = DirectX::SimpleMath::Vector2((posx + col2) * WIN_WIDTH, (posy + (posYoffset * i)) * WIN_HEIGHT);
        m_entry[i].renderInfoScore.position = DirectX::SimpleMath::Vector2((posx + col3) * WIN_WIDTH, (posy + (posYoffset * i)) * WIN_HEIGHT);
        m_entry[i].renderInfoTime.position = DirectX::SimpleMath::Vector2((posx + col4) * WIN_WIDTH, (posy + (posYoffset * i)) * WIN_HEIGHT);
    }

#endif
}

void iMenuHighscore::render() const
{
    iMenu::render();

    for (size_t i = 0; i < m_entry.size(); i++)
    {
        QueueRender(m_entry[i]->renderInfoName);
        QueueRender(m_entry[i]->renderInfoScore);
        QueueRender(m_entry[i]->renderInfoPlacing);
        QueueRender(m_entry[i]->renderInfoTime);
    }
}