#ifndef UX_TOOLS_HH
#define UX_TOOLS_HH




namespace ux
{




class ScopeID
{
public:
	ScopeID(char const * ID);
	ScopeID(char const * begin, char const * end);
	ScopeID(void const * ID);
	ScopeID(int ID);

	~ScopeID();

private:
	ScopeID()                = delete;
	ScopeID(ScopeID const &) = delete;
	ScopeID(ScopeID &&)      = delete;

	ScopeID & operator=(ScopeID const &) = delete;
	ScopeID & operator=(ScopeID &&)      = delete;
};


class ScopeToolTips
{
public:
	ScopeToolTips();
	~ScopeToolTips();

private:
	ScopeToolTips(ScopeToolTips const &) = delete;
	ScopeToolTips(ScopeToolTips &&)      = delete;

	ScopeToolTips & operator=(ScopeToolTips const &) = delete;
	ScopeToolTips & operator=(ScopeToolTips &&)      = delete;
};


class PopupContextMenu
{
public:
	class Scope
	{
	public:
		Scope(PopupContextMenu & s);
		~Scope();

		operator bool () const;

	private:
		Scope(Scope const &)             = delete;
		Scope(Scope &&)                  = delete;
		Scope & operator=(Scope const &) = delete;
		Scope & operator=(Scope &&)      = delete;

		PopupContextMenu & _s;		
	};

	PopupContextMenu()  = default;
	~PopupContextMenu() = default;

	PopupContextMenu(char const * ID);

private:
	PopupContextMenu(PopupContextMenu const &) = delete;
	PopupContextMenu(PopupContextMenu &&)      = delete;

	PopupContextMenu & operator=(PopupContextMenu const &) = delete;
	PopupContextMenu & operator=(PopupContextMenu &&)      = delete;

	const char * ID = nullptr;
	bool _state = false;

	friend class Scope;
};




}




#endif // UX_TOOLS_HH
