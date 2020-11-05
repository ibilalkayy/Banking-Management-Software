# Banking-Management-Software

We all use ATM machines or online banking service in our daily lives for its easiness and to make changes in our account also. These changes could be your name, address and other personal information or even you can make a new account using online banking service.

Keeping this in mind, I thought to have a software that could handle all the basic stuff that a online banking service provides. So I chose C to do my coding and make this software.

For those who are not familiar with C language. It's a very powerful and low level language. To understand that how the machine works and how to think logically, C is the best option. Now come to the making of this software.

This software has six main functions. Although some extra functions are also present but they are used in these six functions. All the functions are performing different tasks. Now come to the function names and their functionality.

# No.1 main()                                                                         

This function contains all the choices that will be shown to the user and all the details that needs to be declared and called. It contains the file locations, the starting options that a user will select from and the functions that will actually be called. The options are, create a new account, update an existing account, account transaction, showing the details, remove an account and the last one is to exit the program.

# No.2 newAccount()

So the first choice is to create a new account. Here a user will give all the details that are neccessary for creating an account like the name, date of birth, id card number, phone number, address, account(current/savings/checkings/etc), fixed(Validation of an account), amount, and the pin code. After entering the details, the new account will be created.

# No.3 updateAccount()

After creating an account, if you decided to change some information in your account later, then this option will help you. Because some of the things are not fixed like your address, pin code, or phone number. These things could be changed. So to make this work, you'll be given three options to update that are your address, pin code, and phone number.

# No.4 userTransaction()

As you can get an idea by the name. This function helps the user to deposit or withdraw the amount from the account. As you deposited or withdrawn the amount. Your new amount will updated with the previous one and the result will be infront of you.

# No.5 accountInfo()

In this function, first you have to access the account. Then the acccount information will be provided to you. This information will contain all the details that you entered when creating an account. Plus it will show you the last deposit date.

# No.6 accountRemoval()

If you're not satisfied with the services of the bank then you will be given an option to easily remove your account. After removal, your account info, deposit info, and withdrawl info will all be deleted from the directory.

These six main functions came to an end. Now come to other functions that are used in these six main functions.

# No.1 allDigits()

This function differetiate the input data, to check whether it's an alphabet or a number. It is used in another function called askPin(), that I'm going to explain it later.

# No.2 record()

It is used in the accountInfo() function in which a user will see the details of the account. But this record() function will get the last deposit date from the deposit history of a user.

# No.3 read()

Reading and finding the pin code from the file requires fgets() again and again multiple times. So this read() function is made for the purpose to read and find the pin code from the file.

# No.4 askPin()

This function will ask the user to enter the pin code from whenever he/she wants to access the account. I used allDigits() function here to check whether the pin code is number and alphabets and put conditions in it.

# No.5 updateOption()

This function is used in the updateAccount() function in which a user has given three options to update that are pin code, phone number, and address.

# No.6 copying()

As it's showing by the name that by copying the data from the temporary file to the original file.
