CREATE TABLE Contact (
    Id int IDENTITY(1,1),
    LastName varchar(255) NOT NULL,
    FirstName varchar(255) NOT NULL,
    PhoneNumber varchar(255) NOT NULL,
	CONSTRAINT PK_Contacts PRIMARY KEY (Id)
);

CREATE TABLE EmailAdress (
    Id int IDENTITY(1,1),
    EmailAdr varchar(255) NOT NULL,
    ContactId int NOT NULL,
	CONSTRAINT PK_EmailAdress PRIMARY KEY (Id),
	CONSTRAINT FK_EmailAdress FOREIGN KEY (ContactId)
    REFERENCES Contact(Id)
);

CREATE TABLE Email (
    Id int IDENTITY(1,1),
    Subject varchar(255) NOT NULL,
	CONSTRAINT PK_Email PRIMARY KEY (Id)
);


CREATE TABLE sendTo(
    Id int IDENTITY(1,1),
    emailAdrId int NOT NULL,
	emailId int NOT NULL,
	CONSTRAINT PK_sentTo PRIMARY KEY (Id),
	CONSTRAINT FK_email FOREIGN KEY (emailId) REFERENCES Email(Id),
	CONSTRAINT FK_emailAdr FOREIGN KEY (emailAdrId) REFERENCES EmailAddress(Id)
);


CREATE TABLE Meetings (
    Id int IDENTITY(1,1),
    MeetingType varchar(255) NOT NULL,
    MeetingDay varchar(255) NOT NULL,
	CONSTRAINT PK_Meetings PRIMARY KEY (Id)
);


CREATE TABLE MeetingParticipant (
    Id int IDENTITY(1,1),
	ParticipantFirstName varchar(255) NOT NULL,
	ParticipantLastName varchar(255) NOT NULL,
	PhoneNumber varchar(255) NOT NULL,
	MeetingId int NOT NULL,
	CONSTRAINT PK_MeetingParticipant PRIMARY KEY (Id),
	CONSTRAINT FK_MeetingParticipant FOREIGN KEY (MeetingId)
    REFERENCES Meetings(Id)
);


INSERT INTO Contact(FirstName, LastName, PhoneNumber) 
VALUES	('Alexandra', 'Gog', '074592369'), 
		('Anca', 'Chetan', '0741253669'),
		('Simina', 'Terec', '071258369'),
		('Alex', 'Campean', '0712345678'),
		('Iulia', 'Farcas', '074554569'),
		('Andrei', 'Gog', '075484649'),
		('Thea', 'Crainic', '072545169'),
		('Tudor', 'Pop', '074592369'),
		('Mihai', 'Antonescu', '071269569'),
		('Gabriel', 'Iacob', '075122869');


INSERT INTO Meetings(MeetingType, MeetingDay) 
VALUES	('Work', '2022-03-23'),
		('School', '2022-03-23'),
		('Fun', '2022-03-24'),
		('Work', '2022-03-27'),
		('Work', '2022-03-28'),
		('Family', '2022-03-27'),
		('Fun', '2022-03-21'),
		('Work', '2022-03-22'),
		('Work', '2022-03-30');