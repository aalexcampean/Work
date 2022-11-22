#include "../TextRepository/TextRepo.h"

class HtmlRepo : public TextRepo {
public:
    HtmlRepo();
    ~HtmlRepo();

    void save() override;
    void openFile() override;
};
