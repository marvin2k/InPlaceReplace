#!/usr/bin/python

import sys
import cindex

# will return a list of "[file, line, column]" in locs
def search_namespaces(node, name, locs):

    # there is also "spelling" which is "None" for NAMESPACE_REF's
    if ((node.kind.name == 'NAMESPACE') | (node.kind.name == 'NAMESPACE_REF')) & \
       (node.displayname == name):

        locs.append([node.location.file, node.location.line, node.location.column])

        # print 'got thingy %s [line=%s, col=%s] in file %s' % (
        #     node.displayname,
        #     node.location.line,
        #     node.location.column, node.location.file)

    # Recurse for children of this node
    for c in node.get_children():
        search_namespaces(c,name,locs)

# usage:
#
# ./basic_example.py $CPPFILENAME $CLASSNAMEBEFORE $CLASSNAMEAFTER
#
def replace_namespace(filename, oldname, newname, flags = []):

    locs = []
    changed_files = []

    # prepare clang's infrastructure
    index = cindex.Index.create()
    tu = index.parse(filename, args=flags)
    # check if something went wrong
    for i in tu.diagnostics:
        if i.severity > 2:
            raise IndexError(i)

    search_namespaces(tu.cursor, oldname, locs)

    # now we have a list of [file, line, column]

    for loc in locs:
        if str(str(loc[0]).split('/')[-1]).find('ui_')==0: 
            print 'skipping ui ' + str(str(loc[0]).split('/')[-1])
            continue

        print 'working in %s:[%i,%i] ' % (
                loc[0], loc[1], loc[2])

        # open the file
        with open(str(loc[0])) as f:
            sourcecode = f.readlines()

        oldline = sourcecode[loc[1]-1]
        newline = oldline[:loc[2]-1] + newname + oldline[loc[2]-1+len(oldname):]

        # print 'oldline %s' % (oldline)
        # print 'newline %s' % (newline)
        sourcecode[loc[1]-1] = newline

        with open(str(loc[0]),'w') as f:
            f.writelines(sourcecode)

        changed_files.append(str(loc[0]))

        # check in locs if we have touched a line which is touched by other things aswell
        i = 0
        for temp in locs:
            if (str(temp[0]) == str(loc[0])):
                if (int(temp[1]) == int(loc[1])):
                    if (int(temp[2]) != int(loc[2])):
                        # and adopt start index to changed string
                        locs[i][2] = temp[2] + len(newname)-len(oldname)
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
