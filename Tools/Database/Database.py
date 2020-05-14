
import sqlite3
import os

class Database:
	# Ctor
	def __init__(self, path):
		# Set member variables
		self.path = path

		# Create connection
		self.connection = sqlite3.connect(path)
		self.cursor = self.connection.cursor()

		# Log
		print("Connected to database : " + path.stem)

		# Run associated sql script
		sqlScript = os.path.splitext(path)[0] + ".sql"
		if (os.path.isfile(sqlScript)):
			self.ExecuteSQLScriptFile(sqlScript)
			print("Executed associated sql script")
		

	# Dtor
	def __del__(self):
		self.connection.close()

	def ExecuteSQLScriptFile(self, filePath):
		file = open(filePath, 'r')
		sql = ""
		for line in file.readlines():
			sql += line
		self.cursor.execute(str(sql))    
		self.connection.commit()