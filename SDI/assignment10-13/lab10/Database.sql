CREATE TABLE Owner
(
    ID          INT GENERATED ALWAYS AS IDENTITY,
    FirstName   VARCHAR NOT NULL,
    LastName    VARCHAR NOT NULL,
    Email       VARCHAR NOT NULL,
    PhoneNumber VARCHAR NOT NULL,
    DateOfBirth VARCHAR NOT NULL,
    CONSTRAINT PK_Owner PRIMARY KEY (ID)
);

INSERT INTO Owner(FirstName, LastName, Email, PhoneNumber, DateOfBirth)
VALUES ('Alexandru', 'Campean', 'alexc.campean@yahoo.com', '0737239657', '2001/10/06'),
       ('Alexandra', 'Gog', 'alexandra.gog@gmail.com', '0745569901', '2001/04/22'),
       ('Florin', 'Ciocan', 'florin.ciocan@gmail.com', '0733554099', '2001/01/05'),
       ('Catinca', 'Cotor', 'cati.cotor@icoloud.com', '07456669011', '2001/04/08'),
       ('Cupes', 'Andrei', 'andrei.cupes@gmail .com', '07137688990', '2001/11/29'),
       ('Iulia', 'Chereji', 'iulia.chereji@yahoo.com', '07113324767', '2002/02/08');

CREATE TABLE Vet
(
    ID          INT GENERATED ALWAYS AS IDENTITY,
    FirstName   VARCHAR NOT NULL,
    LastName    VARCHAR NOT NULL,
    Email       VARCHAR NOT NULL,
    PhoneNumber VARCHAR NOT NULL,
    DateOfBirth VARCHAR NOT NULL,
    Salary      INT CHECK (0 < Salary),
    Rating      INT DEFAULT 5 CHECK (0 < Rating) CHECK (Rating < 6),
    CONSTRAINT PK_Vet PRIMARY KEY (ID)
);
DROP TABLE Vet;

INSERT INTO Vet(FirstName, LastName, Email, PhoneNumber, DateOfBirth, Salary, Rating)
VALUES ('Mircea', 'Popescu', 'mircea.popescu@bestfriendclinic.ro', '0722565989', '1970/04/02', 4000, 4),
       ('Alexandra', 'Negoiu', 'alexandra.negoiu@bestfriendclinic.ro', '0729154676', '1988/10/20', 3700, 5),
       ('Marian', 'Negru', 'marian.negru@bestfriendclinic.ro', '0777091182', '1991/03/11', 2900, 5),
       ('Tudor', 'Vacaru', 'tudor.vacaru@bestfriendclinic.ro', '0712651362', '1996/09/14', 3000, 5),
       ('Iulia', 'Tantau', 'iulia.tantau@bestfriendclinic.ro', '0791923954', '1978/10/05', 3500, 4);

CREATE TABLE Pet
(
    ID              INT GENERATED ALWAYS AS IDENTITY,
    Species         VARCHAR NOT NULL,
    Breed           VARCHAR NOT NULL,
    Name            VARCHAR NOT NULL,
    DateOfEnrolment VARCHAR NOT NULL,
    PersonID        INT,
    CONSTRAINT PK_Pet PRIMARY KEY (ID),
    CONSTRAINT FK_PetToOwner FOREIGN KEY (PersonID) REFERENCES Owner (ID)
);
DROP TABLE Pet;

INSERT INTO Pet (Species, Breed, Name, DateOfEnrolment, PersonID)
VALUES ('Dog', 'Dobermann', 'Abel', '2015/10/10', 1),
       ('Dog', 'Ibizan Hound', 'Rick', '2018/09/09', 1),
       ('Cat', 'Persian', 'Ludmila', '2018/04/22', 4),
       ('Dog', 'Labrador', 'Milo', '2016/02/115', 5),
       ('Chinchilla', 'Long-tailed', 'Ashy', '2021/07/04', 3),
       ('Dog', 'Akita Inu', 'Gorge', '2019/07/11', 2),
       ('Cat', 'British Shorthair', 'Ricky', '2022/03/21', 6);

CREATE TABLE Appointment
(
    ID    INT GENERATED ALWAYS AS IDENTITY,
    PetID INT,
    VetID INT,
    Type  VARCHAR NOT NULL,
    Date  VARCHAR NOT NULL,
    CONSTRAINT PK_Appointment PRIMARY KEY (ID),
    CONSTRAINT FK_AppointmentToPet FOREIGN KEY (PetID) REFERENCES Pet (ID),
    CONSTRAINT FK_AppointmentToVet FOREIGN KEY (VetID) REFERENCES Vet (ID)
);
DROP TABLE Appointment;

INSERT INTO Appointment (PetID, VetID, Type, Date)
VALUES (1, 3, 'Routine Checkup', '2020/10/02'),
       (1, 3, 'Haircut', '2021/01/19'),
       (2, 3, 'Routine Checkup', '2020/10/02'),
       (3, 3, 'Haircut and Grooming', '2019/11/01'),
       (4, 3, 'Routine Checkup', '2021/03/20'),
       (4, 3, 'Teeth Cleaning', '2021/06/10'),
       (4, 3, 'Routine Checkup', '2022/03/20'),
       (5, 3, 'Haircut', '2021/07/04'),
       (5, 3, 'Fur Wash', '2021/10/22'),
       (6, 3, 'Routine Checkup', '2019/07/11'),
       (7, 3, 'Anti Rabies Vaccine', '2022/03/21');