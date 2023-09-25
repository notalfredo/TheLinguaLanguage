#include <memory>
namespace {
    class ExprAST{
    
        public:
            virtual ~ExprAST() = default;
    };

    class BinOpNode: public ExprAST {
        char BinOpType;
        std::unique_ptr<ExprAST> LHS, RHS;

        public:
            BinOpNode(char BinOpType, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS)
            : BinOpType(BinOpType), LHS(std::move(LHS)), RHS(std::move(RHS)) {} 
    };

    class NumberNode: public ExprAST {
        int number; 
        
        public:
            NumberNode(int number): number(number) {}
    };

    class VariableNode: public ExprAST {
        std::string name;
        
        public:
            VariableNode(std::string name): name(name) {}
    };
}
