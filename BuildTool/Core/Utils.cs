using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        namespace Core
        {
            public static class Utils
            {
                public static string GetRelativePath(string path, string relativeTo)
                {
                    string relative = Path.GetRelativePath(relativeTo, path);
                    return relative;
                }
            }
        }
    }
}
