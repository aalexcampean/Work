CREATE TABLE Producer (
    Id int IDENTITY(1,1),
    FirstName varchar(255) NOT NULL,
    LastName varchar(255) NOT NULL,
    Nationality varchar(255) NOT NULL,
	NoOfAwards int NOT NULL
	CONSTRAINT PK_Producer PRIMARY KEY (Id),
);

CREATE TABLE Category (
    Id int IDENTITY(1,1),
    Name varchar(255) NOT NULL,
	Description varchar(255) NOT NULL,
	CONSTRAINT PK_Category PRIMARY KEY (Id),

);

CREATE TABLE Cinema (
    Id int IDENTITY(1,1),
    Name varchar(255) NOT NULL,
	Location varchar(255) NOT NULL,
	NoOfSeats int NOT NULL,
	CONSTRAINT PK_Cinema PRIMARY KEY (Id)
);


CREATE TABLE Movie(
    Id int IDENTITY(1,1),
    Title varchar(255) NOT NULL,
    ProducerId int NOT NULL,
    CategoryId int NOT NULL,
	CONSTRAINT PK_Movie PRIMARY KEY (Id),
	CONSTRAINT FK_Producer FOREIGN KEY (ProducerId)
	REFERENCES Producer(Id),
	CONSTRAINT FK_Category FOREIGN KEY (CategoryId)
	REFERENCES Category(Id)
);

CREATE TABLE Schedule(
	Id int IDENTITY(1,1),
	MovieId int NOT NULL,
	CinemaId int NOT NULL,
	StartHour int NOT NULL,
	NoOfSoldTickets int NOT NULL,
	CONSTRAINT PK_Schedule PRIMARY KEY (Id),
	CONSTRAINT FK_Movie FOREIGN KEY (MovieId)
	REFERENCES Movie(Id),
	CONSTRAINT FK_Cinema FOREIGN KEY (CinemaId)
	REFERENCES Cinema(Id)
);


INSERT INTO Category(Name, Description)
VALUES	('Category1','Description1'), 
		('Category2','Description2'),
		('Category3','Description3'),
		('Category4','Description4'),
		('Category5','Description5'),
		('Category6','Description6'),
		('Category7','Description7');

INSERT INTO Producer(FirstName, LastName, Nationality, NoOfAwards)
VALUES	('Alexnadra', 'Gog', 'Nat1', 3),
		('Anca', 'ede', 'Nat1', 4),
		('Simina', 'ewfewf', 'Nat1', 5),
		('Alex', 'fwefw', 'Nat1', 6),
		('Victor', 'asdfghj', 'Nat1', 9),
		('Tudor', 'Pop', 'Nat1', 10);