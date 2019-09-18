#pragma once
#include "wx\wx.h"
class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
public:
	int m_fieldWidth = 10;
	int m_fieldHeight = 10;
	wxButton** m_btn;
	int* m_field = nullptr;
	bool m_firstClick = true;

	void OnButtonClicked(wxCommandEvent &evt);
};

