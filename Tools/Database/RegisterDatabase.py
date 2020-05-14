
from pathlib import Path

from Database import Database
from ExternalScript import ExternalScriptRunner

def Register(path):
	# Connect to db
	db = Database.Database(path)

	# Get relative path of db
	relPath = Path(path).relative_to(ExternalScriptRunner.rootPath)
	db.AddRow("pathCollection", path = relPath, type = 1, generated = 1, tags = "Tools Engine")
	db.Commit()