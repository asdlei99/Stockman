#include "Misc\MenuMachine.h"

using namespace Logic;

MenuMachine::MenuMachine()
{
}


MenuMachine::~MenuMachine()
{
}

void Logic::MenuMachine::showMenu(GameState state)
{
	if(m_menuStates.find(state) != m_menuStates.end())
	{
		currentActive = m_menuStates.at(state);
	}
	else
	{
		currentActive = nullptr;
	}
}

void Logic::MenuMachine::removeMenu()
{
	currentActive = nullptr;
}

void Logic::MenuMachine::readMenuLayoutFromFile()
{
	//accquire menue state
	//accquires position
	//accquires its width and height
	//accquires texture
}

