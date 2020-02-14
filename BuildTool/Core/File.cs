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
            public enum FileGroup
            {
                None        = 0,
                Group_01    = 1,
                Group_02    = 2,
                Group_03    = 4,
                Group_04    = 8,
                Group_05    = 16,
                Group_06    = 32,
                Group_07    = 64,
                Group_08    = 128,
                Group_09    = 256,
                Group_10    = 512,
                Group_11    = 1024,
                Group_12    = 2048,
                Group_13    = 4096,
                Group_14    = 8192,
                Group_15    = 16384,
                Group_16    = 32768,
                Group_17    = 65536,
                Group_18    = 131072,
                Group_19    = 262144,
                Group_20    = 524288,
            }
            [Flags]
            public enum FileType
            {
                None    = 0,
                Source  = 1,
                Header  = 2,
                Other   = 4,
            }
            public class File : BuildToolObject
            {
                // Private default constructor, disable usage
                private File() { }

                private Directory Directory { get; set; }
                private FileGroup FileGroup { get; set; }

                public FileType FileType { get; private set; }

                public List<string> files { get; private set; }
                public File(Directory directory, FileGroup fileGroup, FileType fileType)
                {
                    Directory = directory;
                    FileGroup = fileGroup;
                    FileType = fileType;
                }

                public File(Directory directory, string fileGroupName, FileType fileType)
                {
                    Directory = directory;
                    FileGroup fileGroup;
                    if (BuildTool.fileGroupNames.TryGetValue(fileGroupName, out fileGroup))
                    {
                        FileGroup = fileGroup;
                    }
                    else
                    {
                        FileGroup last = FileGroup.Group_01;
                        foreach (var item in BuildTool.fileGroups)
                        {
                            last = item.Key.Item1;
                        }
                        BuildTool.fileGroupNames.Add(fileGroupName, last);
                        FileGroup = last;
                    }
                    FileType = fileType;
                }

                public void AddFile(string path)
                {
                    string compinedPath = System.IO.Path.Combine(Directory.DirectoryPath, path);
                    // Validate path
                    if (!System.IO.File.Exists(compinedPath))
                    {
                        Console.WriteLine("Tried to add invalid file {0} to {1} category with {2} filetype", compinedPath, FileGroup, FileType.ToString());
                        return;
                    }
                    
                    // Check key
                    bool categoryExists = BuildTool.fileGroups.ContainsKey(new Tuple<FileGroup, FileType>(FileGroup, FileType));
                    // if key exists, put data there, if not, put self to dictionary
                    if (categoryExists)
                    {
                        List<string> paths;
                        BuildTool.fileGroups.TryGetValue(new Tuple<FileGroup, FileType>(FileGroup, FileType), out paths);
                        paths.Add(compinedPath);
                    }
                    else
                    {
                        BuildTool.fileGroups.Add(new Tuple<FileGroup, FileType>(FileGroup, FileType), new List<string> { compinedPath });
                    }
                }
            }
        }
    }
}
