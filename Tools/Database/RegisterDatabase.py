
from pathlib import Path

from Database import Database

databaseCollection = []
databaseTags = []

def Register(path, tags = ""):
	# Connect to db
	db = Database.Database(path)

	# Add to databases
	databaseCollection.append(db)

	# Add tags to databaseTags, these will be used when recording this database instance in registry
	databaseTags.append(tags)

def GetDatabase(dbName):
	for database in databaseCollection:
		if (database.name == dbName):
			return database