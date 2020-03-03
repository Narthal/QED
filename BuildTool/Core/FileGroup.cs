using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        namespace Core
        {
            [Flags]
            public enum FileType
            {
                None                = 0,
                Source              = 1,
                Header              = 2,
                PrecompiledHeader   = 4,
                Other               = 8
            }
            public class FileGroup : BuildToolObject
            {
                // Private default constructor, disable usage
                private FileGroup() { }

                private Directory Directory { get; set; }
                private string FileGroupName { get; set; }

                public List<string> files { get; private set; }

                public FileGroup(Directory directory, string fileGroupName)
                {
                    // Add groupname if it doesnt exists
                    if (BuildTool.fileGroups.ContainsKey(fileGroupName) == false)
                    {
                        BuildTool.fileGroups.Add(fileGroupName, new List<string>());
                    }

                    // Set values
                    Directory = directory;
                    FileGroupName = fileGroupName;
                }

                public void AddFile(string path)
                {
                    string compinedPath = System.IO.Path.Combine(Directory.DirectoryPath, path);
                    // Validate path
                    if (!System.IO.File.Exists(compinedPath))
                    {
                        Console.WriteLine("Tried to add invalid file {0} to {1} category", compinedPath, FileGroupName);
                        return;
                    }

                    BuildTool.fileGroups[FileGroupName].Add(compinedPath);
                }
            }
        }
    }
}
