#!/usr/bin/python

import sys
import cindex
import re

# will return a list of "[file, line, column, oldname]" in locs
def searchNodes(node, pattern, locs, namelist):

    m = re.match(pattern,node.displayname)
    if m:
        #print 'got thingy %s [line=%s, col=%s] in file %s of type %s' % (
        #    node.displayname,
        #    node.location.line,
        #    node.location.column,
        #    node.location.file,
        #    node.kind.name)

        if any(node.kind.name in s for s in namelist):

            print 'got thingy %s of type %s [line=%s, col=%s, len=%i] in file %s' % (
                 node.displayname,
                 node.kind.name,
                 node.location.line,
                 len(node.displayname),
                 node.location.column, node.location.file)

            locs.append([node.location.file, node.location.line, node.location.column, node.displayname])

    # Recurse for children of this node
    for c in node.get_children():
        searchNodes(c,pattern,locs,namelist)

# usage:
#
# ./basic_example.py $CPPFILENAME $CLASSNAMEBEFORE $CLASSNAMEAFTER
#
def replace_namespace(filename, oldname, newname, task, flags = []):

    locs = []
    changed_files = []

    # prepare clang's infrastructure
    index = cindex.Index.create()
    tu = index.parse(filename, args=flags)
    # check if something went wrong
    for i in tu.diagnostics:
        if i.severity > 2:
            raise IndexError(i)

    if task == "namespace":
        namelist = ['NAMESPACE',
                    'NAMESPACE_REF']
        searchNodes(tu.cursor, oldname, locs, namelist)

    elif task == "variable":
        namelist = ['PARM_DECL',
                    'UNEXPOSED_EXPR',
                    'DECL_REF_EXPR',
                    'FIELD_DECL',
                    'MEMBER_REF',
                    'MEMBER_REF_EXPR',
                    'UNEXPOSED_EXPR',
                    'DECL_REF_EXPR']
        searchNodes(tu.cursor, "m[A-Z].*", locs, namelist)

    else:
        raise NameError("wooooo")

    # now we have a list of [file, line, column], but we care for unique
    # entrys. this specific solution is ugly and very slow. pyhton experts,
    # here you go!
    locs_unique = []
    for loc in locs:
        doubled = 0
        for other in locs_unique:
            if (str(loc[0]) == str(other[0]))&(int(loc[1]) == int(other[1]))&(int(loc[2]) == int(other[2]))&(str(loc[3]) == str(other[3])):
                doubled = doubled+1
        if (doubled==0):
            locs_unique.append(loc)

    locs = locs_unique

    for loc in locs:
        if str(str(loc[0]).split('/')[-1]).find('ui_')==0: 
            print 'skipping ui ' + str(str(loc[0]).split('/')[-1])
            continue

        print 'working in %s:[%i,%i] with %s ' % (
                loc[0], loc[1], loc[2], loc[3])

        # open the file
        with open(str(loc[0])) as f:
            sourcecode = f.readlines()

        oldline = sourcecode[loc[1]-1]
        _oldname = loc[3]
        if task == "namespace":
            _newname = newname
        elif task == "variable":
            _newname = _oldname[1].lower() + _oldname[2:]
        newline = oldline[:loc[2]-1] + _newname + oldline[loc[2]-1+len(_oldname):]

        # print 'oldline %s' % (oldline)
        # print 'newline %s' % (newline)
        sourcecode[loc[1]-1] = newline

        with open(str(loc[0]),'w') as f:
            f.writelines(sourcecode)

        changed_files.append(str(loc[0]))

        # check in locs if we have touched a line which is touched later again
        i = 0
        for temp in locs:
            # same file as now
            if (str(temp[0]) == str(loc[0])):
                # same line
                if (int(temp[1]) == int(loc[1])):
                    # but different column
                    if (int(temp[2]) != int(loc[2])):
                        # and adopt start index to changed string
                        locs[i][2] = temp[2] + len(_newname)-len(_oldname)
                        # print 'changed line ' + str(temp[1]) + ' col ' + str(temp[2]) + ' to ' + str(locs[i][2]) + ' in file ' + str(temp[0])

            i = i+1

    return changed_files

def main():
    
    filename = sys.argv[1]
    # the name of the namespace to replace
    oldname = sys.argv[2]
    newname = sys.argv[3]

    replace_namespace(filename, oldname, newname, ['-I/usr/include'])

if __name__ == "__main__":
    main()
