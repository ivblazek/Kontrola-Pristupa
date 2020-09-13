# Kontrola Pristupa - Seminarski rad NWP 2020

## Aplikacija za administraciju
#### Aplikacija služi za pregled i uređivanje baze podataka koja služi za Kontrolu Pristupa
#### Aplikacijom upravljaju Operateri kojima je dodijeljeno korisničko ime i lozinka a podjeljeni su na obične korisnike i administratore
- Otvaranjem aplikacije potrebno se prijaviti sa korisničkim podatcim "admin" "admin" za Administratora ili "user" "user" za običnog korisnika
- U glavnom prozoru nakon Login-a nalaze se svi događaji, prikaz najnovijih događaja ostvaruje se pritiskom na tipku "Refresh"
- Događaji se mogu filtrirati pritiskom na "Filter"
- Moguć je ispis događaja koji su trenutno prikazani u glavnom prozoru pritiskom na "Report->Print"
- Dodavanje Korisnika, Grupa, Pravila, Vrata i Operatera vrši se pritiskom na odgovarajuću kontrolu npr. dodavanje Korisnika "User->Add User"
- Pregleda Korisnika, Grupa, Pravila, Vrata i Operatera vrši se pritiskom na odgovarajuću kontrolu npr. za pregled Korisnika "User->List Users"
- Uređivanje ili brisanje Korisnika, Grupa, Pravila, Vrata i Operatera vrši se dvostrukim klikom miša na željenu stavku unutar prozora u kojem su izlistani (samo administrator)
- Promjena lozinke vrši se pritiskom na kontrolu "Operator->Change Password"
- U slučaju da kod prijave 3 puta upišemo krivu lozinku više se nije moguće prijavit, potrebno je da admin ponovno omogući korisniku prijavu tako što će otvorit prozor "Operator->List Operators" i kliknuti na željenog koisnika te na gumb "Unlock"
- Moguće je i resetirati lozinku za korisnike, potrebno je otvoriti prozor "Operator->List Operators" i kliknuti na željenog koisnika te na gumb "Reset Password", nakon toga lozinka je "defaultpassword123"
- Administrator može dodijeliti administratorsko pravo i ukloniti ga otvoranjem prozora "Operator->List Operators" i klikom na željenog koisnika te na gumb "Add Admin" odnosno "Remove Admin"
- Pritiskom na "Logout" odjavljujemo se ali ne zatvaramo aplikaciju.

## Zahtjevi za instalaciju
+ [SQL Server 2019](https://www.microsoft.com/en-us/sql-server/sql-server-downloads)
+ [SQL Server Management Studio](https://docs.microsoft.com/en-us/sql/ssms/download-sql-server-management-studio-ssms?view=sql-server-ver15)

## Upute za instalaciju
1. Instalacija programa "setup.exe" koji se nalazi u "Access Control\Release"
2. Potrebno je prikačiti (Attach) bazu podataka "KontrolaPristupa.mdf" ("C:\Program Files (x86)\Seminarski Rad\Database") na SQL server pomoću SQL Server Management studia. 
 -Napomena: trenutni korisnik treba na gore navedenoj  mapi imati prava čitanja i pisanja (staviti "Permissions for Users" u "Security"-u Foldera na "Full Control")
 3. Nako što prikačimo bazu potrebno je napraviti ODBC Data Source (32-bit), "System DSN" imena "KontrolaPristupa" koji će pokazivati na navedenu bazu.
 4. Nakon pokretanja aplikacije možemo koristiti korisničko ime i lozinku "admin" "admin" za Administratora ili "user" "user" za običnog korisnika.
