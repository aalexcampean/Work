//
// Created by Alex Campean on 11.06.2022.
//

#include "IdeaRepo.h"
#include "../Exception/CustomException.h"

#include <iostream>
#include <fstream>
#include <sstream>

IdeaRepo::IdeaRepo(const std::string &filename) : fileName(filename) {
    this->load();
}

int IdeaRepo::getLength() {
    return ideas.size();
}

std::vector<Idea> IdeaRepo::getAll() const {
    return ideas;
}

std::vector<Idea> IdeaRepo::sortAllByAct() const {
    std::vector<Idea> sortedIdeas = ideas;
    std::sort(sortedIdeas.begin(), sortedIdeas.end(), [](Idea &idea1, Idea &idea2) {
        return idea1.getAct() < idea2.getAct();
    });
    return sortedIdeas;
}

std::vector<Idea> IdeaRepo::getAcceptedIdeas() const {
    std::vector<Idea> allIdeas = ideas;
    std::vector<Idea> acceptedIdeas;
    std::copy_if(allIdeas.begin(), allIdeas.end(), std::back_inserter(acceptedIdeas),
                 [](const Idea &idea) {
                     return idea.getStatus() == "Accepted";
                 });
    return acceptedIdeas;
}

void IdeaRepo::addIdea(const Idea &idea) {
    if (idea.getDescription().empty()) {
        throw CustomException(ExceptionTypes::EmptyFieldException);
    }
    if (idea.getAct() != 1 && idea.getAct() != 2 && idea.getAct() != 3) {
        throw CustomException(ExceptionTypes::InvalidActException);
    }

    ideas.push_back(idea);
    this->save();
}

void IdeaRepo::reviseIdea(int id) {
    auto it = std::find(ideas.begin(), ideas.end(), id);
    it->setStatus("Accepted");
    this->save();
}

Idea &IdeaRepo::operator[](int index) {
    return ideas[index];
}

void IdeaRepo::load() {
    std::ifstream input(fileName, 0);

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        Idea idea;
        if (!(iss >> idea)) { break; } // error

        ideas.push_back(idea);
    }
}

void IdeaRepo::save() {
    std::ofstream output(fileName);
    output << *this;
    output.close();
}

void IdeaRepo::savePlot() {
    std::vector<Idea> acceptedIdeas = this->getAcceptedIdeas();


    std::vector<Idea> firstActIdeas;
    std::copy_if(acceptedIdeas.begin(), acceptedIdeas.end(), std::back_inserter(firstActIdeas),
                 [](const Idea &idea) {
                     return idea.getAct() == 1;
                 });

    std::vector<Idea> secondActIdeas;
    std::copy_if(acceptedIdeas.begin(), acceptedIdeas.end(), std::back_inserter(secondActIdeas),
                 [](const Idea &idea) {
                     return idea.getAct() == 2;
                 });

    std::vector<Idea> thirdActIdeas;
    std::copy_if(acceptedIdeas.begin(), acceptedIdeas.end(), std::back_inserter(thirdActIdeas),
                 [](const Idea &idea) {
                     return idea.getAct() == 3;
                 });

    std::ofstream output("Plot.txt");

    output << "Act 1 -" << std::endl;
    for(auto& idea : firstActIdeas) {
        output << idea.getDescription() << " (" << idea.getCreator() << ")" << std::endl;
    }

    output << "Act 2 -" << std::endl;
    for(auto& idea : secondActIdeas) {
        output << idea.getDescription() << " (" << idea.getCreator() << ")" << std::endl;
    }

    output << "Act 3 -" << std::endl;
    for(auto& idea : thirdActIdeas) {
        output << idea.getDescription() << " (" << idea.getCreator() << ")" << std::endl;
    }

    output.close();
}


