//
// Created by Alex Campean on 06.04.2022.
//

#include "../Domain/Project.h"
#include <vector>

class Repository {
private:
    std::vector<Project> projects;
public:
    Repository();
    ~Repository();

    /// Getters
    int getRepositoryLength() const;
    std::vector<Project> getAllProjects() const;

    /// Add Project
    void addProjectRepository(const Project &project);

    /// Operator Overload
    Project& operator[](int index);
    friend std::ostream& operator<<(std::ostream& out, const Repository& repository);
};
inline std::ostream& operator<<(std::ostream& out, const Repository& repository) {
    std::for_each(repository.projects.begin(), repository.projects.end(), [&out](auto &it){
        out << it << "\n";
    });
    return out;
}


