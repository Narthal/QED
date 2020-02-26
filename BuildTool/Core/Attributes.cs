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
            public class RegisterProjectAttribute : UserDefinedAttribute {}

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
                    Console.WriteLine("Found build tool attributes : ");
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
                    Console.WriteLine("Found build tool types : ");
                    // Count build tool types too
                    int buildTypeCounter = 0;
                    foreach (Type type in types)
                    {
                        foreach (CustomAttributeData item in type.CustomAttributes)
                        {
                            switch (item.AttributeType)
                            {
                                case Type registerPathAttribute when registerPathAttribute == typeof(RegisterPathAttribute):
                                    // Write found type
                                    Console.WriteLine('\t' + type.ToString());

                                    // Create instance and add to list
                                    BuildTool.directories.Add((Directory)Activator.CreateInstance(type));

                                    // Increment build type counter
                                    buildTypeCounter++;

                                    // Stop if there is at least one user defined attribute
                                    break;

                                case Type registerProjectAttribute when registerProjectAttribute == typeof(RegisterProjectAttribute):
                                    // Write found type
                                    Console.WriteLine('\t' + type.ToString());

                                    // Create instance and add to list
                                    BuildTool.projects.Add((Project)Activator.CreateInstance(type));

                                    // Increment build type counter
                                    buildTypeCounter++;

                                    // Stop if there is at least one user defined attribute
                                    break;

                                default:
                                    break;
                            }
                        }
                    }
                    // Write summary
                    Console.WriteLine("Created {0} build tool objects", buildTypeCounter);
                    Console.WriteLine("Created {0} build tool directory objects", BuildTool.directories.Count);
                }
            }
        }
    }
}
