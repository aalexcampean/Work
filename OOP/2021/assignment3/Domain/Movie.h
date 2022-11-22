#pragma once
#include <string>

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
    Movie(Movie& m);
    ~Movie();

    // Operators Overload

    Movie& operator=(const Movie&);
    bool operator==(const Movie& m1) const;
    bool operator==(const std::string& title) const;

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

    // String Representation

    /// <summary>Returns the string representation of a given element</summary>
    /// <param name=""></param>
    /// <returns>A string containing the string representation of a given element</returns
    std::string toString() const;

};