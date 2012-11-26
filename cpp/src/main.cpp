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
        {
            const Decl *D = Result.Nodes.getNodeAs<Decl>("first");
            if (D) {
                std::cout << "got smth " << D->getLocation().printToString(*Result.SourceManager) << "\n";
                Replace->insert(Replacement(
                            *Result.SourceManager,
                            CharSourceRange::getTokenRange(
                                SourceRange(D->getLocation())),
                            "first"));
            }
        }

            {
                const Expr *D = Result.Nodes.getNodeAs<Expr>("second");
                if (D) {
                    std::cout << "got smth " << D->getExprLoc().printToString(*Result.SourceManager) << "\n";
                    Replace->insert(Replacement(
                                *Result.SourceManager,
                                CharSourceRange::getTokenRange(
                                    SourceRange(D->getExprLoc())),
                                "second"));
                }
            }
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
    // works but find two matches, one too much... the "int mBase" which is another one
        Finder.addMatcher(
            id("first",decl(fieldDecl(hasName("mBase"),has(hasType(recordDecl(hasName("blabla")))))))),
            &CallCallback
            );
    // kinda works, one too many aswell... the "struct blupp" declaration...
        Finder.addMatcher(
            id("second",expr(hasType(recordDecl(hasName("repretest::blabla"))))),
            &CallCallback
            );


    return Tool.run(newFrontendActionFactory(&Finder));
}
