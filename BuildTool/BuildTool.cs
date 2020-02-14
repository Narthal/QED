using System;
using System.Collections.Generic;
using System.Text;

namespace QED
{
    namespace BuildTool
    {
        public static class BuildTool
        {
            // Registered directories
            public static List<Core.Directory> directories = new List<Core.Directory>();

            public static Dictionary<string, Core.FileGroup> fileGroupNames = new Dictionary<string, Core.FileGroup>();

            public static Dictionary<Tuple<Core.FileGroup, Core.FileType>, List<string>> fileGroups = new Dictionary<Tuple<Core.FileGroup, Core.FileType>, List<string>>();

            public static TargetConfig TargetConfig = null;
        }
    }
}

