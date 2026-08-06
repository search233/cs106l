#ifndef A4_SPELLCHECK_CPP__
#define A4_SPELLCHECK_CPP__

#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
    /* TODO: Implement this method */

    auto spase_lis = find_all(source.begin(), source.end(), ::isspace);

    Corpus tokens;

    std::transform(spase_lis.begin(),
                spase_lis.end() - 1,
                spase_lis.begin() + 1,
                std::inserter(tokens, tokens.end()),
                [&source](auto it1, auto it2) {
                    return Token(source, it1, it2);
    });
    
    std::erase_if(tokens, [](const Token& token) {return token.content.empty();});
    
    return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
    /* TODO: Implement this method */
    namespace rv = std::ranges::views;

    auto notContains = [&dictionary](const Token& token) -> bool {
        return !dictionary.contains(token.content); 
    };

    auto view = source 
    | rv::filter(notContains)
    | rv::transform(
        [&dictionary](const Token& token) -> Misspelling {
            
            auto disEq1 = [&token](const std::string& s) -> bool {
                return levenshtein(token.content, s) == 1;
            };

            auto sugges = dictionary 
            | rv::filter(disEq1) 
            | std::ranges::to<std::set<std::string>>();
            
            return Misspelling{token, sugges};
        }
    );

    auto haveSugges = [](const Misspelling& element) -> bool {
        return !element.suggestions.empty();
    };

    return view 
    | rv::filter(haveSugges)
    | std::ranges::to<std::set<Misspelling>>();
};

/* Helper methods */

#include "utils.cpp"

#endif
