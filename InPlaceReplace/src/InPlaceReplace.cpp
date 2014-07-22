#include <iostream>

// http://clang.llvm.org/docs/LibASTMatchersReference.html

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/Refactoring.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;
using namespace llvm;

static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static cl::extrahelp MoreHelp(
        "\t this is the private help for the InPlaceReplace tool\n"
);

class ClassRenamer : public MatchFinder::MatchCallback
{
    Replacements *Replace;
    public:
    ClassRenamer(Replacements *_Replace) : Replace(_Replace) {}
    virtual void run(const MatchFinder::MatchResult &Result)
    {
        {
            const Decl *D = Result.Nodes.getNodeAs<Decl>("declaration");
            if (D) {
                    std::cout << "got declaration "
                              << D->getLocation().printToString(*Result.SourceManager) << "\n";
                Replace->insert(Replacement(
                            *Result.SourceManager,
                            CharSourceRange::getTokenRange(
                                SourceRange(D->getLocation())),
                            "pappel"));// this is the string which gets actually inserted
            }
        }

        {
            const MemberExpr *D = Result.Nodes.getNodeAs<MemberExpr>("reference");
            if (D) {
                std::cout << "got reference "
                    << D->getLocStart().printToString(*Result.SourceManager) << "\n";
                Replace->insert(Replacement(
                            *Result.SourceManager,
                            CharSourceRange::getTokenRange(
                                SourceRange(D->getExprLoc())),
                            "pappel"));// this is the string which gets actually inserted
            }
        }
    }
};


int main(int argc, const char **argv)
{
    /* the common-options parser provides the basic options: "-p<buildir>" and "sources" are the
     * more important ones. see "$0 --help" for more details.
     * see $HOME/llvm.git/tools/clang/tools/clang-check/ClangCheck.cpp */
    CommonOptionsParser OptionsParser(argc, argv);
    RefactoringTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());

    // a matcher to find a thing of type "tree" named "oak", to be reused
    DeclarationMatcher matcher = fieldDecl(hasName("oak"), hasType(recordDecl(hasName("plotz::tree"))));

    MatchFinder Finder;
    ClassRenamer CallCallback(&Tool.getReplacements());
    // wanna have "the one and only" declaration of out matcher
    Finder.addMatcher(fieldDecl(matcher).bind("declaration"),
            &CallCallback
            );
    // and also we wanna have all member-expressions where this one is used (?)
    Finder.addMatcher(
            memberExpr(member(matcher)).bind("reference"),
            &CallCallback
            );

    return Tool.runAndSave(newFrontendActionFactory(&Finder));
}
