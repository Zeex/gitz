#define WXUSINGDLL

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <git2.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum
{
    ID_Hello = 1
};

wxIMPLEMENT_APP(MyApp);

bool CheckGitResult(int result, const wxString &message) {
    if (result != 0) {
        wxMessageBox((message + ": ") + git_error_last()->message, "Error", wxOK | wxICON_ERROR);
        return false;
    }
    return true;
}

bool MyApp::OnInit()
{
    git_libgit2_init();

    auto repo_path = wxGetCwd();
    git_repository *repo;
    git_revwalk *walker;
    git_oid commit_id;
    git_commit *commit = nullptr;

    if (!CheckGitResult(
            git_repository_open(&repo, repo_path.c_str()), 
            "Could not open repository")) {
        return false;
    }
    if (!CheckGitResult(
            git_revwalk_new(&walker, repo), 
            "Could not read repository history")) {
        return false;
    }

    while (git_revwalk_next(&commit_id, walker) == 0) {
        if (!CheckGitResult(
                git_commit_lookup(&commit, repo, &commit_id), 
                "Failed to look up commit")) {
            break;
        }
        git_commit_free(commit);
    }

    git_revwalk_free(walker);
    git_repository_free(repo);

    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Hello World")
{
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
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
};