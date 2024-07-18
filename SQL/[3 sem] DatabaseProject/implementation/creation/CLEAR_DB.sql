USE online_shop;

DROP VIEW IF EXISTS CustomerReturns;

-- Delete data from tables with foreign key relationships starting from the child tables
DELETE FROM Returned_items_events;
DELETE FROM Invoice_corrects;
DELETE FROM Deliveries;
DELETE FROM Return_items;
DELETE FROM Returns;
DELETE FROM Magazine_events;
DELETE FROM Delivery_position;
DELETE FROM Magazine_positions;
DELETE FROM Order_items;
DELETE FROM Invoices;
DELETE FROM Product_offers;
DELETE FROM Products;
DELETE FROM Delivery_packages;
DELETE FROM Orders;
DELETE FROM Delivery_services;
DELETE FROM Payments;
DELETE FROM Addresses;
DELETE FROM Customers;

-- Reset identity seed for tables with primary keys
DBCC CHECKIDENT ('Return_items', RESEED, 0);
DBCC CHECKIDENT ('Delivery_position', RESEED, 0);
DBCC CHECKIDENT ('Order_items', RESEED, 0);
DBCC CHECKIDENT ('Payments', RESEED, 0);
DBCC CHECKIDENT ('Orders', RESEED, 0);
DBCC CHECKIDENT ('Delivery_packages', RESEED, 0);
DBCC CHECKIDENT ('Magazine_events', RESEED, 0);
DBCC CHECKIDENT ('Product_offers', RESEED, 0);
DBCC CHECKIDENT ('Magazine_positions', RESEED, 0);
DBCC CHECKIDENT ('Products', RESEED, 0);
DBCC CHECKIDENT ('Addresses', RESEED, 0);
DBCC CHECKIDENT ('Customers', RESEED, 0);
DBCC CHECKIDENT ('Delivery_services', RESEED, 0);