#include "..\include\cMain.h"

cMain::cMain() : wxFrame(nullptr,wxID_ANY,"Minesweeper - AEK")
{
	m_btn = new wxButton * [m_fieldWidth * m_fieldHeight];
	wxGridSizer* grid = new wxGridSizer(m_fieldHeight, m_fieldWidth, 0, 0);
	m_field = new int[m_fieldWidth * m_fieldHeight];
	wxFont font1(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	for (int y = 0; y < m_fieldHeight; y++) {
		for (int x = 0; x < m_fieldWidth; x++) {
			m_btn[y * m_fieldWidth + x] = new wxButton(this, 10000 + y * m_fieldWidth + x);
			m_btn[y * m_fieldWidth + x]->SetFont(font1);
			grid->Add(m_btn[y * m_fieldWidth + x], 1, wxEXPAND | wxALL);

			m_btn[y * m_fieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			
			m_field[y * m_fieldWidth + x] = 0;
		}
	}
	this->SetSizer(grid);
	grid->Layout();
}

cMain::~cMain()
{
	delete[]m_btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	// Get coordinate of button in field array
	int x = (evt.GetId() - 10000) % m_fieldWidth;
	int y = (evt.GetId() - 10000) / m_fieldWidth;

	// Generate mines in first click
	if (m_firstClick) {
		int mines = 30;
		while (mines) {
			int rx = rand() % m_fieldWidth;
			int ry = rand() % m_fieldHeight;
			if (m_field[ry * m_fieldWidth + rx] == 0 && rx != x && ry != y) {
				m_field[ry * m_fieldWidth + rx] = -1;
				mines--;
			}
		}
		m_firstClick = false;
	}

	// Disable last button, preventing it being pressed again
	m_btn[y * m_fieldWidth + x]->Enable(false);

	// Check if player hit mine
	if (m_field[y * m_fieldWidth + x] == -1) {
		wxMessageBox("Booom! Game Over :(");

		// Reset game
		m_firstClick = true;
		for (int y = 0; y < m_fieldHeight; y++) {
			for (int x = 0; x < m_fieldWidth; x++) {
				m_field[y * m_fieldWidth + x] = 0;
				m_btn[y * m_fieldWidth + x]->SetLabel("");
				m_btn[y * m_fieldWidth + x]->Enable(true);
			}
		}
	}
	else {
		// Count neighbouring mines
		int mine_count = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				// Chechk boundaries
				if (x + i >= 0 && x + i < m_fieldWidth && y + j >= 0 && y + j < m_fieldHeight) {
					// Check mine
					if (m_field[(y + j) * m_fieldWidth + (x + i)] == -1) {
						mine_count++;
					}
				}
			}
		}
		// Update button label to show mine count
		if (mine_count > 0) {
			m_btn[y * m_fieldWidth + x]->SetLabel(std::to_string(mine_count));
		}

	}

	evt.Skip();
}
