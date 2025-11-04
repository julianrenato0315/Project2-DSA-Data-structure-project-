//I put this into chatgpt just to make the database
#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include "movie.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

vector<string> splitGenres(string s) {
    vector<string> g;
    string temp;
    stringstream ss(s);
    while (getline(ss, temp, '|')) g.push_back(temp);
    return g;
}

// Load movie metadata
unordered_map<int, Movie> loadMovies(string filename) {
    unordered_map<int, Movie> movies;
    ifstream file(filename);
    string line;

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, title, genres;
        getline(ss, idStr, ',');
        getline(ss, title, ',');
        getline(ss, genres, ',');

        int id = stoi(idStr);
        movies[id] = Movie(id, title, splitGenres(genres), 0);
    }

    return movies;
}

// Add ratings (compute average)
void loadRatings(string filename, unordered_map<int, Movie>& movies) {
    unordered_map<int, pair<double,int>> stats;
    ifstream file(filename);
    string line;

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string userId, movieIdStr, ratingStr;

        getline(ss, userId, ',');
        getline(ss, movieIdStr, ',');
        getline(ss, ratingStr, ',');

        int movieId = stoi(movieIdStr);
        double rating = stod(ratingStr);

        if (stats.count(movieId)==0)
            stats[movieId] = {0,0};

        stats[movieId].first += rating;
        stats[movieId].second++;
    }

    for (auto &p : stats) {
        int id = p.first;
        double total = p.second.first;
        int count = p.second.second;
        if (movies.count(id))
            movies[id].avgRating = total / count;
    }
}

#endif