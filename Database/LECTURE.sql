-- DISPLAY all Lectures
select * from lecture;

-- Insert new Lecture to a table
INSERT INTO Lecture 
VALUES
("lectureID", "tableID", "userID", "day", "name", "startHour","finishHour", "location");

-- Delete lecutre by its ID
DELETE FROM Lecture 
WHERE user_id = "userID" and table_id = "tableID" and Lecture_id = "lectureID";

-- DISPLAY ALL Lecutres of a user from a table
SELECT lecture_id, name, day, location
FROM Lecture
NATURAL JOIN TTABLE
NATURAL JOIN USER
WHERE USER_ID = 5 and table_id = 1;

-- Count of lectures
SELECT COUNT(*)
FROM lecture
NATURAL JOIN ttable
NATURAL JOIN user
WHERE user_id = 3 and table_id = 0;

-- COUNT of lectures in day = ""
SELECT COUNT(*)
FROM Lecture L
NATURAL JOIN TTABLE
NATURAL JOIN USER
WHERE L.day = "SUN" and L.table_id = 2 and user_id = 1;

-- DISPLAY ALL Lecutres of a user from a table in day
SELECT day, name, start_hour, finish_hour, location
FROM Lecture
NATURAL JOIN TTABLE
NATURAL JOIN USER
WHERE 
DAY = "SUN" 
and USER_ID = "userID" 
and table_id = "tableID";

-- get last lecture id
SELECT LECTURE_ID
from Lecture
where user_id = 1 and table_id = 2
order by lecture_id desc
limit 1;

SELECT start_hour
from lecture
where user_id = 1 and table_id = 2 and day = "tue"
order by start_hour;


INSERT INTO Lecture VALUES (2, 4, 1, "SAT", "ِسي", "08:00","11:00", "شسي");