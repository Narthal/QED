﻿using System;
using System.Collections.Generic;
using System.Text;

using System.Reflection;

namespace QED
{
    namespace BuildTool
    {
        namespace Core
        {
            public abstract class Directory : BuildToolObject
            {
                public RegisterPathAttribute PathAttribute { get; protected set; }
                public string DirectoryPath { get; private set; }

                public string SubDirectory = "";

                protected Directory()
                {
                    RetrieveDirectoryPath();
                }

                public void RetrieveDirectoryPath()
                {
                    object[] customAttributes = GetType().GetCustomAttributes(true);
                    foreach (Attribute attribute in customAttributes)
                    {
                        if (attribute.GetType() == typeof(RegisterPathAttribute))
                        {
                            PathAttribute = (RegisterPathAttribute)attribute;
                            DirectoryPath = System.IO.Directory.GetParent(PathAttribute.SourcePath).FullName;
                        }
                    }

                    if (SubDirectory != "")
                    {
                        DirectoryPath += '\\' + SubDirectory;
                    }
                }
            }
        }
    }
}
