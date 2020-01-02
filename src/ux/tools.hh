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
	ScopeID(ScopeID const &) = delete;
	ScopeID(ScopeID &&) = delete;

	ScopeID & operator=(ScopeID const &) = delete;
	ScopeID & operator=(ScopeID &&) = delete;
};




}




#endif // UX_TOOLS_HH
