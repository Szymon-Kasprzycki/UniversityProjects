USE master;
GO

-- Drop the database if it exists
IF NOT EXISTS (SELECT name FROM master.dbo.sysdatabases WHERE name = 'online_shop')
	CREATE DATABASE online_shop;
ELSE 
	USE online_shop;

-- Drop the view to allow dropping tables
DROP VIEW IF EXISTS CustomerReturns;

-- Drop tables in the correct order to avoid foreign key constraints
DROP TABLE IF EXISTS Returned_items_events,
                     Invoice_corrects,
                     Deliveries,
                     Return_items,
                     Returns,
                     Magazine_events,
                     Delivery_position,
                     Magazine_positions,
                     Order_items,
                     Invoices,
                     Product_offers,
                     Products,
                     Delivery_packages,
                     Orders,
                     Delivery_services,
                     Payments,
                     Addresses,
                     Customers;


-- Use the database
USE online_shop;
GO

-- Create Tables
CREATE TABLE Customers (
    Customer_id INT 
		IDENTITY(1,1) 
		PRIMARY KEY,
    First_name VARCHAR(32),
    Last_name VARCHAR(48),
    is_company BIT 
		NOT NULL,
    Company_name VARCHAR(200),
    Nip VARCHAR(10) 
		CONSTRAINT CHK_NipIsDigits 
			CHECK (Nip IS NULL OR (ISNUMERIC(Nip) = 1)),
    Email VARCHAR(72) 
		NOT NULL 
		CONSTRAINT CHK_CustomerEmail 
			CHECK (Email LIKE '%@%') -- check email format
);
	
CREATE TABLE Addresses (
    Address_id INT IDENTITY(1,1) 
		PRIMARY KEY,
    First_line VARCHAR(250) 
		NOT NULL,
    Second_line VARCHAR(250),
    Postal_code VARCHAR(6) 
		NOT NULL,
    City VARCHAR(100) 
		NOT NULL,
    Country VARCHAR(100) 
		NOT NULL,
    Phone_number VARCHAR(16) 
		CONSTRAINT CHK_PhoneNumber_Format 
			CHECK (Phone_number LIKE '+%'), -- Check for phone number country code
    is_delivery_addr BIT 
		NOT NULL,
    is_billing_addr BIT 
		NOT NULL,
    CustomerConnected INT
		REFERENCES Customers(Customer_id) 
		ON UPDATE CASCADE 
		ON DELETE CASCADE
		NOT NULL,
	CONSTRAINT CHK_PostalCode_Format 
		CHECK (ISNUMERIC(Postal_code) = 1), -- Check if all characters are digits
	CONSTRAINT CHK_PostalCode_Length 
		CHECK (LEN(Postal_code) = 5) -- Check for 6-digit postal code
);

CREATE TABLE Payments (
    Payment_id INT 
		IDENTITY(1,1) 
		PRIMARY KEY,
    Payment_method VARCHAR(32),
    Payment_type VARCHAR(8)
		CONSTRAINT CHK_PaymentType 
			CHECK (Payment_type IN ('incoming', 'outgoing')),
    Date_confirmed DATETIME,
	CONSTRAINT CHK_PaymentMethod
		CHECK (Payment_method IN ('bank transfer', 'BLIK', 'credit card', 'cash', 'fast bank transfer'))
);

CREATE TABLE Delivery_services (
    Delivery_service_id INT 
		IDENTITY(1,1) 
		PRIMARY KEY,
    Company_name VARCHAR(100) 
		NOT NULL,
    Internal_cost DECIMAL(10, 2) 
		NOT NULL 
		CONSTRAINT CHK_InternalCost 
			CHECK (Internal_cost >= 0), -- Non-negative internal cost
    Delivery_type VARCHAR(20) 
		NOT NULL 
		CONSTRAINT CHK_DeliveryType 
			CHECK (Delivery_type IN ('courier', 'parcel_machine')),
    Delivery_time INT 
		CONSTRAINT CHK_DeliveryTime 
			CHECK (Delivery_time > 0) -- Positive delivery time
);

CREATE TABLE Orders (
    Order_id INT 
		IDENTITY(1,1) 
		PRIMARY KEY,
    Created_on DATETIME 
		NOT NULL,
    Return_reported BIT 
		NOT NULL,
    CustomerID INT 
		REFERENCES Customers(Customer_id)
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
    DeliveryService INT 
		REFERENCES Delivery_services(Delivery_service_id)
		NOT NULL,
    DeliveryAddressID INT 
		REFERENCES Addresses(Address_id)
		NOT NULL,
    PaymentID INT 
		REFERENCES Payments(Payment_id) 
		ON UPDATE CASCADE
		ON DELETE CASCADE
);

CREATE TABLE Delivery_packages (
    Package_id INT 
		IDENTITY(1,1) 
		PRIMARY KEY,
    Delivery_status VARCHAR(30),
    Is_return BIT 
		NOT NULL,
    Tracking_number VARCHAR(50) 
		UNIQUE
		NOT NULL,
    DeliveryServiceID INT 
		REFERENCES Delivery_services(Delivery_service_id) 
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
	CONSTRAINT CHK_DeliveryStatus 
		CHECK (Delivery_status IN ('created_shipping_document', 'packed', 'handed_over_to_the_delivery', 'delivered')) -- Check for valid delivery status,
);

CREATE TABLE Products (
    Product_id INT 
		IDENTITY(1,1) 
		PRIMARY KEY,
    Short_desc VARCHAR(1000),
    Long_desc VARCHAR(8000),
    Last_updated DATETIME 
		NOT NULL,
    Phone_brand VARCHAR(100) 
		NOT NULL,
    Phone_model VARCHAR(100) 
		NOT NULL,
    Battery_capacity INT 
		CONSTRAINT CHK_BatteryCapacity 
			CHECK (Battery_capacity > 0), -- non-negative battery capacity
    Memory INT 
		CONSTRAINT CHK_Memory 
			CHECK (Memory >= 0), -- non-negative memory
    Ram FLOAT 
		CONSTRAINT CHK_Ram 
			CHECK (Ram > 0), -- positive ram memory amount
    Origin_market VARCHAR(50),
    Color VARCHAR(50) 
		NOT NULL
);
	 
CREATE TABLE Product_offers (
    Offer_id INT 
		IDENTITY(1,1) 
		PRIMARY KEY,
    Date_started DATETIME 
		NOT NULL,
    Date_ended DATETIME 
		NOT NULL,
    Price_net DECIMAL(10, 2) 
		NOT NULL 
		CONSTRAINT CHK_PriceNet 
			CHECK (Price_net >= 0),
    Vat_rate DECIMAL(5, 2) 
		NOT NULL 
		CONSTRAINT CHK_VatRate 
			CHECK (Vat_rate >= 0),
    ProductID INT 
		REFERENCES Products(Product_id) 
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
	CONSTRAINT CHK_TimeValid 
		CHECK (Date_ended > Date_started)
);

CREATE TABLE Invoices (
    Document_number VARCHAR(20)
		PRIMARY KEY,
    Date_issued DATETIME 
		NOT NULL,
    Issued_by VARCHAR(100) 
		NOT NULL,
    is_correction BIT 
		NOT NULL,
    file_location VARCHAR(200)
);

CREATE TABLE Order_items (
    Order_item_id BIGINT 
		IDENTITY(1,1)
		PRIMARY KEY,
    Quantity_bought INT 
		NOT NULL 
		CONSTRAINT CHK_QuantityBought 
			CHECK (Quantity_bought > 0), -- positive quantity bought
    OrderID INT
		REFERENCES Orders(Order_id) 
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
    OfferID INT 
		REFERENCES Product_offers(Offer_id) 
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
    InvoiceID VARCHAR(20) 
		REFERENCES Invoices(Document_number)
);

CREATE TABLE Magazine_positions (
    Position_id INT 
		IDENTITY(1,1) 
		PRIMARY KEY,
    Capacity INT 
		CONSTRAINT CHK_Capacity 
			CHECK (Capacity > 0),
    Buy_price DECIMAL(10, 2) 
		NOT NULL 
		CONSTRAINT CHK_BuyPrice 
			CHECK (Buy_price >= 0),
    Actual_quantity INT 
		NOT NULL 
		CONSTRAINT CHK_ActualQuantity 
			CHECK (Actual_quantity >= 0),
    Buy_tax_rate DECIMAL(5, 2) 
		NOT NULL CONSTRAINT CHK_BuyTaxRate 
			CHECK (Buy_tax_rate >= 0),
    ProductID INT 
		REFERENCES Products(Product_id) 
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL
);

CREATE TABLE Delivery_position (
    Delivery_position_id INT 
		IDENTITY(1,1) 
		PRIMARY KEY,
    Quantity_sent INT
		NOT NULL 
		CONSTRAINT CHK_QuantitySent 
			CHECK (Quantity_sent > 0), -- positive quantity sent
    packageID INT 
		REFERENCES Delivery_packages(Package_id)
		ON UPDATE NO ACTION
		ON DELETE CASCADE,
    orderItemID BIGINT 
		REFERENCES Order_items(Order_item_id) 
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
	trackingNumberID VARCHAR(50) -- ADDED JUST TO SHOW CASCADE UPDATE EXAMPLE (NOT ON ERD!!!)
		REFERENCES Delivery_packages(Tracking_number) -- ADDED JUST TO SHOW CASCADE UPDATE EXAMPLE (NOT ON ERD!!!)
		ON UPDATE CASCADE
		ON DELETE NO ACTION
);

CREATE TABLE Magazine_events (
    Event_id INT 
		IDENTITY(1,1)
		PRIMARY KEY,
    Entry_date DATETIME
		NOT NULL,
    Is_add BIT
		NOT NULL,
    Quantity INT
		NOT NULL
		CONSTRAINT CHK_QuantityPositive
			CHECK (Quantity > 0),
    Comment VARCHAR(1000),
    MagazinePositionID INT
		REFERENCES Magazine_positions(Position_id)
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
    DeliveryPositionID INT
		REFERENCES Delivery_position(Delivery_position_id)
		ON UPDATE NO ACTION
		ON DELETE NO ACTION
);

CREATE TABLE Returns (
    Rma VARCHAR(20) 
		PRIMARY KEY,
    Created_on DATETIME
		NOT NULL,
    Return_reason VARCHAR(500)
		NOT NULL,
    Return_status VARCHAR(20)
		CONSTRAINT CHK_ReturnStatus
			CHECK (Return_status IN ('return_submitted', 'return_received', 'return_accepted', 'return_rejected')),
);

CREATE TABLE Return_items (
    Item_id INT 
		IDENTITY(1,1)
		PRIMARY KEY,
    Quantity_returned INT
		NOT NULL
		CONSTRAINT CHK_QuantityReturned
			CHECK (Quantity_returned > 0),
    ReturnID VARCHAR(20)
		REFERENCES Returns(Rma)
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
    DeliveryPositionID INT
		REFERENCES Delivery_position(Delivery_position_id)
		ON UPDATE CASCADE
		ON DELETE CASCADE
);

CREATE TABLE Deliveries (
    OrderID INT
		REFERENCES Orders(Order_id)
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
    PackageID INT
		REFERENCES Delivery_packages(Package_id)
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
    PRIMARY KEY (OrderID, PackageID),
	CONSTRAINT CHK_Delivery
		UNIQUE (OrderID, PackageID) -- Unique combination of OrderID and PackageID
);

CREATE TABLE Invoice_corrects (
    InvoiceID VARCHAR(20)
		REFERENCES Invoices(Document_number)
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
    ReturnID VARCHAR(20)
		REFERENCES Returns(Rma)
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
    PRIMARY KEY (InvoiceID, ReturnID),
	CONSTRAINT CHK_Corrects 
		UNIQUE (InvoiceID, ReturnID) -- Unique combination of InvoiceID and ReturnID
);

CREATE TABLE Returned_items_events (
    Rma VARCHAR(20)
		REFERENCES Returns(Rma)
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
    MagazineEventID INT
		REFERENCES Magazine_events(Event_id)
		ON UPDATE CASCADE
		ON DELETE CASCADE
		NOT NULL,
    PRIMARY KEY (Rma, MagazineEventID),
	CONSTRAINT CHK_RmaEvent 
		UNIQUE (Rma, MagazineEventID) -- Unique combination of Rma and MagazineEventID
);
