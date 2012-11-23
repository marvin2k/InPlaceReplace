#!/usr/bin/python

from basic_example import replace_namespace
import subprocess
import json
import sys

# missing:
# - skip moc-compiles from json-list
#
workingBranch = 'temp'

# where to check changes in
gitRepo = '/home/mzenzes/InPlaceReplace'


# helper function
def gitAdd(fileName, repoDir):
    cmd = ['git', 'add', fileName]
    p = subprocess.Popen(cmd, cwd=repoDir)
    return p.wait()

# helper function
def gitBranch(branchName, repoDir):
    cmd = ['git', 'branch', branchName]
    p = subprocess.Popen(cmd, cwd=repoDir)
    return p.wait()

def gitCheckout(branchName, repoDir):
    cmd = ['git', 'checkout', branchName]
    p = subprocess.Popen(cmd, cwd=repoDir)
    return p.wait()

# helper function
def gitCommit_m(message, repoDir):
    cmd = ['git', 'commit', '-m', message]
    p = subprocess.Popen(cmd, cwd=repoDir)
    return p.wait()

# the core function, recevies one entry from the json-list
def process_unit(json_entry, oldname, newname):

    filename = json_entry['file']
    # print 'filename ' + filename
    [flags, sep, rest] = json_entry['command'].partition(' -o ');
    flags = flags.split(' ')
    flags.append('-I/home/mzenzes/llvm.install/lib/clang/3.2/include')
    # print 'args ' + str(len(flags))

    try:
        changed_files = replace_namespace(filename, oldname, newname, flags)
    except IndexError as clang_diagnostic:
        print 'exception: ' + str(clang_diagnostic)
        return

    # uniqify see http://www.peterbe.com/plog/uniqifiers-benchmark
    changed_files_unique = list(set(changed_files))

    print 'namespace replacing in ' + filename + ' finished, ' + str(len(changed_files_unique)) + ' files changed'

    if len(changed_files_unique)>0:

        for entry in changed_files_unique:
            # print 'gitAdd ' + str(entry)
            gitAdd(str(entry),gitRepo)

        gitCheckout(workingBranch,gitRepo)
        gitCommit_m('[InPlaceReplace] ' + filename + '\n\nautochanged namespace '+oldname+' to '+newname+' in '+filename, gitRepo)
        gitCheckout('private',gitRepo)

# usage
#
# ./complex_example $JSONFILE
#
#
#
#
def main():

    json_file = sys.argv[1]
    oldname = sys.argv[2]
    newname = sys.argv[3]

    commands = json.loads(open(json_file).read());

    gitBranch('private',gitRepo)
    gitBranch(workingBranch,gitRepo)
    gitCheckout(workingBranch,gitRepo)

    for entry in commands:
        # skip moc files:
        filename = str(entry['file'].split('/')[-1])
        if filename.find('moc_')==0:
            print 'skipping moc ' + filename
            continue
        if filename.find('qrc_')==0:
            print 'skipping qrc ' + filename
            continue

        process_unit(entry, oldname, newname)
        print 'translation unit ' + filename + ' finished'

if __name__ == "__main__":
    main()
