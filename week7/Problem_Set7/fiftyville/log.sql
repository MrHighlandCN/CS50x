-- Keep a log of any SQL queries you execute as you solve the mystery.
--LOOKING FOR CRIME SCENE REPORT
SELECT
description
FROM
crime_scene_reports
WHERE
month = 7
AND day = 28
AND street = 'Humphrey Street'
/*
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
|                                                                                                       description                                                                                                        |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/
--SEE WHAT WITNESSES SAID
SELECT
transcript
FROM
interviews
WHERE
month = 7
AND
day = 28;

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
|                                                                                                                                                     transcript                                                                                                                                                      |
+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”                                                                                                                               |
| “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”                                                                                                                                                                                      |
| “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.                                                                                                                   |
| Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
| Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.                                                                        |
+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/
-- SELECT NAME WHO WIDTHRAW IN 28 JULY ON LEGGETT STREET
SELECT
name
FROM
people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE
month = 7
AND day = 28
AND atm_location = "Leggett Street"
AND transaction_type = "withdraw"
/*
+---------+
|  name   |
+---------+
| Bruce   |
| Diana   |
| Brooke  |
| Kenny   |
| Iman    |
| Luca    |
| Taylor  |
| Benista |
+---------+
*/
-- SELECT NAME WHO HAVE LICENSE PLATE WAS EXIT FROM 10:15 TO 10:25
SELECT
people.name
FROM
people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE
bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.activity = "exit"
AND bakery_security_logs.minute BETWEEN 15 AND 25;

/*
+---------+
|  name   |
+---------+
| Vanessa |
| Bruce   |
| Barry   |
| Luca    |
| Sofia   |
| Iman    |
| Diana   |
| Kelsey  |
+---------+
*/
-- THOSE WHO ARE SUSPECTED ARE BRUCE, DIANA, IMAN, LUCA,
--SELECT NAME CALL AND RECEIVED CALL LESS THAN A MINUTE IN SUSPECTED PEOPLE
SELECT
people.name,
people.phone_number,
phone_calls.caller,
phone_calls.receiver
FROM
people
JOIN phone_calls ON people.phone_number = phone_calls.caller
OR people.phone_number = phone_calls.receiver
WHERE
phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration <= 60
AND people.name IN ('Bruce', 'Diana', 'Iman', 'Luca');

/*
+-------+----------------+----------------+----------------+
| name  |  phone_number  |     caller     |    receiver    |
+-------+----------------+----------------+----------------+
| Luca  | (389) 555-5198 | (609) 555-5876 | (389) 555-5198 |
| Diana | (770) 555-1861 | (770) 555-1861 | (725) 555-3243 |
| Bruce | (367) 555-5533 | (367) 555-5533 | (375) 555-8161 |
+-------+----------------+----------------+----------------+
*/
/*
- Iman didn't make any call
- Luca was reciever
- So now just have Diana and Bruce were suspected people
*/
-- 2 PEOPLE WHO MAYBE BE ACCOMPLICE
SELECT
name
FROM
people
WHERE
phone_number IN ('(725) 555-3243', '(375) 555-8161');

/*
+--------+
|  name  |
+--------+
| Philip |
| Robin  |
+--------+
*/
-- CHECK IF BRUCE OR DIANA HAVE A FLIGHT OR NOT
SELECT
people.name,
people.passport_number,
passengers.flight_id
FROM
people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE
people.name IN ('Bruce', 'Diana');

/*
+-------+-----------------+-----------+
| name  | passport_number | flight_id |
+-------+-----------------+-----------+
| Diana | 3592750733      | 18        |
| Diana | 3592750733      | 24        |
| Diana | 3592750733      | 54        |
| Bruce | 5773159633      | 36        |
+-------+-----------------+-----------+
*/
--GET INFORMATION BASE ON FLIGHT ID
SELECT
id,
origin_airport_id,
destination_airport_id
FROM
flights
WHERE
id IN (18, 24, 54, 36)
/*
+----+-------------------+------------------------+
| id | origin_airport_id | destination_airport_id |
+----+-------------------+------------------------+
| 18 | 8                 | 6                      |
| 24 | 7                 | 8                      |
| 36 | 8                 | 4                      |
| 54 | 8                 | 5                      |
+----+-------------------+------------------------+
*/
/*
Diana doesn't seem like a thief as she has many flights back and forth to the city of Fiftyville
So I think Bruce was the thief
*/
-- LET SEE WHERE BRUCE FLIGHT TO
SELECT
city
FROM
airports
WHERE
id = 4
/*
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+
*/
--CONCLUSION: BRUCE WAS A THIEF AND HE ESCAPE TO NEW YORK CITY AND HIS ACCOMPICE IS ROBIN
