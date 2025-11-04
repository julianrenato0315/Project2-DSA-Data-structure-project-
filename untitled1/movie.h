
#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>
using namespace std;

struct Movie {
    int id;
    string title;
    vector<string> genres;
    double avgRating;

    Movie() {}
    Movie(int i, string t, vector<string> g, double r)
        : id(i), title(t), genres(g), avgRating(r) {}
};

#endif