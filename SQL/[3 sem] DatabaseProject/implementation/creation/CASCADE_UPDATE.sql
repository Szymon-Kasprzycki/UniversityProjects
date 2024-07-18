USE online_shop;
GO

UPDATE Delivery_packages SET Tracking_number = 'ABC123456789' where Tracking_number = 'ABC123';

SELECT * FROM Delivery_packages;
SELECT * FROM Delivery_position;