#include "tools.hh"

#include "imgui.h"




/*
                      _____                       ________
                     / ___/_________  ____  ___  /  _/ __ \
                     \__ \/ ___/ __ \/ __ \/ _ \ / // / / /
                    ___/ / /__/ /_/ / /_/ /  __// // /_/ /
                   /____/\___/\____/ .___/\___/___/_____/
                                  /_/
*/




ux::ScopeID::ScopeID(char const * ID)
{
	ImGui::PushID(ID);
}

ux::ScopeID::ScopeID(char const * begin, char const * end)
{
	ImGui::PushID(begin, end);
}

ux::ScopeID::ScopeID(void const * ID)
{
	ImGui::PushID(ID);
}

ux::ScopeID::ScopeID(int ID)
{
	ImGui::PushID(ID);
}

ux::ScopeID::~ScopeID()
{
	ImGui::PopID();
}




/*
         _____                     ______            _________
        / ___/_________  ____  ___/_  __/___  ____  / /_  __(_)___  _____
        \__ \/ ___/ __ \/ __ \/ _ \/ / / __ \/ __ \/ / / / / / __ \/ ___/
       ___/ / /__/ /_/ / /_/ /  __/ / / /_/ / /_/ / / / / / / /_/ (__  )
      /____/\___/\____/ .___/\___/_/  \____/\____/_/ /_/ /_/ .___/____/
                     /_/                                  /_/
*/




ux::ScopeToolTips::ScopeToolTips()
{
	ImGui::BeginTooltip();
}

ux::ScopeToolTips::~ScopeToolTips()
{
	ImGui::EndTooltip();
}




/*
    ____                          ______            __            __  __  ___
   / __ \____  ____  __  ______  / ____/___  ____  / /____  _  __/ /_/  |/  /__  ____  __  __
  / /_/ / __ \/ __ \/ / / / __ \/ /   / __ \/ __ \/ __/ _ \| |/_/ __/ /|_/ / _ \/ __ \/ / / /
 / ____/ /_/ / /_/ / /_/ / /_/ / /___/ /_/ / / / / /_/  __/>  </ /_/ /  / /  __/ / / / /_/ /
/_/    \____/ .___/\__,_/ .___/\____/\____/_/ /_/\__/\___/_/|_|\__/_/  /_/\___/_/ /_/\__,_/
           /_/         /_/
*/




////////////////////////////////////////////////////////////////////////////////
//                                   Scope                                    //
////////////////////////////////////////////////////////////////////////////////




ux::PopupContextMenu::Scope::Scope(PopupContextMenu & s)
: _s(s)
{
	assert(_s.ID);

	_s._state = ImGui::BeginPopupContextItem(_s.ID);
}

ux::PopupContextMenu::Scope::~Scope()
{
	if (_s._state) ImGui::EndPopup();
}

ux::PopupContextMenu::Scope::operator bool () const
{
	return (_s._state);
}




////////////////////////////////////////////////////////////////////////////////
//                              PopupContextMenu                              //
////////////////////////////////////////////////////////////////////////////////




ux::PopupContextMenu::PopupContextMenu(char const * ID)
: ID(ID), _state(false)
{}
