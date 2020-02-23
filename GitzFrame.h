#include <git2.h>
#include "wx.h"

class GitzFrame : public wxFrame
{
public:
    GitzFrame();

    void AppendCommit(git_commit *commit);

private:
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

private:
    wxGrid *grid;
};