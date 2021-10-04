USE TIMETABLE;
SHOW TABLES;

-- DISPLAY all users
SELECT * FROM User;

-- INSERT new user
INSERT 
INTO USER 
values 
(0, "username", "email", "password", "firstName", "lastName");

-- CHECK username and password if exist
SELECT User_ID, first_name, last_name
from USER
where username = "hazem" and password = "121035";

-- Get count of users
SELECT COUNT(*) FROM USER;
