#import pymysql.cursors
import pymysql

# Open database connection
db = pymysql.connect("localhost","wallace","","test_db" )	#ip, user, password, database

# prepare a cursor object using cursor() method
cursor = db.cursor()


'''	#============================================= '''
	#Demo1: Creating Database Table
# Drop table if it already exist using execute() method.
cursor.execute("DROP TABLE IF EXISTS Persons")

# Create table as per requirement
sql = """CREATE TABLE Persons (
         PersonID  INT,
         LASTNAME  CHAR(20),
         FirstName CHAR(20),  
         Address CHAR(20),
         City CHAR(20) )"""

cursor.execute(sql)



'''	#=============================================
	# Demo1: Prepare SQL query to INSERT a record into the database.
#sql = "INSERT INTO Persons(PersonID, LastName, FirstName, Address, City) VALUES ('%d', '%s', '%s', '%s', '%s' )" % (1, 'William', 'Wallace', 'Scotland', 'Lubeck')
#sql = "INSERT INTO Persons(PersonID, LastName, FirstName, Address, City) VALUES ('%d', '%s', '%s', '%s', '%s' )" % (2, 'Longshanks', 'Edward', 'England', 'London')
sql = "INSERT INTO Persons(PersonID, LastName, FirstName, Address, City) VALUES ('%d', '%s', '%s', '%s', '%s' )" % (3, 'Albert', 'George', 'England', 'London')

try:
	# Execute the SQL command
	cursor.execute(sql)

	# Commit your changes in the database
	db.commit()
except:
	# Rollback in case there is any error
	db.rollback()
'''


'''	#============================================= 
	#Demo2: Prepare SQL query to queries all record from the database.
sql = "SELECT * FROM Persons \
       WHERE City = '%s'" % ('London')


try:
	cursor.execute(sql)
	results = cursor.fetchall()
	for row in results:
		PersonID = row[0]
		LastName = row[1]
		FirstName = row[2]
		Address = row[3]
		City = row[4]
# Now print fetched result
		print ("PersonID: %d, LastName: %s, FirstName: %s, Address: %s, City: %s" % \
			(PersonID, LastName, FirstName, Address, City))

except:
	print ("Error: unable to fecth data")	
'''


'''	#=============================================
	#Prepare SQL query to UPDATE required records
sql = "UPDATE Persons SET PersonID = PersonID + 1 \
                          WHERE City = '%s'" % ('Lubeck')
try:
	cursor.execute(sql)
	db.commit()
except:
	# Rollback in case there is any error
	db.rollback()
'''

'''	#============================================= 
	#Prepare SQL query to DELETE required records
sql = "DELETE FROM Persons WHERE City = '%s'" % ('Berlin')
try:
	# Execute the SQL command
	cursor.execute(sql)
	# Commit your changes in the database
	db.commit()
except:
	# Rollback in case there is any error
	db.rollback()
'''


# disconnect from server
db.close()
