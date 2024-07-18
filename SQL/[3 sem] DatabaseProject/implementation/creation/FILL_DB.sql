USE online_shop;
GO

-- Insert data into Customers table
INSERT INTO Customers (First_name, Last_name, is_company, Company_name, Nip, Email)
VALUES
('John', 'Doe', 0, NULL, NULL, 'john.doe@example.com'),
('Alice', 'Smith', 1, 'ABC Company', '1234567890', 'alice.smith@abc.com'),
('Bob', 'Johnson', 0, NULL, NULL, 'bob.johnson@example.com'),
('Emma', 'White', 1, 'XYZ Corporation', '9876543210', 'emma.white@xyz.com'),
('Charlie', 'Brown', 0, NULL, NULL, 'charlie.brown@example.com'),
('Eva', 'Davis', 1, 'DEF Ltd', '4567890123', 'eva.davis@def.com'),
('Michael', 'Clark', 0, NULL, NULL, 'michael.clark@example.com'),
('Sophia', 'Garcia', 1, 'GHI Inc', '7890123456', 'sophia.garcia@ghi.com'),
('Daniel', 'Miller', 0, NULL, NULL, 'daniel.miller@example.com'),
('Olivia', 'Lopez', 1, 'JKL Enterprises', '2345678901', 'olivia.lopez@jkl.com'),
('Ethan', 'Hill', 0, NULL, NULL, 'ethan.hill@example.com'),
('Mia', 'Wright', 1, 'MNO Co', '3456789012', 'mia.wright@mno.com'),
('Liam', 'Young', 0, NULL, NULL, 'liam.young@example.com'),
('Ava', 'Brown', 1, 'PQR Ltd', '4567890123', 'ava.brown@pqr.com'),
('Noah', 'Lee', 0, NULL, NULL, 'noah.lee@example.com'),
('Isabella', 'Martin', 1, 'STU Corp', '5678901234', 'isabella.martin@stu.com'),
('James', 'Jackson', 0, NULL, NULL, 'james.jackson@example.com'),
('Sophie', 'Harris', 1, 'VWX Ltd', '6789012345', 'sophie.harris@vwx.com'),
('Benjamin', 'Ward', 0, NULL, NULL, 'benjamin.ward@example.com'),
('Emily', 'Young', 1, 'YZA Inc', '7890123456', 'emily.young@yza.com');


-- Insert data into Addresses table
INSERT INTO Addresses (First_line, Second_line, Postal_code, City, Country, Phone_number, is_delivery_addr, is_billing_addr, CustomerConnected)
VALUES
('ul. Wiejska 12', 'Mieszkanie 45', '12345', 'Warszawa', 'Polska', '+48165316789', 1, 1, 1), --1st customer
('ul. Leśna 34', 'Apartament 101', '67890', 'Kraków', 'Polska', '+48186436790', 1, 0, 1),
('ul. Słoneczna 56', 'Mieszkanie 7', '98765', 'Wrocław', 'Polska', '+49123122289', 1, 0, 2), --2nd customer
('ul. Główna 23', 'Pawilon 5', '12345', 'Wrocław', 'Polska', '+49123456791', 0, 1, 2),
('ul. Morska 78', 'Piętro 3', '54321', 'Gdańsk', 'Polska', '+48123456791', 0, 1, 3), --3rd customer
('ul. Brzozowa 90', 'Mieszkanie 12', '87654', 'Poznań', 'Polska', '+33126666789', 1, 1, 4), --4th customer
('ul. Brzozowa 90', 'Mieszkanie 12', '87654', 'Poznań', 'Polska', '+33123477789', 1, 0, 4),
('ul. Klonowa 45', 'Pokój 15', '43210', 'Katowice', 'Polska', '+48120987792', 1, 0, 5), --5th customer
('ul. Klonowa 45', 'Pokój 15', '43210', 'Katowice', 'Polska', '+48223456792', 0, 1, 5),
('ul. Jasna 67', 'Mieszkanie 22', '76543', 'Łódź', 'Polska', '+48123456793', 1, 0, 6), -- 6th customer
('123 Main St', 'Apt 3', '54321', 'New York', 'USA', '+11234567890', 0, 1, 7),-- 7th customer
('ul. Kwiatowa 34', 'Mieszkanie 5', '78901', 'Bydgoszcz', 'Polska', '+48125556794', 1, 0, 8), --8th customer
('45 Rue de la Paix', 'Appartement 8', '56789', 'Paris', 'France', '+33123456789', 0, 1, 8),
('ul. Ogrodowa 56', 'Pokój 11', '34567', 'Gdynia', 'Polska', '+48123456795', 1, 0, 9), --9th customer
('ul. Słowiańska 78', 'Piętro 2', '90123', 'Częstochowa', 'Polska', '+48123999796', 1, 1, 10), --10th customer
('75 Baker Street', 'Flat 22', '23456', 'London', 'UK', '+442071235567', 1, 0, 10),
('ul. Zielona 12', 'Mieszkanie 33', '45678', 'Radom', 'Polska', '+49113456792', 1, 0, 11), --11st customer
('ul. Krótka 90', 'Pokój 7', '89012', 'Toruń', 'Polska', '+33123456790', 0, 1, 12), --12nd customer
('ul. Słupska 45', 'Piętro 1', '23456', 'Sosnowiec', 'Polska', '+48122456797', 1, 0, 13), --13rd customer
('ul. Malczewskiego 67', 'Mieszkanie 15', '78901', 'Kielce', 'Polska', '+48121456998', 1, 0, 14), --14th customer
('ul. Malinowa 34', 'Pokój 19', '56789', 'Gliwice', 'Polska', '+48127456799', 1, 1, 15), --15th customer
('1234 Elm St', 'Apt 10', '98765', 'Los Angeles', 'USA', '+13134507890', 1, 0, 15),
('ul. Wiosenna 23', 'Mieszkanie 8', '23456', 'Szczecin', 'Polska', '+48129456800', 0, 1, 16), --16th customer
('456 Oak St', 'Apt 12', '34567', 'Chicago', 'USA', '+17734567890', 1, 0, 16),
('ul. Leśna 56', 'Pokój 14', '45678', 'Płock', 'Polska', '+48163496801', 1, 0, 17), --17th customer
('ul. Główna 89', 'Mieszkanie 29', '56789', 'Rzeszów', 'Polska', '+48123256802', 1, 0, 18), --18th customer
('ul. Wąska 12', 'Pokój 5', '67890', 'Opole', 'Polska', '+48123456803', 0, 1, 19), --19th customer
('789 Maple St', 'Apt 7', '78901', 'San Francisco', 'USA', '+14154567390', 1, 0, 19),
('ul. Podgórna 45', 'Mieszkanie 18', '89012', 'Zielona Góra', 'Polska', '+48183416804', 1, 1, 20); --20th customer

-- Insert data into Products table
INSERT INTO Products (Short_desc, Long_desc, Last_updated, Phone_brand, Phone_model, Battery_capacity, Memory, Ram, Origin_market, Color)
VALUES
('Samsung Galaxy S21 FE 5G', 'Experience the limitless possibilities with our high-performance smartphone.', '2022-05-15 10:30:00', 'Samsung', 'S21FE', 4000, 128, 6, 'Asia', 'Black'),
('Samsung Galaxy S21 FE', 'Indulge in sophistication with this sleek and stylish powerhouse.', '2022-06-20 11:45:00', 'Samsung', 'S21 FE 5G', 3500, 64, 4, 'Europe', 'Silver'),
('Apple Iphone 15 PRO', 'Reach the peak of affordability and durability with our latest smartphone.', '2022-07-25 12:15:00', 'Apple', '15 PRO', 5000, 256, 3, 'US', 'Black'),
('Apple Iphone 15 PRO MAX', 'Swiftly navigate your day with this compact and lightweight companion.', '2022-08-30 13:20:00', 'Apple', '15 PRO MAX', 4000, 512, 4, 'Asia', 'White'),
('Apple Iphone 15 PRO', 'Embrace the gaming world with a smartphone designed for champions.', '2022-09-05 14:30:00', 'Apple', '15 PRO', 4500, 512, 4, 'Europe', 'Red'),
('Apple Iphone 14 PRO', 'Discover bliss in affordability with essential features at your fingertips.', '2022-10-10 15:45:00', 'Apple', '14 PRO', 4000, 128, 6, 'US', 'Gold'),
('Apple Iphone 13 PRO', 'Fused with supremacy, this flagship smartphone sets a new standard.', '2022-11-15 16:10:00', 'Apple', '13 PRO', 6000, 256, 12, 'Asia', 'Green'),
('Xiaomi Mi 15', 'Unleash your photography skills with an AI-powered camera-centric marvel.', '2022-12-20 17:25:00', 'Xiaomi', 'Mi15', 4200, 128, 8, 'Europe', 'Purple'),
('Google Pixel 5', 'Conquer the outdoors with a rugged and durable smartphone companion.', '2022-01-25 18:40:00', 'Google', 'Pixel 5', 5500, 64, 6, 'US', 'Orange'),
('Samsung Galaxy Z Fold', 'Experience royalty in every detail with an elegant and premium masterpiece.', '2022-02-28 19:55:00', 'Samsung', 'Z FOLD', 3800, 256, 10, 'Asia', 'Silver');

-- Insert data into Procuts_offers table
INSERT INTO Product_offers (Date_started, Date_ended, Price_net, Vat_rate, ProductID)
VALUES
-- Offers for Smartphone A
('2022-01-01 00:00:00', '2022-02-28 23:59:59', 750, 0.23, 1),
('2022-03-01 00:00:00', '2022-04-30 23:59:59', 700, 0.23, 1),
('2022-05-01 00:00:00', '2022-06-30 23:59:59', 720, 0.23, 1),
-- Offers for Smartphone B
('2022-02-01 00:00:00', '2022-03-31 23:59:59', 700, 0.23, 2),
('2022-04-01 00:00:00', '2022-05-31 23:59:59', 680, 0.23, 2),
('2022-06-01 00:00:00', '2022-07-31 23:59:59', 720, 0.23, 2),
-- Offers for Smartphone C
('2022-03-01 00:00:00', '2022-04-30 23:59:59', 900, 0.23, 3),
('2022-05-01 00:00:00', '2022-06-30 23:59:59', 880, 0.23, 3),
('2022-07-01 00:00:00', '2022-08-31 23:59:59', 920, 0.23, 3),
-- Offers for Smartphone D
('2022-04-01 00:00:00', '2022-05-31 23:59:59', 680, 0.23, 4),
('2022-06-01 00:00:00', '2022-07-31 23:59:59', 660, 0.23, 4),
('2022-08-01 00:00:00', '2022-09-30 23:59:59', 700, 0.23, 4),
-- Offers for Smartphone E
('2022-05-01 00:00:00', '2022-06-30 23:59:59', 1000, 0.23, 5),
('2022-07-01 00:00:00', '2022-08-31 23:59:59', 980, 0.23, 5),
('2022-09-01 00:00:00', '2022-10-31 23:59:59', 1020, 0.23, 5),
-- Offers for Smartphone F
('2022-06-01 00:00:00', '2022-07-31 23:59:59', 600, 0.23, 6),
('2022-08-01 00:00:00', '2022-09-30 23:59:59', 580, 0.23, 6),
('2022-10-01 00:00:00', '2022-11-30 23:59:59', 620, 0.23, 6),
-- Offers for Smartphone G
('2022-07-01 00:00:00', '2022-08-31 23:59:59', 1200, 0.23, 7),
('2022-09-01 00:00:00', '2022-10-31 23:59:59', 1180, 0.23, 7),
('2022-11-01 00:00:00', '2022-12-31 23:59:59', 1220, 0.23, 7),
-- Offers for Smartphone H
('2022-08-01 00:00:00', '2022-09-30 23:59:59', 850, 0.23, 8),
('2022-10-01 00:00:00', '2022-11-30 23:59:59', 830, 0.23, 8),
('2022-12-01 00:00:00', '2023-01-31 23:59:59', 870, 0.23, 8),
-- Offers for Smartphone I
('2022-09-01 00:00:00', '2022-10-31 23:59:59', 950, 0.23, 9),
('2022-11-01 00:00:00', '2022-12-31 23:59:59', 930, 0.23, 9),
('2023-01-01 00:00:00', '2023-02-28 23:59:59', 970, 0.23, 9),
-- Offers for Smartphone J
('2022-10-01 00:00:00', '2022-11-30 23:59:59', 1100, 0.23, 10),
('2022-12-01 00:00:00', '2023-01-31 23:59:59', 1080, 0.23, 10),
('2023-02-01 00:00:00', '2023-03-31 23:59:59', 1120, 0.23, 10);


-- Insert data into Magazine_positions table
INSERT INTO Magazine_positions (Capacity, Buy_price, Actual_quantity, Buy_tax_rate, ProductID)
VALUES
-- Smartphone A
(100, 500, 50, 0.23, 1),
(150, 520, 80, 0.23, 1),
(200, 480, 120, 0.23, 1),
-- Smartphone B
(120, 450, 60, 0.23, 2),
(180, 430, 90, 0.23, 2),
(240, 470, 130, 0.23, 2),
-- Smartphone C
(80, 700, 30, 0.23, 3),
(120, 680, 50, 0.23, 3),
(160, 720, 70, 0.23, 3),
-- Smartphone D
(130, 420, 70, 0.23, 4),
(190, 400, 100, 0.23, 4),
(250, 440, 140, 0.23, 4),
-- Smartphone E
(90, 900, 40, 0.23, 5),
(130, 880, 60, 0.23, 5),
(170, 920, 80, 0.23, 5),
-- Smartphone F
(110, 380, 50, 0.23, 6),
(160, 360, 80, 0.23, 6),
(210, 400, 110, 0.23, 6),
-- Smartphone G
(70, 1100, 20, 0.23, 7),
(100, 1080, 40, 0.23, 7),
(130, 1120, 60, 0.23, 7),
-- Smartphone H
(80, 800, 30, 0.23, 8),
(120, 780, 50, 0.23, 8),
(160, 820, 70, 0.23, 8),
-- Smartphone I
(100, 950, 40, 0.23, 9),
(140, 930, 60, 0.23, 9),
(180, 970, 80, 0.23, 9),
-- Smartphone J
(120, 1100, 50, 0.23, 10),
(170, 1080, 80, 0.23, 10),
(220, 1120, 110, 0.23, 10);


-- Insert into Delivery_services table
INSERT INTO Delivery_services (Company_name, Internal_cost, Delivery_type, Delivery_time)
VALUES
('DPD', 5.00, 'courier', 2),
('DHL', 6.50, 'courier', 2),
('FedEx', 7.00, 'courier', 1),
('InPost', 6.00, 'courier', 1),
('InPost', 4.00, 'parcel_machine', 1),
('Pocztex', 4.50, 'parcel_machine', 2),
('Pocztex', 6.00, 'courier', 2),
('UPS', 6.50, 'courier', 2),
('GLS', 5.50, 'courier', 2);


-- Inserting into Payments table
INSERT INTO Payments (Payment_method, Payment_type, Date_confirmed)
VALUES
('bank transfer', 'incoming', '2022-01-05 10:30:00'),
('credit card', 'incoming', '2022-02-10 14:45:00'),
('BLIK', 'incoming', '2022-03-15 08:00:00'),
('cash', 'incoming', '2022-04-20 16:20:00'),
('fast bank transfer', 'incoming', '2022-05-25 11:10:00'),
('bank transfer', 'incoming', '2022-07-01 09:45:00'),
('credit card', 'incoming', '2022-08-07 17:30:00'),
('BLIK', 'incoming', '2022-09-15 12:15:00'),
('cash', 'incoming', '2022-10-20 13:50:00'),
('fast bank transfer', 'incoming', '2022-11-25 14:30:00'),
('bank transfer', 'incoming', '2022-12-30 08:40:00'),
('credit card', 'incoming', '2023-01-05 09:00:00'),
('BLIK', 'incoming', '2023-01-10 15:30:00');


-- Insert into Orders table
INSERT INTO Orders (Created_on, Return_reported, CustomerID, DeliveryService, DeliveryAddressID, PaymentID)
VALUES
('2022-01-01 10:00:00', 1, 1, 1, 1, 1),
('2022-02-05 12:30:00', 1, 2, 3, 2, 2),
('2022-03-10 15:45:00', 0, 3, 2, 3, 3),
('2022-04-15 08:20:00', 1, 4, 4, 4, 4),
('2022-05-20 14:00:00', 0, 5, 1, 5, 5),
('2022-06-25 11:30:00', 1, 6, 2, 6, 6),
('2022-07-30 09:15:00', 0, 7, 3, 7, NULL),
('2022-08-05 16:45:00', 1, 8, 4, 8, 8),
('2022-09-10 13:00:00', 0, 9, 1, 9, 9),
('2022-10-15 07:30:00', 1, 10, 2, 10, 10),
('2022-11-20 12:15:00', 0, 11, 3, 11, 11),
('2022-12-25 18:00:00', 1, 12, 4, 12, 12),
('2023-01-01 10:00:00', 0, 13, 1, 13, 13);


-- Inserting Invoices for Orders
INSERT INTO Invoices (Document_number, Date_issued, Issued_by, is_correction, file_location)
VALUES
('FV/01/2022/000001', '2022-01-05 14:32:12', 'Jan Nowak', 0, '/path/to/file1.pdf'),
('FV/02/2022/000001', '2022-02-10 15:11:37', 'John Lee', 0, '/path/to/file2.pdf'),
('FV/03/2022/000001', '2022-03-15 10:10:03', 'John Lee', 0, '/path/to/file3.pdf'),
('FV/04/2022/000001', '2022-04-21 08:27:10', 'David Miller', 0, '/path/to/file4.pdf'),
('FV/05/2022/000001', '2022-05-25 13:54:19', 'Jan Nowak', 0, '/path/to/file5.pdf'),
('FV/07/2022/000001', '2022-07-01 13:22:45', 'David Miller', 0, '/path/to/file6.pdf'),
('FV/08/2022/000001', '2022-08-08 09:30:03', 'David Miller', 0, '/path/to/file7.pdf'),
('FV/09/2022/000001', '2022-09-15 14:12:11', 'Sophia Wilson', 0, '/path/to/file8.pdf'),
('FV/10/2022/000001', '2022-10-20 15:42:32', 'Daniel Turner', 0, '/path/to/file9.pdf'),
('FV/11/2022/000001', '2022-11-25 15:32:18', 'Sophia Wilson', 0, '/path/to/file10.pdf'),
('FV/12/2022/000001', '2022-12-30 09:01:41', 'Matthew Harris', 0, '/path/to/file11.pdf'),
('FV/01/2023/000001', '2023-01-05 12:38:04', 'Sophia Wilson', 0, '/path/to/file12.pdf'),
('FV/01/2023/000002', '2023-01-11 14:53:10', 'Jackson Martinez', 0, '/path/to/file13.pdf'),
('FC/01/2022/000001', '2022-03-27 15:11:44', 'Jan Nowak', 1, '/path/to/FC_RMA003.pdf'),
('FC/08/2022/000001', '2022-04-19 14:12:07', 'Jan Nowak', 1, '/path/to/FC_RMA007.pdf');


-- Insert into Order_items table
INSERT INTO Order_items (Quantity_bought, OrderID, OfferID, InvoiceID)
VALUES
(2, 1, 1, 'FV/01/2022/000001'),
(1, 1, 2, 'FV/01/2022/000001'),
(3, 2, 3, 'FV/02/2022/000001'),
(4, 3, 4, 'FV/03/2022/000001'),
(2, 4, 5, 'FV/04/2022/000001'),
(1, 5, 6, 'FV/05/2022/000001'),
(3, 6, 7, 'FV/07/2022/000001'),
(5, 7, 8, 'FV/08/2022/000001'),
(2, 8, 9, 'FV/09/2022/000001'),
(4, 9, 10, 'FV/10/2022/000001'),
(1, 10, 11, 'FV/11/2022/000001'),
(3, 11, 12, 'FV/12/2022/000001'),
(2, 12, 13, 'FV/01/2023/000001'),
(4, 13, 14, 'FV/01/2023/000002');


-- Insert data into Delivery_packages table
INSERT INTO Delivery_packages (Delivery_status, Is_return, Tracking_number, DeliveryServiceID)
VALUES
    ('created_shipping_document', 0, 'ABC123', 1),
    ('packed', 0, 'DEF456', 2),
    ('handed_over_to_the_delivery', 1, 'GHI789', 3),
    ('delivered', 0, 'JKL012', 4),
    ('created_shipping_document', 0, 'MNO345', 5),
    ('packed', 1, 'PQR678', 6),
    ('handed_over_to_the_delivery', 0, 'STU901', 7),
    ('delivered', 0, 'VWX234', 8),
    ('packed', 0, 'YZA567', 9),
    ('packed', 0, 'BCD890', 1),
    ('delivered', 1, 'EFG123', 2),
    ('delivered', 0, 'HIJ456', 3),
    ('created_shipping_document', 0, 'KLM789', 4),
    ('packed', 1, 'NOP012', 5),
    ('handed_over_to_the_delivery', 0, 'QRS345', 6),
    ('delivered', 0, 'TUV678', 7),
    ('created_shipping_document', 0, 'WXY901', 8),
    ('packed', 0, 'ZAB234', 9),
    ('delivered', 1, 'CDE567', 1),
    ('delivered', 0, 'FGH890', 2);

-- Insert data into Delivery_position table with split deliveries
INSERT INTO Delivery_position (Quantity_sent, packageID, orderItemID, trackingNumberID)
VALUES
(1, 1, 1, 'ABC123'),
(1, 1, 1, 'ABC123'),
(1, 2, 2, 'DEF456'),
(3, 3, 3, 'GHI789'),
(2, 4, 4, 'JKL012'),
(2, 4, 4, 'JKL012'),
(2, 5, 5, 'MNO345'),
(1, 6, 6, 'PQR678'),
(2, 7, 7, 'STU901'),
(1, 7, 7, 'STU901'),
(2, 8, 8, 'VWX234'),
(3, 8, 8, 'VWX234'),
(2, 9, 9, 'YZA567'), 
(1, 10, 10, 'BCD890'),
(2, 10, 10, 'BCD890'),
(1, 11, 10, 'EFG123'),
(1, 12, 11, 'HIJ456'),
(2, 13, 12, 'KLM789'),
(1, 13, 12, 'KLM789'),
(2, 14, 13, 'NOP012'),
(2, 15, 14, 'QRS345'),
(1, 16, 14, 'TUV678'),
(1, 16, 14, 'TUV678');


-- Insert data into Returns table
INSERT INTO Returns (Rma, Created_on, Return_reason, Return_status)
VALUES
('RMA001', '2022-03-15 10:00:00', 'Defective product', 'return_submitted'),
('RMA002', '2022-03-20 14:30:00', 'Changed mind', 'return_received'),
('RMA003', '2022-03-25 08:45:00', 'Damaged during delivery', 'return_accepted'),
('RMA004', '2022-04-01 11:20:00', 'Not as described', 'return_rejected'),
('RMA005', '2022-04-05 15:00:00', 'Defective product', 'return_submitted'),
('RMA006', '2022-04-10 09:15:00', 'Changed mind', 'return_received'),
('RMA007', '2022-04-15 17:30:00', 'Damaged during delivery', 'return_accepted'),
('RMA008', '2022-04-20 12:00:00', 'Not as described', 'return_rejected'),
('RMA009', '2022-04-25 14:45:00', 'Defective product', 'return_submitted'),
('RMA010', '2022-05-01 08:30:00', 'Changed mind', 'return_received'),
('RMA011', '2022-06-15 12:30:00', 'Damaged during delivery', 'return_accepted'),
('RMA012', '2022-06-20 16:00:00', 'Not as described', 'return_rejected');


-- Insert data into Return_items table
INSERT INTO Return_items (Quantity_returned, ReturnID, DeliveryPositionID)
VALUES
(1, 'RMA001', 1), -- 3
(1, 'RMA002', 2), -- 3
(1, 'RMA003', 3),
(1, 'RMA004', 5),
(2, 'RMA005', 7),
(1, 'RMA006', 9),
(1, 'RMA007', 11),
(2, 'RMA008', 13)

-- Insert data into Magazine_events table
INSERT INTO Magazine_events (Entry_date, Is_add, Quantity, Comment, MagazinePositionID, DeliveryPositionID)
VALUES
('2022-01-05 12:30:52', 0, 1, 'Packing delivery for order 1', 1, 1),
('2022-01-05 12:32:33', 0, 1, 'Packing delivery for order 1', 2, 2),
('2022-01-05 12:37:02', 0, 1, 'Packing delivery for order 1', 3, 3),
('2022-02-10 13:10:37', 0, 3, 'Packing delivery for order 2', 2, 4),
('2022-03-15 08:21:05', 0, 2, 'Packing delivery for order 3', 5, 5),
('2022-03-15 08:45:19', 0, 2, 'Packing delivery for order 3', 4, 6),
('2022-04-21 08:05:11', 0, 2, 'Packing delivery for order 4', 6, 7),
('2022-05-25 12:14:28', 0, 1, 'Packing delivery for order 5', 6, 8),
('2022-07-01 10:01:43', 0, 2, 'Packing delivery for order 6', 7, 9),
('2022-07-01 10:08:12', 0, 1, 'Packing delivery for order 6', 8, 10),
('2022-08-08 09:30:03', 0, 2, 'Packing delivery for order 7', 7, 11),
('2022-08-08 09:54:09', 0, 3, 'Packing delivery for order 7', 9, 12),
('2022-09-15 12:33:49', 0, 2, 'Packing delivery for order 8', 8, 13),
('2022-10-20 13:33:33', 0, 1, 'Packing delivery for order 9', 10, 14),
('2022-10-20 13:55:01', 0, 2, 'Packing delivery for order 9', 11, 15),
('2022-11-24 14:55:07', 0, 1, 'Packing delivery for order 10', 12, 16),
('2022-11-25 13:17:10', 0, 1, 'Packing delivery for order 10', 11, 17),
('2022-12-29 11:11:47', 0, 2, 'Packing delivery for order 11', 11, 18),
('2022-12-30 08:48:17', 0, 1, 'Packing delivery for order 11', 10, 19),
('2023-01-05 10:08:29', 0, 2, 'Packing delivery for order 12', 15, 20),
('2023-01-11 10:05:21', 0, 2, 'Packing delivery for order 13', 13, 21),
('2023-01-11 10:17:44', 0, 1, 'Packing delivery for order 13', 14, 22),
('2023-01-11 11:03:12', 0, 1, 'Packing delivery for order 13', 15, 23),
('2022-03-22 14:31:32', 1, 1, 'RMA002', 3, 3),
('2022-03-27 12:11:44', 1, 1, 'RMA003', 3, 3),
('2022-04-04 12:27:01', 1, 1, 'RMA004', 5, 5),
('2022-04-15 09:10:10', 1, 1, 'RMA006', 7, 9),
('2022-04-19 08:12:07', 1, 1, 'RMA007', 7, 11);

-- Insert data into Returned items events table
INSERT INTO Returned_items_events(Rma, MagazineEventID)
VALUES
('RMA002', 24),
('RMA003', 25),
('RMA004', 26),
('RMA006', 27),
('RMA007', 28);

-- Insert data into Deliveries table
INSERT INTO Deliveries (OrderID, PackageID)
VALUES
(1, 1),
(1, 2),
(2, 3),
(3, 4),
(4, 5),
(5, 6),
(6, 7),
(7, 8),
(8, 9),
(9, 10),
(9, 11),
(10, 12),
(11, 13),
(12, 14),
(13, 15),
(13, 16);


-- Insert data into Invoice corrects table
INSERT INTO Invoice_corrects(InvoiceID, ReturnID)
VALUES
('FC/01/2022/000001', 'RMA003'),
('FC/08/2022/000001', 'RMA007');