#pragma once
#include <string>
#include <iostream>
#include <vector>

class Movie {
private:

    std::string title;
    std::string genre;
    int year_of_release;
    int nr_of_likes;
    std::string trailer;

public:

    // Constructor, Destructor

    Movie();
    Movie(const std::string& title, const std::string& genre, int year_of_release, int nr_of_likes, const std::string& trailer);
    Movie(const Movie& m);
    ~Movie();

    // Operators Overload

    Movie& operator=(const Movie&);
    bool operator==(const Movie& m1) const;
    bool operator==(const std::string& title) const;
    friend std::ostream& operator<<(std::ostream& out, const Movie& m);
    friend std::istream& operator>>(std::istream& in, Movie& m);

    // Getters

    std::string getTitle() const;
    std::string getGenre() const;
    int getYearOfRelease() const;
    int getNrOfLikes() const;
    std::string getTrailer() const;

    // Setters

    void setGenre(const std::string& new_genre);
    void setYearOfRelease(int new_year_of_release);
    void setNrOfLikes(int new_nr_of_likes);
    void setTrailer(const std::string& new_trailer);

    /// <summary>Sets all attributes of a given movie (besides the title which is unique) to the given ones</summary>
    /// <param name="new_genre">int, the genre of the movie</param>
    /// <param name="new_year_of_release">int, the year which the movie was released in</param>
    /// <param name="new_nr_of_like">int, the number of like the movie has(rating)</param>
    /// <param name="new_trailer">string, the link to the trailer of the movie</param>
    /// <returns></returns
    void setNonUniqueAttributes(const std::string& new_genre, int new_year_of_release, int new_nr_of_likes, const std::string& new_trailer);

    std::string toString();
};

inline std::ostream& operator<<(std::ostream& out, const Movie& m) {
    out << m.title << ",";
    out << m.genre << ",";
    out << std::to_string(m.year_of_release) << ",";
    out << std::to_string(m.nr_of_likes) << ",";
    out << m.trailer;
    return out;
}

inline std::istream& operator>>(std::istream& in, Movie& m) {
    std::vector<std::string> fields;
    std::string field;
    for (int i = 0; i < 5; i++) {
        std::getline(in, field, ',');
        fields.push_back(field);
    }

    m.title = fields[0];
    m.genre = fields[1];
    m.year_of_release = std::stoi(fields[2]);
    m.nr_of_likes = std::stoi(fields[3]);
    m.trailer = fields[4];
    return in;
}
