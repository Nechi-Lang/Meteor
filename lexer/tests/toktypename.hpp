#pragma once

#include "../token.hpp"
#include <string>

inline std::string tokenKindToString(TokenKind kind) {
    switch (kind) {
        case TokenKind::Identifier: return "Identifier";

        case TokenKind::Write:      return "Write";
        case TokenKind::Exec:       return "Exec";
        case TokenKind::Module:     return "Module";
        case TokenKind::Import:     return "Import";
        case TokenKind::Func:       return "Func";

        case TokenKind::StringL:    return "String";
        case TokenKind::True:       return "Boolean True";
        case TokenKind::False:      return "Boolean False";

        case TokenKind::LParen:     return "LParen";
        case TokenKind::RParen:     return "RParen";
        case TokenKind::LBrace:     return "LBrace";
        case TokenKind::RBrace:     return "RBrace";

        case TokenKind::Semicolon:  return "Semicolon";
        case TokenKind::Comma:      return "Comma";

        case TokenKind::Eof:        return "Eof";

        default:
            return "Unknown";
    }
}
