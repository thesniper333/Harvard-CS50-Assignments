--To see about airports details

SELECT * FROM airports;


--To Check the earliest Flight from fiftyville



SELECT flights.id, flights.origin_airport_id, flights.destination_airport_id, flights.month, flights.day, flights.hour, flights.minute, airports.full_name FROM flights JOIN airports ON flights.origin_airport_id = airports.id WHERE airports.full_name = 'Fiftyville Regional Airport' AND flights.year = 2023 AND month = 7 AND day = 29;


--To see the phone_call for duration less than a minute.


 SELECT * FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration <=60;

 --To seen information about vehicle license plate which left within 10 minutes of theft.

 SELECT * FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

 --To see the account number from atm_transaction details of 'leggett Street' of withdrawal.


SELECT * FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street';

--To see the people details such as id, name, phone_number, passport_number, license_plate

SELECT people.* FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE atm_transactions.year = 2023 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.transaction_type = 'withdraw';

-- Now after matching the license plate phone number as per the incident. Person with Passport No. = 5773159633 was common. So, retrieving the details of the said person.

SELECT * FROM passengers WHERE passport_number = 5773159633;

--To check flight details

SELECT * from flights WHERE id = 36;

--To find the city they have boarded to

SELECT * FROM airports WHERE id = 8;

--to find the city they have escaped to

SELECT * FROM airports WHERE id = 4;

--To see the passengers details

SELECT * FROM passengers WHERE flight_id = 36;

--Now by checking the phone_number, license plate and passport number. They thief was Bruce.

SELECT people.* FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE atm_transactions.year = 2023 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.transaction_type = 'withdraw';

-- Now checking the phone details of the Bruce. His accomplice was Robin.











