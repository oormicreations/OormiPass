# Oormi Pass Project Overview

![Promo](https://oormi.in/software/oormipass/images/opicon170p.png)
![Promo](https://oormi.in/software/oormipass/images/ss.jpg)


**Oormi Pass** is a free, cross platform and open sourced application for password management and storage. It maintains and displays your passwords corresponding to various websites and files etc in a categorized way.


---

**Usage and Help**

https://oormi.in/software/oormipass/help.html

---

**Intro Video**

Coming soon.

---

**Download link**

Windows:
https://github.com/oormicreations/OormiPass/releases

Linux and Mac OS:
No binaries at this time. Checkout and build please. See below for issues.


---

**Features:**

* Stores passwords securely using AES encryption.
* Requires only one master password to access all passwords.
* Stores other useful info like usernames, urls, notes etc.
* Items are categorized neatly into groups, which can be accessed easily by simply clicking their names in the list.
* Users can customize the groups and all items in the group.
* Open URLs directly from Oormi Pass and paste your username and password. Save precious time.
* Functions to auto log out and change master password.
* Hide or show passwords.
* Built in password generator.
* Minimal UI.
* Runs on MS Windows 7 to 10, Linux and Mac OS.
* Code::Blocks 17.12, MinGW, C++11, wxWidgets 3.1.2
* Dependencies: wxWidgets 3.1.2, wxSmith, Crypto++ 5.6.3

---

**What is new in version 1.0.0**

* See above.

---

**Building Oormi Pass from source**

You will need Code::Blocks with MinGW and wxWidgets. You will also need Crypto++ 5.6.3 library (Monolithic static) with all the headers. All 32bits.

Once you get that, just open the CB project and set up the link paths and include directories in both the Debug and Release builds. In Windows it should compile and link without any changes. For Linux and Mac OS, some changes will be needed such as changing the path for storage of data and hashes etc. In windows, it is the user AppData folder, which is determined by wxWidgets.

---

**Security and Encryption**

Oormi Pass encrypts passwords using the AES method implemented in Crypto++ open source cryptography library. This is widely used and time tested library, but the security is only as good as that which it provides. Use Oormi Pass if you trust Crypto++.

The master password is not stored. An SHA256 salted hash is stored instead. Every time you log in the hash of the entered password is compared with the stored hash to verify and authenticate the user. However, once the program is running, the master password resides in RAM in clear text.

The passwords are encrypted using AES for which the key is derived from the master password and a salt string using HKDF method (implemented in Crypto++). They are stored in Base64 encoding in a clear text delimited database.

The individual passwords are decrypted using the master password derived key only when the show password or copy password button is clicked. Else they remain encrypted even in RAM.

Except for passwords, other fields remain in clear text both on the disk and in RAM. However, they can also be encrypted with some changes in the source, if really needed.


---

A FOSS Project by Oormi Creations

http://oormi.in

oormicreations@gmail.com


![logo](https://oormi.in/software/cbp/images/OormiLogo.png)