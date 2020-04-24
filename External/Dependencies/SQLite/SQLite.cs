using System;
using System.Collections.Generic;
using System.Text;
using QED.BuildTool.Core;


namespace QED
{
    namespace BuildTool
    {

        [RegisterPath]
        public class SQLiteDirectory : Directory
        {
            public SQLiteDirectory()
            {

            }
        }

        [RegisterPath]
        [RegisterProject]
        public class SQLite : Project
        {
            public SQLite()
            {
                // Basic config
                Name = "SQLite";
                OutputType = OutputType.Utility;
                CppVersion = CppVersion.cpp17;

                // Directories
                OutputDirectory = BuildTool.GetDirectory("SQLiteDirectory");

                // Targets
                Targets = new Targets()
                {
                    Architecture = Architecture.x64,
                    Platform = Platform.Windows,
                    Configuration = Configuration.Debug | Configuration.Release
                };

                // Conditionals
                Conditionals = new List<Conditional>()
                {
                    new Conditional
                    (
                        // Filters
                        Architecture.x64,
                        Platform.Windows,
                        Configuration.Debug | Configuration.Release
                    )
                    {
                        // Configuration

                        PreBuildCommand = BuildTool.GetDirectory("SQLiteDirectory").DirectoryPath + "\\" + "rebuildSQLite.bat"
                    }
                };
            }
        }
    }
}
