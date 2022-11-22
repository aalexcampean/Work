

#include <QApplication>
#include "Repository/QuestionRepo.h"
#include "Widgets/ParticipantWidget.h"
#include "Widgets/PresenterWidget.h"
#include "Repository/PersonsRepo.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	QuestionRepo questions{};
    PersonsRepo persons{};

    PresenterWidget presenter{questions};
    presenter.show();

    std::vector<ParticipantWidget*> participants;
    for (auto& person : persons.getAll()) {
        participants.push_back(new ParticipantWidget(person.getName(), questions));
    }

    for (auto& participant : participants) {
        participant->show();
    }

	return a.exec();
}
