using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;

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

                public List<string> Files { get; private set; }

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

                public void AddFiles(string searchString, bool recursive = false, string exceptString = "")
                {
                    System.IO.SearchOption searchOption;
                    if (recursive)
                    {
                        searchOption = System.IO.SearchOption.AllDirectories;
                    }
                    else
                    {
                        searchOption = System.IO.SearchOption.TopDirectoryOnly;
                    }

                    string[] files = System.IO.Directory.GetFiles(Directory.DirectoryPath, searchString, searchOption);
                    List<string> exceptFiles = new List<string>();
                    if (exceptString != "")
                    {
                        exceptFiles = new List<string>(System.IO.Directory.GetFiles(Directory.DirectoryPath, exceptString, searchOption));
                    } 

                    foreach (string file in files)
                    {
                        if (!exceptFiles.Contains(file))
                        {
                            BuildTool.fileGroups[FileGroupName].Add(file);
                        }
                    }
                }

                public List<string> GetFiles(string searchString)
                {
                    List<string> files = new List<string>();

                    foreach (string file in Files)
                    {
                        Match m = Regex.Match(file, searchString, RegexOptions.IgnoreCase);
                        if (m.Success)
                        {
                            files.Add(file);
                        }
                    }

                    return files;
                }
            }
        }
    }
}
