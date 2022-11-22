#include "../TextRepository/TextRepo.h"

class CsvRepo : public TextRepo {
public:
    CsvRepo();
    ~CsvRepo();

    void save() override;
    void openFile() override;
};
