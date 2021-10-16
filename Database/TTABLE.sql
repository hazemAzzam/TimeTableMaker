-- DISPLAY all tables
SELECT * FROM TTable;

-- INSERT new table belongs to a user
INSERT INTO TTABLE 
VALUES
(0, 2, "TITLE");

-- DELETE TABLE by an ID
DELETE FROM TTable WHERE ID=3;

-- CHANGE TITLE of a Time table by its ID
UPDATE TTABLE SET TITLE = "PM CS 2ND YEAR" WHERE ID = 1;

-- Get table title from Table_id
SELECT title
from TTable
where tableID = 1;

-- UPDATE title of the table
UPDATE TTable
set title = "title"
where tableID = 1 and userID = 1;

-- Get number of time tables
SELECT count(*)
from ttable 
natural join user
where user_ID = 1;

-- DISPLAY ALL TimeTable's Title of a User ID
SELECT *
FROM USER U
NATURAL JOIN TTABLE T
where user_id = 1; 

-- Delete table by TABLE_ID AND USER_ID
DELETE FROM TTable
WHERE table_id = "0" and user_id = "1";

--
SELECT table_id
from ttable
where user_id = 1
order by table_id desc
limit 1;