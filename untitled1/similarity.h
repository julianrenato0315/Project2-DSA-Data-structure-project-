//
// Created by julia on 11/3/2025.
//
#ifndef SIMILARITY_H
#define SIMILARITY_H

#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

// +1 for each shared genre (vector of genres of movie 1, vector of genres of move 2)
int genreSimilarity(const vector<string>& a, const vector<string>& b) {
    unordered_set<string> s(a.begin(), a.end());
    int score = 0;
    for (auto &genre : b) {
        if (s.count(genre) > 0) score++;
    }
    return score;
}

#endif