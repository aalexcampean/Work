#pragma once
#include "../MemoryRepository/MemoryRepo.h"
#include "../Exception/CustomException.h"

class TextRepo : public MemoryRepo {
private:
    std::string file_name;

    void load();
    void save();

public:
    TextRepo();
    TextRepo(const std::string& file);
    TextRepo(const TextRepo& text_repo);
    ~TextRepo();

    TextRepo& operator=(const TextRepo &repo);
    virtual void openFile(){throw CustomException(0002, "Functionality not implemented for class TextRepo");};
};