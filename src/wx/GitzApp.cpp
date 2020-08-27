#include <memory>
#include <git2.h>
#include "GitzApp.h"
#include "GitzFrame.h"

bool CheckGitResult(int result, const wxString &message)
{
    if (result != 0) {
        wxMessageBox((message + ": ") + git_error_last()->message, "Error", wxOK | wxICON_ERROR);
        return false;
    }
    return true;
}

bool GitzApp::OnInit()
{
    auto repoPath = argc > 1 ? argv[1] : wxGetCwd();

    auto frame = new GitzFrame();
    frame->Show(true);
    frame->SetSize(800, 600);

    git_libgit2_init();

    git_repository *repo;
    if (!CheckGitResult(
            git_repository_open(&repo, repoPath.c_str()),
            "Failed to open repository")) {
        return false;
    }

    git_revwalk *walker;
    if (!CheckGitResult(
            git_revwalk_new(&walker, repo),
            "Failed to read repository history")) {
        git_repository_free(repo);
        return false;
    }

    git_revwalk_sorting(walker, GIT_SORT_TOPOLOGICAL | GIT_SORT_TIME);
    git_revwalk_push_head(walker);
    git_revwalk_hide_glob(walker, "tags/*");

    git_oid commit_id;
    git_commit *commit = nullptr;

    while (true) {
        git_commit_free(commit);

        auto result = git_revwalk_next(&commit_id, walker);
        if (result == GIT_ITEROVER) {
            break;
        }
        if (!CheckGitResult(result, "Failed to walk revision history")) {
            break;
        }

        if (!CheckGitResult(
                git_commit_lookup(&commit, repo, &commit_id),
                "Failed to look up commit")) {
            break;
        }

        frame->AppendCommit(commit);
    }

    git_revwalk_free(walker);
    git_repository_free(repo);

    return true;
}
