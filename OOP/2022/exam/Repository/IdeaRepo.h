//
// Created by Alex Campean on 11.06.2022.
//
#pragma once
#include "../Domain/Idea.h"

class IdeaRepo {
private:
    std::vector<Idea> ideas;
    std::string fileName;

    void load();
    void save();
public:
    IdeaRepo(const std::string &filename = "Ideas.txt");
    ~IdeaRepo(){};

    int getLength();
    std::vector<Idea> getAll() const;
    std::vector<Idea> sortAllByAct() const;
    std::vector<Idea> getAcceptedIdeas() const;

    void addIdea(const Idea &idea);
    void reviseIdea(int id);

    void savePlot();

    Idea& operator[](int index);
    friend std::ostream& operator<<(std::ostream& stream, const IdeaRepo &repository);
};

inline std::ostream& operator<<(std::ostream& stream, const IdeaRepo &repository) {
    for (auto& it : repository.getAll()) {
        stream << it << "\n";
    }
    return stream;
}
