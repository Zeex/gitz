#include "GitzFrame.h"

enum
{
    ID_Hello = 1
};

GitzFrame::GitzFrame()
    : wxFrame(NULL, wxID_ANY, wxApp::GetInstance()->GetAppDisplayName())
{
    SetIcon(wxICON(AppIcon));

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    Bind(wxEVT_MENU, &GitzFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &GitzFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &GitzFrame::OnExit, this, wxID_EXIT);

    grid = new wxGrid(this, -1);
    grid->CreateGrid(0, 4);
    grid->HideRowLabels();
    grid->SetColLabelValue(0, "Message");
    grid->SetColLabelValue(1, "Author");
    grid->SetColLabelValue(2, "Email");
    grid->SetColLabelValue(3, "Time");
    grid->SetMargins(0, 0);

    auto sizer = new wxBoxSizer(wxVERTICAL);
    SetSizerAndFit(sizer);
    sizer->Add(grid, 0, wxEXPAND);
}

void GitzFrame::AppendCommit(git_commit *commit)
{
    const auto author = git_commit_author(commit);
    auto currentRow = grid->GetNumberRows();
    grid->AppendRows(1);

    auto message = git_commit_message(commit);
    grid->SetCellValue(currentRow, 0, message);

    grid->SetCellValue(currentRow, 1, author->name);
    grid->SetCellValue(currentRow, 2, author->email);

    auto time = wxDateTime(git_commit_time(commit));
    grid->SetCellValue(currentRow, 3, time.Format());

    grid->AutoSizeRow(currentRow);
    grid->AutoSizeColumns();

    for (int i = 0; i < grid->GetNumberCols(); i++) {
        grid->SetReadOnly(currentRow, i, true);
    }
}

void GitzFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void GitzFrame::OnAbout(wxCommandEvent &event)
{
    auto appName = wxApp::GetInstance()->GetAppDisplayName();
    wxMessageBox(
        appName + " is a cross-platform Git repository explorer.",
        "About " + appName,
        wxOK | wxICON_INFORMATION);
}

void GitzFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Hello world from wxWidgets!");
};
