
import sqlite3

class Database:
	# Ctor
	def __init__(self, path):
		self.path = path

		self.connection = sqlite3.connect(path)
		self.cursor = self.connection.cursor()

	# Dtor
	def __del__(self):
		self.connection.close()