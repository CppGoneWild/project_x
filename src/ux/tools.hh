#ifndef UX_TOOLS_HH
#define UX_TOOLS_HH




#include "imgui.h"




namespace ux
{


class ScopeID
{
public:
	ScopeID(char const * ID)                      { ImGui::PushID(ID); }
	ScopeID(char const * begin, char const * end) { ImGui::PushID(begin, end); }
	ScopeID(void const * ID)                      { ImGui::PushID(ID); }
	ScopeID(int ID)                               { ImGui::PushID(ID); }

	~ScopeID() { ImGui::PopID(); }

private:
	ScopeID() = delete;
	ScopeID(ScopeID const &) = delete;
	ScopeID(ScopeID &&) = delete;

	ScopeID & operator=(ScopeID const &) = delete;
	ScopeID & operator=(ScopeID &&) = delete;
};


class ScopeToolTips
{
public:
	ScopeToolTips()  { ImGui::BeginTooltip(); }
	~ScopeToolTips() { ImGui::EndTooltip(); }

private:
	ScopeToolTips(ScopeToolTips const &) = delete;
	ScopeToolTips(ScopeToolTips &&) = delete;

	ScopeToolTips & operator=(ScopeToolTips const &) = delete;
	ScopeToolTips & operator=(ScopeToolTips &&) = delete;
};


class PopupContextMenu
{
public:
	class Scope
	{
	public:
		Scope(PopupContextMenu & s) : _s(s) { assert(_s.ID); _s._state = ImGui::BeginPopupContextItem(_s.ID); }
		~Scope() {if (_s._state) ImGui::EndPopup(); }

	operator bool () const { return (_s._state); }
	
	private:
		Scope(Scope const &) = delete;
		Scope(Scope &&) = delete;
		Scope & operator=(Scope const &) = delete;
		Scope & operator=(Scope &&) = delete;

		PopupContextMenu & _s;		
	};

	PopupContextMenu() = default;
	PopupContextMenu(char const * ID) : ID(ID), _state(false) {}
	~PopupContextMenu() {}

private:
	PopupContextMenu(PopupContextMenu const &) = delete;
	PopupContextMenu(PopupContextMenu &&) = delete;

	PopupContextMenu & operator=(PopupContextMenu const &) = delete;
	PopupContextMenu & operator=(PopupContextMenu &&) = delete;

	const char * ID = nullptr;
	bool _state = false;

	friend class Scope;
};



}




#endif // UX_TOOLS_HH
