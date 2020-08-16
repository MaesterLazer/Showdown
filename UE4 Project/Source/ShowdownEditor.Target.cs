// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;
using System.IO;

public class ShowdownEditorTarget : TargetRules{

    public ShowdownEditorTarget(TargetInfo Target) : base(Target) {
		Type = TargetType.Editor;
		ExtraModuleNames.Add("Showdown");
        
            // List of possible project paths based on developer machines. Any developers will need to add project paths to list array
            string[] projectPaths = new string[]{
            "G:/Showdown/UE4 Project/", //Simon Norman
            };

            // Text to replace in Version header file
            const string BUILD_NUMBER_LINE = "int BuildNumber = ";

            // Absolute path to your Version header file
            string GAME_VERSION_FILE = "";

            // Line number to replace. Should minus 1 from the real line number. That is if #define GAME_BUILD_NUMBER is in line number 15 then this value should be 14
            const int BUILD_LINE_NUMBER_TO_REPLACE = 11;
            bool bGenComplete = false;

            for (int i = 0; i < projectPaths.Length; i++){
                string PROJECT_PATH = projectPaths[i];
                // Absolute path to your GameVersion header file
                GAME_VERSION_FILE = (PROJECT_PATH + "Source/Showdown/Version.h");

                // Absolute path to your BUILD_NUMBER text file
                string BUILD_NUMBER_FILE = (PROJECT_PATH + "Source/BUILD_NUMBER.txt");

                bool bFilesExist = File.Exists(GAME_VERSION_FILE) && File.Exists(BUILD_NUMBER_FILE);
                if (bFilesExist == true){

                    FileInfo GVInfo = new FileInfo(GAME_VERSION_FILE);
                    FileInfo GBInfo = new FileInfo(BUILD_NUMBER_FILE);
                    GVInfo.IsReadOnly = false;
                    GBInfo.IsReadOnly = false;

                    string BUILD_NUMBER_Text = File.ReadAllText(BUILD_NUMBER_FILE);
                    string GAME_VERSION_Text = File.ReadAllText(GAME_VERSION_FILE);

                    string BuildNumberInfo = ("const " + BUILD_NUMBER_LINE + BUILD_NUMBER_Text + ";");

                    if (GAME_VERSION_Text.Contains(BuildNumberInfo))
                    {
                        System.Console.WriteLine("VersionTracker - current build number is up to date : " + BUILD_NUMBER_Text);
                        bGenComplete = true;
                        break;
                    }

                    else if (GAME_VERSION_Text.Contains(BUILD_NUMBER_LINE))
                    {
                        //Get the line numbers of Version.h and add 1;
                        int TotalLinesInGameVersionFile = File.ReadAllLines(GAME_VERSION_FILE).GetLength(0) + 1;

                        using (var sr = new StreamReader(GAME_VERSION_FILE))
                        {

                            for (int j = 1; j < TotalLinesInGameVersionFile; j++)
                            {
                                // If the line contains #define GAME_BUILD_NUMBER
                                if (sr.ReadLine().Contains(BUILD_NUMBER_LINE))
                                {
                                    //Notify using VS Output
                                    System.Console.WriteLine("VersionTracker - Build number updated : " + BUILD_NUMBER_Text);
                                    sr.Close();
                                    var GameVersionFileLines = new List<string>(File.ReadAllLines(GAME_VERSION_FILE));
                                    //Replace build number
                                    GameVersionFileLines.RemoveAt(BUILD_LINE_NUMBER_TO_REPLACE);
                                    GameVersionFileLines.Insert(BUILD_LINE_NUMBER_TO_REPLACE, BuildNumberInfo);


                                    File.WriteAllLines(GAME_VERSION_FILE, GameVersionFileLines);
                                    bGenComplete = true;
                                    break;
                                }
                            }

                        }
                    }
                }
            }

        if (bGenComplete == false){

            throw new BuildException("Failed to get GAME_VERSION_FILE or GAME_BUILD_FILE. Version.h Must be located at <ProjectDir>/<ProjectName>/Source/<ProjectName>/Public. BUILD_NUMBER.txt Must be located at <ProjectDir>/<ProjectName>/Source/. Please ensure you have added your UE4 Project path to <ProjectName>Editor.Target.cs");

        }
    }
}
