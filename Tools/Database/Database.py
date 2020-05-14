
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

	# Execute sql statements from .sql script file
	def ExecuteSQLScriptFile(self, filePath):
		file = open(filePath, 'r')
		sql = ""
		for line in file.readlines():
			sql += line
		self.cursor.execute(str(sql))    
		self.connection.commit()

	def Commit(self):
		self.connection.commit()

	# Add a row in a table
	def AddRow(self, tableName, **kwargs):
		# Create command buffer
		sqlCommand = ""
		sqlCommandPlaceholders = ""

		# Insert into specified table
		sqlCommand += "INSERT INTO " + tableName + '('

		# For each key, add command and placeholder
		for key in kwargs.keys():
			sqlCommand += key + ','
			sqlCommandPlaceholders += "?,"

		# Remove unnecessary last commas
		sqlCommand = sqlCommand[:-1]
		sqlCommandPlaceholders = sqlCommandPlaceholders[:-1]
		
		# Close brackets
		sqlCommand += ')'
		sqlCommandPlaceholders += ')'

		# Merge command and placeholders
		sqlCommand += " VALUES(" + sqlCommandPlaceholders

		# Get values
		argValues = list(kwargs.values())
		# Convert Path to string
		argValues[0] = str(argValues[0])
		# Convert argValues to tuple
		sqlParams = tuple(argValues)

		# Execute command with params
		self.cursor.execute(sqlCommand, sqlParams)