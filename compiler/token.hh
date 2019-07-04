#ifndef _FLANER_COMPILER_TOKEN_HH_
#define _FLANER_COMPILER_TOKEN_HH_

/*
* File: token.hh
* 定义 token 模型和列表
*/

#include <string>
#include <vector>

namespace Flaner
{
    namespace Compiler
    {
        namespace Lex
        {
            enum TokenType
            {
                TOKEN_UNKNOWN,

                TOKEN_ID,

                TOKEN_NUMBER,   // 123456
				TOKEN_BIGINT,   // 123456n
				TOKEN_RATIONAL, // 123r456
                TOKEN_STRING,

                TOKEN_LET,
                TOKEN_CONST,

                TOKEN_IF,
                TOKEN_ELSE,
                TOKEN_SWITCH,
                TOKEN_CASE,
                TOKEN_DEFAULT,
                TOKEN_WHILE,
                TOKEN_DO,
                TOKEN_FOR,
                TOKEN_CONTINUE,
                TOKEN_BREAK,
                TOKEN_RETURN,
                TOKEN_THROW,
                TOKEN_TRY,
                TOKEN_CATCH,
                TOKEN_FINALLY,
                TOKEN_AS,
                TOKEN_IN,
                TOKEN_OF,
                TOKEN_IMPORT,
                TOKEN_EXPORT,

                TOKEN_THIS,
                TOKEN_NULL,
                TOKEN_TRUE,
                TOKEN_FALSE,          

                TOKEN_PAREN_BEGIN,     // (
                TOKEN_PAREN_END,       // )
                TOKEN_BRACKET_BEGIN,   // [
                TOKEN_BRACKET_END,     // ]
                TOKEN_BRACE_BEGIN,     // {
                TOKEN_BRACE_END,       // }

				TOKEN_BIT_NOT,         // ~        
				TOKEN_LOGIC_NOT,       // !
				TOKEN_TYPEOF,          // typeof

				TOKEN_LOGIC_AND,       // &&
				TOKEN_BIT_AND,         // &
				TOKEN_LOGIC_OR,        // ||
				TOKEN_BIT_OR,          // |
				TOKEN_LOGIC_XOR,       // ^^
				TOKEN_BIT_XOR,         // ^
				
				TOKEN_PIPELINE,        // |>
				TOKEN_EQUAL,           // ==
				TOKEN_NOT_EQUAL,       // !=
				TOKEN_LESS_THAN,       // <
				TOKEN_GREATER_THAN,    // >
				TOKEN_LESS_EQ_THAN,    // <=
				TOKEN_GREATER_EQ_THAN, // >=
				TOKEN_SPACESHIP,       // <=>

				TOKEN_ADD,             // +
				TOKEN_SUB,             // -
				TOKEN_MUL,             // *
				TOKEN_DIV,             // /
				TOKEN_MOD,             // %
				TOKEN_POW,             // **
				TOKEN_SAL,             // <<
				TOKEN_SRL,             // >>
				TOKEN_ROL,             // <<<
				TOKEN_ROR,             // >>>

                TOKEN_FUNCTION_ARROW,  // =>
				
                TOKEN_COLON,           // :
                TOKEN_COMMA,           // ,
                TOKEN_DOT,             // .
                TOKEN_DOT_DOT_DOT,     // ...
                TOKEN_QUESTION,        // ?
                TOKEN_SEMICOLON        // ;
            };

            struct Token
            {
                TokenType type;
                std::string value;

                Token(TokenType _type, std::string _value) : type(_type), value(_value) {}

                inline char raw_value()
                {
                    return value.data()[0];
                }

                // 以下方法用于确定 token 的范围

                inline bool isStringLiteral()
                {
                    return this->type == TOKEN_STRING;
                }

                inline bool isNumberLiteral()
                {
                    return this->type == TOKEN_NUMBER;
                }


                // 用于确定 token 是否与指定类型相等
                inline bool operator==(TokenType t)
                {
                    return type == t;
                }

                inline bool operator!=(TokenType t)
                {
                    return type != t;
                }

                inline bool eq(TokenType t)
                {
                    return *this == t;
                }

                inline bool noteq(TokenType t)
                {
                    return *this != t;
                }
            };


            class TokenList
            {
            private:
                std::vector<std::shared_ptr<Token>> tokens;
                unsigned int cursor;
            public:

                TokenList() noexcept : cursor(0) {}

                /*
                * 术语定义
                *         向后       当前      向前
                * 第一个 <------------#------------> 最后一个
                */

                // 在末尾移入一个 token
                void push(std::shared_ptr<Token> token);

                // 移出并得到最后一个 token
                std::shared_ptr<Token> pop();

                // 设置游标位置
                void reset(unsigned int n = 0);

                // 获取当前游标位置
                int pos();

                // 获取上一个 token，游标不变
                std::shared_ptr<Token> last();

                // 获取当前 token
                std::shared_ptr<Token> now();

                // 获取下一个 token，游标不变
                std::shared_ptr<Token> next();

                // 将游标向前移动 n 个位置，并得到当前 token
                std::shared_ptr<Token> forward(unsigned int n);
                std::shared_ptr<Token> forward();

                // 将游标后前移动 n 个位置，并得到当前 token
                std::shared_ptr<Token> backward(unsigned int n);
                std::shared_ptr<Token> backward();

                // 获取第一个 token
                std::shared_ptr<Token> first();

                // 获取最后一个 token
                std::shared_ptr<Token> end();
                
            };
        };
    };
};

#endif // !_FLANER_COMPILER_TOKEN_HH_
