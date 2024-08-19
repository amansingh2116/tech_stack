# Git & GitHub

Git version control system helps to track changes in code and to collaborate in a project by different users

GitHub website allows developers to store and manage their code using git.

`README.md` is a special file where we can write about the project/repository.

### Basic Commands:

- ~ (root directory)
- `git --version` (current version of installed git)
- `git config -- global user.name “My Name”` ( set a name that is identifiable for credit when review version history)
- `git config -- global user.email "email@mail"` ( set an email address that will be associated with each history marker)
- `git config --list` (configuration settings)
- `ls` (list all the files/folders in the current directory)
- `mkdir` folder (creates a folder in the current directory)
- `cd folder_name` (change current working directory to `folder_name`)
- `clear` (clear terminal)
- `git init` (initialize empty git repository)
- `ls -a` (show hidden files)
- `ls .git` (open `.git` i.e., the hidden file where all the history is stored as a working tree)
- `touch names.txt` (create a new file in the current directory)
- `git status` (changes that are not staged or committed in the `.git` ; it involves *untracked* (new files that git doesn’t yet track), **modified** (changed), *staged* (file ready to be committed), *unmodified* (unchanged) )
- `git add file_name` (stage new file or changes in `file_name` to `.git`)
- `git add .` (stage all changes to `.git`)
- `git commit -m “message”` (commit i.e., record all staged changes to `.git` with the “message”)
- `git log` (lists all the commits with their commit hash and date & time for the currently active branch)

### Workflow Commands

- `git clone repo_link` ( retrieve an entire repository from a hosted location via URL)
- fork (a rough copy or new repository that shares codes and visibility settings with the original “upstream” repository in your GitHub; you have to create a pull request to merge your changes in the fork to push it the original repo)
- `git remote add origin repo_link` (add a git URL(`repo_link`) as an alias (here origin))
- `git remote -v` (to verify remote)
- `git fetch [alias]` (fetch down all the branches from that Git remote)
- `git branch` (to check branch i.e., a local self made copy of repo with all the commits which can be further merged to the main/master branch, its purpose is to make simultaneous changes in a repository thus providing collaborative features)
- `git branch -M main` (to rename current branch to main)
- `git push origin main` (upload local repo content/changes to remote repo in GitHub, origin is the default name of remote repo at GitHub and main in the branch name you are pushing your code through)
- `git push -u origin main` (set upstream, so next time we can just use `git push` instead of `git push origin main`)
- `git pull origin main` (to fetch and download content from a remote repo and immediately update the local repo to match that content)

### Undoing Changes

Staged changes

- `git reset file_name` (reset staged changes in `file_name`)
- `git reset` (reset all staged changes)

Committed changes

- `git reset HEAD~1` (reset last commit and bring it back to un-staged status)
- `git reset commit_hash` (reset to the given commit hash)
- `git reset --hard commit_hash` (reset to the given commit hash in local repo too)
- `git rebase branch_name` (apply any commits of current branch ahead of specified one)

### Temporary Commits

- `git stash` (Save modified and staged changes)
- `git stash list` (list stack-order of stashed file changes)
- `git stash pop` (write working from top of stash stack)
- `git stash drop` (discard  the changes from top of stash stack)

### Branch commands

- `git checkout branch_name` (to navigate to `branch_name`)
- `git checkout -b new_branch` (to create new branch)
- `git checkout -d branch_name` (to delete `branch_name`, but first you have to navigate to a different branch)

### Merging Code

- Way 1
`git diff branch_name` (to compare commits, branches, files and more)
`git diff` (diff of what is changed but not staged)
`git diff --staged` (diff of what is staged but not yet committed)
`git merge branch_name` (to merge 2 branches, current and `branch_name`)
- Way 2
Create a ***Pull Request*** (lets you tell others about the changes you’ve pushed to a branch in a repository on GitHub, try to make different branches for different pull requests)
Compare & Pull Request → Create a Pull Request → Merge Pull Request (add a message and review before merging)
- Resolving Merge Conflicts
an event that takes place when Git is unable to automatically resolve differences in code between two commits while merging branches
Way 1 : Resolve using VS Code merge editor
Way 2 : Resolve in GitHub merge conflict resolve

There are three commands with similar names: `git reset`, `git restore` and `git revert`.

- `git revert` is about making a new commit that reverts the changes made by other commits.
- `git restore` is about restoring files in the working tree from either the index or another commit. This command does not update your branch. The command can also be used to restore files in the index from another commit.
- `git reset` is about updating your branch, moving the tip in order to add or remove commits from the branch. This operation changes the commit history.`git reset` can also be used to restore the index, overlapping with `git restore`.
- `git switch` can now be used to change branches, as `git checkout <branchname>` does
- `git restore` can be used to reset files to certain revisions, as `git checkout -- <path_to_file>` does