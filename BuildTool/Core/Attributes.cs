using System;
using System.Collections.Generic;
using System.Text;

using System.Runtime.CompilerServices;
using System.Reflection;

namespace QED
{
    namespace BuildTool
    {
        namespace Core
        {
            [AttributeUsage(AttributeTargets.Class)]
            public abstract class UserDefinedAttribute : Attribute { }

            [AttributeUsage(AttributeTargets.Class)]
            public class RegisterPathAttribute : UserDefinedAttribute
            {
                public RegisterPathAttribute([CallerFilePath()] string sourceFilePath = "") { SourcePath = sourceFilePath; }

                public string SourcePath { get; private set; }
            }

            [AttributeUsage(AttributeTargets.Class)]
            public class TargetConfigAttribute : UserDefinedAttribute {}
            public static class Attributes
            {
                public static void RegisterAttributes()
                {
                    // Log init
                    Console.WriteLine("Initializing attribute registration");

                    // Get assembly and types
                    Assembly assembly = Assembly.GetExecutingAssembly();
                    Type[] types = assembly.GetTypes();
                    Console.WriteLine("Searching in assembly : " + assembly.Location);

                    // Get custom attributes
                    Console.WriteLine("Found custom attributes : ");
                    List<Type> userDefinedAttributes = new List<Type>();
                    foreach (Type type in types)
                    {
                        if (type.BaseType == typeof(UserDefinedAttribute))
                        {
                            Console.WriteLine('\t' + type.Name);
                            userDefinedAttributes.Add(type);
                        }
                    }

                    // Iterate through all types and all custom attributes in each type
                    Console.WriteLine("Found {0} user defined types", types.Length);
                    Console.WriteLine("Found types : ");
                    foreach (Type type in types)
                    {
                        foreach (CustomAttributeData item in type.CustomAttributes)
                        {
                            // True when found a type with RegisterPath attribute
                            if (item.AttributeType == typeof(RegisterPathAttribute))
                            {
                                // Write found type
                                Console.WriteLine('\t' + type.ToString());

                                // Create instance and add to list
                                BuildTool.directories.Add((Directory)Activator.CreateInstance(type));

                                // Stop if there is at least one user defined attribute
                                break;
                            }
                            else if(item.AttributeType == typeof(TargetConfigAttribute))
                            {
                                // Write found type
                                Console.WriteLine('\t' + type.ToString());

                                // Create instance and add to list, throw error if multiple target configs are defined
                                if (BuildTool.TargetConfig != null)
                                {
                                    Console.WriteLine("Can not define architecture configurations in multiple classes");
                                    throw new Exception("Can not define architecture configurations in multiple classes");
                                }
                                BuildTool.TargetConfig = ((TargetConfig)Activator.CreateInstance(type));

                                // Stop if there is at least one user defined attribute
                                break;
                            }
                        }
                    }
                    // Return directory instances
                    Console.WriteLine("Found {0} build tool objects that has user defined attributes", BuildTool.directories.Count);
                }
            }
        }
    }
}
