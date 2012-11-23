#include <iostream>
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "clang/Tooling/Refactoring.h"
#include "llvm/Support/CommandLine.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;
using namespace llvm;

cl::opt<std::string> BuildPath(cl::Positional, cl::desc("<build-path>"));
cl::list<std::string> SourcePaths(cl::Positional, cl::desc("<source0> [... <sourceN>]"), cl::OneOrMore);


class ClassRenamer : public MatchFinder::MatchCallback
{
        Replacements *Replace;
    public:
        ClassRenamer(Replacements *_Replace) : Replace(_Replace) {}
        virtual void run(const MatchFinder::MatchResult &Result)
        {
            const CXXMethodDecl *D = Result.Nodes.getDeclAs<CXXMethodDecl>("method");
            if (!D)
                return;
            Replace->insert(Replacement(
                        *Result.SourceManager,
                        CharSourceRange::getTokenRange(
                            SourceRange(D->getLocation())),
                        "bla"));
        }
};


int main(int argc, char **argv)
{
    cl::ParseCommandLineOptions(argc, argv);

    std::string ErrorMessage;
    OwningPtr<CompilationDatabase> Compilations(CompilationDatabase::loadFromDirectory(BuildPath, ErrorMessage));

    if (!Compilations)
        report_fatal_error(ErrorMessage);

    RefactoringTool Tool(*Compilations, SourcePaths);


    MatchFinder Finder;
    ClassRenamer CallCallback(&Tool.getReplacements());
    Finder.addMatcher(id("class",methodDecl(hasName("Bar"))), &CallCallback);

    return Tool.run(newFrontendActionFactory(&Finder));
}
