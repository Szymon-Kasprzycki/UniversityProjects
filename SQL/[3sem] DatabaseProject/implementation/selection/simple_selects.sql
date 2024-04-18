USE online_shop;
GO

-- 1
-- Retrieve top 10 customers by amount spent in the shop
SELECT
	TOP(10)
    --o.CustomerID,
    c.First_name 'Name',
    c.Last_name 'Surname',
	CASE WHEN c.is_company = 1 THEN c.Company_name ELSE '-' END AS 'Company name',
    SUM(oi.Quantity_bought * (po.Price_net*(1+po.Vat_rate))) AS 'Total money spent [$]'
FROM
    Orders o
JOIN
    Order_items oi ON o.Order_id = oi.OrderID
JOIN
    Product_offers po ON oi.OfferID = po.Offer_id
JOIN
    Customers c ON o.CustomerID = c.Customer_id
GROUP BY
    o.CustomerID, c.First_name, c.Last_name, c.is_company, c.Company_name
ORDER BY
    'Total money spent [$]' DESC;


GO
-- 2
-- Find the most used delivery service and the total number of packages sent using it.
SELECT
    ds.Company_name AS 'Delivering company',
    ds.Delivery_type AS 'Type of delivery',
    COUNT(*) AS 'Total packages sent'
FROM
    Delivery_packages dp
JOIN
    Delivery_services ds ON dp.DeliveryServiceID = ds.delivery_service_id
GROUP BY
    ds.Company_name, ds.Delivery_type
ORDER BY
    'Total packages sent' DESC


GO
-- 3
-- Identify delivery positions that handle a higher than average quantity of items and may need to have a look at their optimization
-- Shows positionid in one column and total item quantity in second column
SELECT dp.Delivery_position_id,
       SUM(dp.Quantity_sent) AS 'Total quantity'
FROM Delivery_position dp
GROUP BY dp.Delivery_position_id
HAVING SUM(dp.Quantity_sent) >
	(SELECT AVG(TotalQuantity)
		FROM
			(SELECT Delivery_position_id,
					SUM(Quantity_sent) AS TotalQuantity
				FROM Delivery_position
				GROUP BY Delivery_position_id) AS AvgQuantity);


GO
-- 4.1
-- Prepares the view with all return ids and client that made the return
CREATE VIEW CustomerReturns AS
SELECT DISTINCT
	c.Customer_id,
	r.Rma
FROM
	Customers c
JOIN
	Orders o ON c.Customer_id = o.CustomerID
JOIN
	Order_items oi ON o.Order_id = oi.OrderID
JOIN
	Delivery_position dp ON oi.Order_item_id = dp.orderItemID
JOIN
	Return_items ri ON ri.DeliveryPositionID = dp.Delivery_position_id
JOIN
	Returns r ON ri.ReturnID = r.Rma;

GO
-- 4.2
-- Find Customers with any returns and show amount of their returns (using view from previous batch)
SELECT 
   Customer_id,
   COUNT(DISTINCT Rma) AS 'Returns count'
FROM
    CustomerReturns
GROUP BY
    Customer_id
HAVING
    COUNT(DISTINCT Rma) >= 1;


GO
-- 5
-- Find the number of packages in each delivery status
-- The result is a number of packages for each status
SELECT
    Delivery_status AS 'Package status',
    COUNT(*) AS 'Package count'
FROM
    Delivery_packages
GROUP BY
    Delivery_status;


GO
-- 6
-- Customers who haven't placed any order yet
-- The result is a list of customers with no orders in database (their name, surname, and company name if they have one)
SELECT
    c.Customer_id,
    c.First_name,
	c.Last_name,
	CASE WHEN c.is_company = 1 THEN c.Company_name ELSE '-' END AS 'Company name'
FROM
    Customers c
LEFT JOIN
    Orders o ON c.Customer_id = o.CustomerID
WHERE
    o.CustomerID IS NULL;


GO
-- 7
-- Retrieve each product current stock
-- The result is a table with columns representing (PRODUCT, AMOUNT)
SELECT
    po.ProductID,
    SUM(mp.Actual_quantity) AS 'Stock'
FROM
    Product_offers po
JOIN
    Products p ON p.Product_id = po.ProductID
JOIN
    Magazine_positions mp ON mp.ProductID = p.Product_id
GROUP BY
    po.ProductID;


GO
-- 8
-- Retrieve the Overall Average Value of the order
-- The result is just one cell with average value
SELECT
    AVG(TotalOrderValue) AS 'Overall Average Order Value'
FROM (
    SELECT
        o.Order_id,
        SUM(oi.Quantity_bought * (po.Price_net * (1 + po.Vat_rate))) AS TotalOrderValue
    FROM
        Orders o
    JOIN
        Order_items oi ON o.Order_id = oi.OrderID
    JOIN
        Product_offers po ON oi.OfferID = po.Offer_id
    GROUP BY
        o.Order_id
) AS OrderTotals;
