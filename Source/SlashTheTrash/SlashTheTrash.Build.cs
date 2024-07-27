// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SlashTheTrash : ModuleRules
{
	public SlashTheTrash(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "NetCore"});
		PrivateDependencyModuleNames.AddRange(new string[] {"GameplayAbilities", "GameplayTags", "GameplayTasks"});
		
		PublicIncludePaths.Add("SlashTheTrash/");
	}
}
