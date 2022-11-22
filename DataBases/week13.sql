-- I

-- exercise 1. a, b
-- exercise 2. e
-- exercise 3. a

--II

GO
CREATE TABLE Drone_manufacturer(
    dm_name VARCHAR(100) PRIMARY KEY
)

CREATE TABLE Drone_Model(
    drone_name VARCHAR(100) UNIQUE,
	battery INT,
	speed INT,
	manufacturer VARCHAR(100) REFERENCES Drone_manufacturer(dm_name)
)

CREATE TABLE Drone(
    serialNr INT PRIMARY KEY,
    model VARCHAR(100) REFERENCES Drone_Model(drone_name)
)

CREATE TABLE PizzaShop(
    shopName VARCHAR(100) UNIQUE,
    shopAddress VARCHAR(100)
)

CREATE TABLE Customer(
    customerName VARCHAR(100) UNIQUE,
    loyaltyScore INT
 )

CREATE TABLE Delivery(
	cName VARCHAR(100) REFERENCES Customer(customerName),
	sName VARCHAR(100) REFERENCES PizzaShop(shopName),
	drone_sn INT REFERENCES Drone(serialNr),
	order_date DATE,
	order_time TIME
)

GO
CREATE OR ALTER PROC insertDelivery( @CName VARCHAR(100), @SName VARCHAR(100), @serialNr INT, @day DATE, @time TIME) As
	INSERT INTO Delivery VALUES (@CName, @SName, @serialNr, @day, @time)


