import sqlite3

#Connecting to sqlite
conn = sqlite3.connect('data.db')

#Creating a cursor object using the cursor() method
cursor = conn.cursor()

#Create Table
#Doping EMPLOYEE table if already exists.
cursor.execute("DROP TABLE IF EXISTS data")

#Creating table as per requirement
sql ='''CREATE TABLE data(
   id INTEGER PRIMARY KEY AUTOINCREMENT,
   humidity INTEGER,
   temperature INTEGER,
   pressure INTEGER,
   result CHAR(20)
)'''
cursor.execute(sql)
print("Table created successfully........")


# Insert Table

# Insert Data
sql ='''INSERT INTO data (humidity,temperature,pressure,result) VALUES (80.0, 80.0, 105.3, 'Light Rain')'''
cursor.execute(sql)
print("Data Inserted successfully........")

# Select Data
sql ='''SELECT * FROM data ORDER BY ID DESC LIMIT 1'''
cursor.execute(sql)
rows = cursor.fetchall()

for row in rows:
   print(row)
print("Data Selected successfully........")


# Commit your changes in the database
conn.commit()

#Closing the connection
conn.close()