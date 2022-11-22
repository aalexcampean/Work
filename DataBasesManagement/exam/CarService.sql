CREATE TABLE Car(
    Id int IDENTITY(1,1),
    Name varchar(255) NOT NULL,
    Engine varchar(255) NOT NULL,
    Price int NOT NULL,
	LocationId int NOT NULL,
	CONSTRAINT PK_Car PRIMARY KEY (Id),
	CONSTRAINT FK_CarService FOREIGN KEY (LocationId)
	REFERENCES Location(Id)
);


CREATE TABLE Location(
    Id int IDENTITY(1,1),
	Coordinates int NOT NULL,
	CONSTRAINT PK_Location PRIMARY KEY (Id),
);

CREATE TABLE worksIn (
	Id int IDENTITY(1,1),
	EmployeeId int NOT NULL,
	LocationId int NOT NULL,
	CONSTRAINT PK_worksIn PRIMARY KEY (Id),
	CONSTRAINT FK_Employee FOREIGN KEY (EmployeeId)
	REFERENCES Employee(Id),
	CONSTRAINT FK_CarServiceworksIn FOREIGN KEY (LocationId)
	REFERENCES Location(Id)
);



CREATE TABLE Client(
    Id int IDENTITY(1,1),
    Name varchar(255) NOT NULL,
	carId int NOT NULL,
	CONSTRAINT PK_Client PRIMARY KEY (Id),
	CONSTRAINT FK_Car FOREIGN KEY (CarId)
	REFERENCES Car(Id),
);

CREATE TABLE hasACar (
	Id int IDENTITY(1,1),
	ClientId int NOT NULL,
	CarId int NOT NULL,
	CONSTRAINT PK_worksIn PRIMARY KEY (Id),
	CONSTRAINT FK_Client FOREIGN KEY (ClientId)
	REFERENCES Client(Id),
	CONSTRAINT FK_Car FOREIGN KEY (CarId)
	REFERENCES Car(Id),
);

CREATE TABLE Employee(
    Id int IDENTITY(1,1),
    Name varchar(255) NOT NULL,
    Surname varchar(255) NOT NULL,
    Age int NOT NULL,
	CONSTRAINT PK_Employee PRIMARY KEY (Id),
);


INSERT INTO Location(Coordinates)
VALUES (4), (5), (9), (10), (2), (3), (6)


INSERT INTO Car(Name, Engine, Price, LocationId)
VALUES	('Name1', 'engine1', 23, 1),
		('Name2', 'engine2', 76, 1),
		('Name3', 'engine3', 67, 2),
		('Name4', 'engine4', 25, 2),
		('Name5', 'engine5', 223, 3);