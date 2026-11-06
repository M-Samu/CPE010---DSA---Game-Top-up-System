**Project Title **

In-game currency Top-up system utilizing Buy-now Pay-Later

**Project Description **

This project is a C++ terminal based business process system, which presents a game top-up system for MOBA games including Mobile Legends, Wild Rift, and Honor of Kings.
In addition, the system features a account system, wherein users can register and login an account, in game currency top-up, purchase history tracking, account details.
With search and filtering capabilities when searching for games, and even for viewing purchase history.
And the utilization of Buy Now, Pay Later payment method which allows users to choose from monthly installments. 

**Team Members**

1. Barbo, Michael Yuri 
2. Cabug, Jeffordniel 
3. Mapas, Dustin Carl 
4. Ramos, Samuel
5. Urbano, Vince Andrew


**How to compile and run**

When compiling this system, first make sure that you have a C++ compiler like GCC or MinGW installed. Code Runner can also be used.


**Sample Inputs**
======== WELCOME ========
1. Register
2. Login
3. Forgot Password
4. Exit
=========================
Choose: 1
Choose a username: sam
Choose a password: 12345
Registered successfully!

======== WELCOME ========
1. Register
2. Login
3. Forgot Password
4. Exit
=========================
Choose: 2
Username: sam
Password: 12345
Login successful. Welcome, sam!

 ------------- 
              MAIN MENU              

1. Top-up Games
2. Purchase History
3. Account Details
4. Exit
-----------------
Enter your choice (1-4): 1

======== TOP-UP MENU ========
1. Mobile Legends (MLBB)
2. Wild Rift (WR)
3. Honor of Kings (HOK)
4. Search Game
0. Back to Main Menu
=============================
Select an option: 2

======= WILD RIFT TOP-UP =======


Option  Cores             Price (PHP)
-------------------------------------
1       475               249
2       1000              499
3       2050              999
4       3650              1799
5       5350              2490
6       11000             4990
-------------------------------------
7. View Cart
8. Checkout
9. Remove Item from Cart
10. Sort Packages: Lowest to Highest Price
11. Sort Packages: Highest to Lowest Price
0. Exit
=====================================

Enter your choice: 11

Packages sorted by price: Highest to Lowest

======= WILD RIFT TOP-UP =======
Option  Cores             Price (PHP)
-------------------------------------
1       11000             4990
2       5350              2490
3       3650              1799
4       2050              999
5       1000              499
6       475               249
-------------------------------------
7. View Cart
8. Checkout
9. Remove Item from Cart
10. Sort Packages: Lowest to Highest Price
11. Sort Packages: Highest to Lowest Price
0. Exit
=====================================

Enter your choice: 1

Added 11000 cores to your cart.

======= WILD RIFT TOP-UP =======
Option  Cores             Price (PHP)
-------------------------------------
1       11000             4990
2       5350              2490
3       3650              1799
4       2050              999
5       1000              499
6       475               249
-------------------------------------
7. View Cart
8. Checkout
9. Remove Item from Cart
10. Sort Packages: Lowest to Highest Price
11. Sort Packages: Highest to Lowest Price
0. Exit
=====================================

Enter your choice: 10

Packages sorted by price: Lowest to Highest

======= WILD RIFT TOP-UP =======
Option  Cores             Price (PHP)
-------------------------------------
1       475               249
2       1000              499
3       2050              999
4       3650              1799
5       5350              2490
6       11000             4990
-------------------------------------
7. View Cart
8. Checkout
9. Remove Item from Cart
10. Sort Packages: Lowest to Highest Price
11. Sort Packages: Highest to Lowest Price
0. Exit
=====================================

Enter your choice: 2

Added 1000 cores to your cart.

======= WILD RIFT TOP-UP =======
Option  Cores             Price (PHP)
-------------------------------------
1       475               249
2       1000              499
3       2050              999
4       3650              1799
5       5350              2490
6       11000             4990
-------------------------------------
7. View Cart
8. Checkout
9. Remove Item from Cart
10. Sort Packages: Lowest to Highest Price
11. Sort Packages: Highest to Lowest Price
0. Exit
=====================================

Enter your choice: 7

========== YOUR CART ==========
Item    Wild Cores        Price       
--------------------------------------
1       11000             PHP 4990
2       1000              PHP 499
--------------------------------------
Total: PHP 5489

======= WILD RIFT TOP-UP =======
Option  Cores             Price (PHP)
-------------------------------------
1       475               249
2       1000              499
3       2050              999
4       3650              1799
5       5350              2490
6       11000             4990
-------------------------------------
7. View Cart
8. Checkout
9. Remove Item from Cart
10. Sort Packages: Lowest to Highest Price
11. Sort Packages: Highest to Lowest Price
0. Exit
=====================================

Enter your choice: 9

========== YOUR CART ==========
Item    Wild Cores        Price       
--------------------------------------
1       11000             PHP 4990
2       1000              PHP 499
--------------------------------------
Total: PHP 5489

Enter the item number to remove: 1
11000 cores removed from your cart.

======= WILD RIFT TOP-UP =======
Option  Cores             Price (PHP)
-------------------------------------
1       475               249
2       1000              499
3       2050              999
4       3650              1799
5       5350              2490
6       11000             4990
-------------------------------------
7. View Cart
8. Checkout
9. Remove Item from Cart
10. Sort Packages: Lowest to Highest Price
11. Sort Packages: Highest to Lowest Price
0. Exit
=====================================

Enter your choice: 8

========== YOUR CART ==========
Item    Wild Cores        Price       
--------------------------------------
1       1000              PHP 499
--------------------------------------
Total: PHP 499

Proceed to checkout? (Y/N): Y

Enter your Wild Rift Player ID: 123123 

========== PAYMENT METHODS ==========
1. GCash
2. Maya
3. PayPal
4. Buy Now, Pay Later (BNPL)
=====================================
Select payment method (1-4): 1

Processing GCash payment...

========== RECEIPT ==========
Date: November 06, 2026
Player ID: 123123
Total Cores: 1000
Total Amount: PHP 499
Status: Sent
===============================

======= WILD RIFT TOP-UP =======
Option  Cores             Price (PHP)
-------------------------------------
1       475               249
2       1000              499
3       2050              999
4       3650              1799
5       5350              2490
6       11000             4990
-------------------------------------
7. View Cart
8. Checkout
9. Remove Item from Cart
10. Sort Packages: Lowest to Highest Price
11. Sort Packages: Highest to Lowest Price
0. Exit
=====================================

Enter your choice: 0

Thank you for using Wild Rift Top-Up!

======== TOP-UP MENU ========
1. Mobile Legends (MLBB)
2. Wild Rift (WR)
3. Honor of Kings (HOK)
4. Search Game
0. Back to Main Menu
=============================
Select an option: 3

======= HONOR OF KINGS TOP-UP =======
Option  Tokens            Price (PHP)
-------------------------------------
1       80                65
2       240               198
3       560               460
4       830               650
5       1245              960
6       4180              3200
-------------------------------------
7. View Cart
8. Checkout
9. Remove Item from Cart
10. Sort Packages: Lowest to Highest Price
11. Sort Packages: Highest to Lowest Price
0. Exit
=====================================

Enter your choice: 5

Added 1245 tokens to your cart.

======= HONOR OF KINGS TOP-UP =======
Option  Tokens            Price (PHP)
-------------------------------------
1       80                65
2       240               198
3       560               460
4       830               650
5       1245              960
6       4180              3200
-------------------------------------
7. View Cart
8. Checkout
9. Remove Item from Cart
10. Sort Packages: Lowest to Highest Price
11. Sort Packages: Highest to Lowest Price
0. Exit
=====================================

Enter your choice: 8

========== YOUR CART ==========
Item    Tokens            Price       
--------------------------------------
1       1245              PHP 960
--------------------------------------
Total: PHP 960

Proceed to checkout? (Y/N): Y

Enter your Honor of Kings Player Email: testemail@gmail.com

========== PAYMENT METHODS ==========
1. GCash
2. Maya
3. PayPal
4. Buy Now, Pay Later (BNPL)
=====================================
Select payment method (1-4): 4

====== BUY NOW, PAY LATER ======
1. 1 Month  (0% interest)
2. 2 Months (1.3% interest)
3. 3 Months (1.3% interest)
================================
Select installment plan (1-3): 3

--- BNPL Plan Selected ---
Principal Amount : PHP 960.00
Interest Applied : PHP 12.48 (1.30%)
Total to Pay     : PHP 972.48
Monthly Payment  : PHP 324.16 for 3 month(s)
BNPL successfully scheduled! You can view and pay your balance in Account Details.

========== RECEIPT ==========
Date: November 06, 2026
Player Email: testemail@gmail.com
Total Tokens: 1245
Total Amount: PHP 972
Status: Sent
===============================

======= HONOR OF KINGS TOP-UP =======
Option  Tokens            Price (PHP)
-------------------------------------
1       80                65
2       240               198
3       560               460
4       830               650
5       1245              960
6       4180              3200
-------------------------------------
7. View Cart
8. Checkout
9. Remove Item from Cart
10. Sort Packages: Lowest to Highest Price
11. Sort Packages: Highest to Lowest Price
0. Exit
=====================================

Enter your choice: 0

Thank you for using HOK Top-Up!

======== TOP-UP MENU ========
1. Mobile Legends (MLBB)
2. Wild Rift (WR)
3. Honor of Kings (HOK)
4. Search Game
0. Back to Main Menu
=============================
Select an option: 0

 ------------- 
              MAIN MENU              

1. Top-up Games
2. Purchase History
3. Account Details
4. Exit
-----------------
Enter your choice (1-4): 2

======= PURCHASE HISTORY (sam) =======
1. View all transactions
2. Filter by date
3. Filter by date range
0. Back
================================
Enter your choice: 1
ID    Date                Game           Account (ID/Email)       Item Count     Amount      Status
------------------------------------------------------------------------------------------------------
1     November 5, 2026    MLBB           12313 (123)              86 Diamonds    PHP 49      Sent
2     November 6, 2026    Wild Rift      123123                   1000 Cores     PHP 499     Sent
3     November 6, 2026    HoK            testemail@gmail.com      1245 Tokens    PHP 972     Sent

======= PURCHASE HISTORY (sam) =======
1. View all transactions
2. Filter by date
3. Filter by date range
0. Back
================================
Enter your choice: 1
ID    Date                Game           Account (ID/Email)       Item Count     Amount      Status
------------------------------------------------------------------------------------------------------
1     November 5, 2026    MLBB           12313 (123)              86 Diamonds    PHP 49      Sent
2     November 6, 2026    Wild Rift      123123                   1000 Cores     PHP 499     Sent
3     November 6, 2026    HoK            testemail@gmail.com      1245 Tokens    PHP 972     Sent

======= PURCHASE HISTORY (sam) =======
1. View all transactions
2. Filter by date
3. Filter by date range
0. Back
================================
Enter your choice: 2

Enter date (YYYY-MM-DD): 2026-6-11
ID    Date                Game           Account (ID/Email)       Item Count     Amount      Status
------------------------------------------------------------------------------------------------------

No transactions found for sam within that date range.

======= PURCHASE HISTORY (sam) =======
1. View all transactions
2. Filter by date
3. Filter by date range
0. Back
================================
Enter your choice: 2

Enter date (YYYY-MM-DD): 2026-11-06
ID    Date                Game           Account (ID/Email)       Item Count     Amount      Status
------------------------------------------------------------------------------------------------------
2     November 6, 2026    Wild Rift      123123                   1000 Cores     PHP 499     Sent
3     November 6, 2026    HoK            testemail@gmail.com      1245 Tokens    PHP 972     Sent
------------------------------------------------------------------------------------------------------
2 transaction(s) | Total spent: PHP 1471

======= PURCHASE HISTORY (sam) =======
1. View all transactions
2. Filter by date
3. Filter by date range
0. Back
================================
Enter your choice: 0

 ------------- 
              MAIN MENU              

1. Top-up Games
2. Purchase History
3. Account Details
4. Exit
-----------------
Enter your choice (1-4): 3

----------- ACCOUNT DETAILS ----------
Username          : sam
Outstanding Pay Later Balance: PHP 972.48
------------------------------------------
Would you like to pay early now? (Y/N): Y

--- Processing Payment ---
Successfully Paid Month 1 Installment: PHP 324.16
--------------------------

--- RECENT ACCOUNT PURCHASES ---
ID    Date                Game           Account (ID/Email)       Item Count     Amount      Status
------------------------------------------------------------------------------------------------------
1     November 5, 2026    MLBB           12313 (123)              86 Diamonds    PHP 49      Sent
2     November 6, 2026    Wild Rift      123123                   1000 Cores     PHP 499     Sent
3     November 6, 2026    HoK            testemail@gmail.com      1245 Tokens    PHP 972     Sent
------------------------------------------

 ------------- 
              MAIN MENU              

1. Top-up Games
2. Purchase History
3. Account Details
4. Exit
-----------------
Enter your choice (1-4): 3

----------- ACCOUNT DETAILS ----------
Username          : sam
Outstanding Pay Later Balance: PHP 648.32
------------------------------------------
Would you like to pay early now? (Y/N): Y

--- Processing Payment ---
Successfully Paid Month 2 Installment: PHP 324.16
--------------------------

--- RECENT ACCOUNT PURCHASES ---
ID    Date                Game           Account (ID/Email)       Item Count     Amount      Status
------------------------------------------------------------------------------------------------------
1     November 5, 2026    MLBB           12313 (123)              86 Diamonds    PHP 49      Sent
2     November 6, 2026    Wild Rift      123123                   1000 Cores     PHP 499     Sent
3     November 6, 2026    HoK            testemail@gmail.com      1245 Tokens    PHP 972     Sent
------------------------------------------

 ------------- 
              MAIN MENU              

1. Top-up Games
2. Purchase History
3. Account Details
4. Exit
-----------------
Enter your choice (1-4): 3

----------- ACCOUNT DETAILS ----------
Username          : sam
Outstanding Pay Later Balance: PHP 324.16
------------------------------------------
Would you like to pay early now? (Y/N): Y

--- Processing Payment ---
Successfully Paid Month 3 Installment: PHP 324.16
--------------------------

--- RECENT ACCOUNT PURCHASES ---
ID    Date                Game           Account (ID/Email)       Item Count     Amount      Status
------------------------------------------------------------------------------------------------------
1     November 5, 2026    MLBB           12313 (123)              86 Diamonds    PHP 49      Sent
2     November 6, 2026    Wild Rift      123123                   1000 Cores     PHP 499     Sent
3     November 6, 2026    HoK            testemail@gmail.com      1245 Tokens    PHP 972     Sent
------------------------------------------

 ------------- 
              MAIN MENU              

1. Top-up Games
2. Purchase History
3. Account Details
4. Exit
-----------------
Enter your choice (1-4): 3

----------- ACCOUNT DETAILS ----------
Username          : sam
Outstanding Pay Later Balance: PHP 0.00
------------------------------------------

--- RECENT ACCOUNT PURCHASES ---
ID    Date                Game           Account (ID/Email)       Item Count     Amount      Status
------------------------------------------------------------------------------------------------------
1     November 5, 2026    MLBB           12313 (123)              86 Diamonds    PHP 49      Sent
2     November 6, 2026    Wild Rift      123123                   1000 Cores     PHP 499     Sent
3     November 6, 2026    HoK            testemail@gmail.com      1245 Tokens    PHP 972     Sent
------------------------------------------

 ------------- 
              MAIN MENU              

1. Top-up Games
2. Purchase History
3. Account Details
4. Exit
-----------------
Enter your choice (1-4): 4

Exiting application. Thank you!






