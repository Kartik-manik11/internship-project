# Test Cases and Verification Plan

Run tests from the project root. The included `data/students.txt` contains two sample records; use IDs such as `3001` and `3002` below to avoid them. To test an empty or missing file, temporarily run a copied executable from a fresh directory containing an empty `data/` folder.

## Functional test cases

| ID | Scenario and input | Expected result |
| --- | --- | --- |
| TC-01 | Choose **Add Student** and enter `3001`, `Ishaan Verma`, `BCA`, `2`, `ishaan@example.com`, `84.5`. | `Student added successfully.` appears and the record is visible in Display Students. |
| TC-02 | Add another student with ID `3001`. | A duplicate-ID message appears; no existing record changes and no duplicate is added. |
| TC-03 | During Add Student, submit an empty name, then enter a valid name. | An invalid-name validation message appears; the form continues without committing a partial record. |
| TC-04 | During Add Student, enter `120` for marks, then enter a value in range. | An invalid-marks validation message appears; only the in-range value is accepted. |
| TC-05 | Search by Student ID for `3001`. | The complete matching record is displayed. |
| TC-06 | Search by Student ID for an unused valid ID, such as `9999`. | `Student not found.` appears. |
| TC-07 | Update ID `3001` with valid replacement details, for example marks `90`. | Current details display first; after all fields are valid, `Student updated successfully.` appears and Display/Search shows the new values. |
| TC-08 | Delete ID `3001`, answer `Y` to confirmation. Repeat with another record and answer `N`. | The confirmed record is removed. The `N` case prints `Deletion cancelled.` and keeps the record. |
| TC-09 | Add records with names out of alphabetical order, choose Sort Students → Sort by Name, then display. | Records are ordered alphabetically by name (case-insensitive; same names fall back to ID). |
| TC-10 | Add or update a record, choose Save Data, exit, start the program again, and search for that ID. | The record, including its modified value, is restored from `data/students.txt`. |
| TC-11 | Start with no `students.txt` or an empty `data/` directory and choose Display Students. | Startup does not crash and display prints `No student records available.` |
| TC-12 | At the main menu, enter `99`, then a nonnumeric value such as `abc`. | Each input prints an invalid-menu message and returns to the main menu. |

## Boundary and invalid-input tests

| Field | Input | Expected result |
| --- | --- | --- |
| Student ID | Empty input, `0`, `-1`, `abc` | Reject and request a positive numeric ID. |
| Student ID | Existing ID | Reject as a duplicate before other fields are committed. |
| Name | Empty string, `123`, 101-character value | Reject. Spaces inside an otherwise valid name are accepted. |
| Course | Empty string or a value containing `|` | Reject. |
| Semester | `0` | Reject. |
| Semester | `1` | Accept. |
| Semester | `8` | Accept. |
| Semester | `9`, `-1`, `two` | Reject. |
| Email | Empty string, `name`, `name@domain`, `@domain.com`, `name@domain.` | Reject. |
| Marks | `-1` | Reject. |
| Marks | `0` | Accept. |
| Marks | `100` | Accept. |
| Marks | `101`, `abc`, `nan` | Reject. |
| Deletion confirmation | Any value other than `Y` or `N` | Reject confirmation and ask again. |

## Update integrity check

1. Search an existing record and note every current value.
2. Choose Update Student for that ID.
3. Enter invalid replacement data, such as semester `9`, and then close input or cancel the operation.
4. Search the record again.

Expected result: the original record is unchanged because the program creates a replacement `Student` only after every input is valid and then assigns it in one step.

## Malformed-file test

1. Save a known valid file first.
2. Add one or more invalid lines manually, such as `not|enough|fields` or `3001|Bad Semester|BCA|9|bad@example.com|50`.
3. Restart the program.

Expected result: valid lines load, invalid lines are ignored, the number ignored is reported, and the application remains usable. A duplicate ID in the file is also ignored to preserve uniqueness.

## Required integration workflow

1. Start the application and confirm the data file loads.
2. Add a student with an unused ID.
3. Search for that ID and verify all details.
4. Update the student's marks with a valid value.
5. Sort the records by a selected field.
6. Choose Save Data and confirm `Data saved successfully.`
7. Exit, then restart the application from the same project root.
8. Search for the same ID and verify the updated marks are still present.

Expected result: the complete workflow finishes without data corruption; the modified record is restored after restart.
