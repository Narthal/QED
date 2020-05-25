
import sqlite3
import os
from pathlib import Path

class Database:
	# Ctor
	def __init__(self, path, debug = True):
		# Set member variables
		self.path = path
		self.name = path.stem
		self.debug = debug
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
		# Log
		if (self.debug == True):
			print("Adding new row to table : " + tableName + " with args : " + str(kwargs))

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
		try:
			self.cursor.execute(sqlCommand, sqlParams)
		except Exception as e:
			if (self.debug == True):
				print("SQL command failed : " + sqlCommand)
				print("With parameters : " + str(argValues))
				print(e)

def DeleteRow(self, tableName, columnName, value):
	# 'DELETE FROM tasks WHERE id=?'
	# Log
	print("Deleting row in table : " + tableName)

	# Create command buffer
	sqlCommand = ""

	# Delete from table
	sqlCommand += "DELETE FROM " + tableName + " WHERE " + columnName + "=?"

	# Execute command with params
	try:
		self.cursor.execute(sqlCommand, value)
	except Exception as e:
		print("SQL command failed : " + sqlCommand)
		print("With parameters : " + str(value))
		print(e)