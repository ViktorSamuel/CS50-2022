-- STEP 1: Find the crime details for the given date and location
SELECT description
FROM crime_scene_reports
WHERE year = 2021
  AND month = 7
  AND day = 28
  AND street LIKE '%Humphrey Street%';

-- STEP 2: Retrieve the transcripts of interviews mentioning the bakery
SELECT transcript
FROM interviews
WHERE year = 2021
  AND month = 7
  AND day = 28
  AND transcript LIKE '%bakery%';

-- STEP 3: Search for the license plate of the suspect's vehicle
SELECT license_plate
FROM bakery_security_logs
WHERE year = 2021
  AND month = 7
  AND day = 28
  AND activity LIKE '%exit%'
  AND hour = 10
  AND minute > 16
  AND minute < 24;

-- STEP 4: Find the phone numbers related to the suspect
SELECT caller
FROM phone_calls
WHERE year = 2021
  AND month = 7
  AND day = 28
  AND duration < 60;

SELECT receiver
FROM phone_calls
WHERE year = 2021
  AND month = 7
  AND day = 28
  AND duration < 60;

-- STEP 5: Retrieve the person ID based on the bank account information
SELECT person_id
FROM bank_accounts
WHERE account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2021
      AND month = 7
      AND day = 28
      AND transaction_type LIKE '%withdraw%'
      AND atm_location LIKE '%Leggett Street%'
);

-- STEP 6: Find the passport number of the suspect's earliest flight on the following day
SELECT passport_number
FROM passengers
WHERE flight_id IN (
    SELECT id
    FROM flights
    WHERE year = 2021
      AND month = 7
      AND day = 29
      AND origin_airport_id = (
          SELECT id
          FROM airports
          WHERE city LIKE '%Fiftyville%'
      )
    ORDER BY hour
    LIMIT 1
);

-- STEP 7: Retrieve the details of the person matching the criteria (license plate, phone numbers, bank account, and passport)
SELECT id, name, passport_number, phone_number
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2021
          AND month = 7
          AND day = 28
          AND transaction_type LIKE '%withdraw%'
          AND atm_location LIKE '%Leggett Street%'
    )
)
  AND (
    phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE year = 2021
          AND month = 7
          AND day = 28
          AND duration < 60
    )
    OR phone_number IN (
        SELECT receiver
        FROM phone_calls
        WHERE year = 2021
          AND month = 7
          AND day = 28
          AND duration < 60
    )
  )
  AND license_plate IN (
      SELECT license_plate
      FROM bakery_security_logs
      WHERE year = 2021
        AND month = 7
        AND day = 28
        AND activity LIKE '%exit%'
        AND hour = 10
        AND minute > 16
        AND minute < 24
  )
  AND passport_number IN (
      SELECT passport_number
      FROM passengers
      WHERE flight_id IN (
          SELECT id
          FROM flights
          WHERE year = 2021
            AND month = 7
            AND day = 29
            AND origin_airport_id = (
                SELECT id
                FROM airports
                WHERE city LIKE '%Fiftyville%'
            )
          ORDER BY hour
          LIMIT 1
      )
  );

-- STEP 8: Find the city where the suspect escaped to
SELECT city
FROM airports
WHERE id IN (
    SELECT destination_airport_id
    FROM flights
    WHERE year = 2021
      AND month = 7
      AND day = 29
      AND origin_airport_id = (
          SELECT id
          FROM airports
          WHERE city LIKE '%Fiftyville%'
      )
    ORDER BY hour
    LIMIT 1
);

-- STEP 9: Find the details of the suspected accomplice based on the phone number
SELECT id, name, passport_number, phone_number
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2021
      AND month = 7
      AND day = 28
      AND duration < 60
      AND caller LIKE '%(367) 555-5533%'
);
