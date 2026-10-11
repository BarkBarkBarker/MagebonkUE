// ============================================================
//  MegaBonkLearn.Build.cs — с добавленной зависимостью EnhancedInput
//
//  ЗАЧЕМ: MegaBonkPlayerController.cpp использует
//  UEnhancedInputLocalPlayerSubsystem и UInputMappingContext.
//  Без этой строки получишь error LNK2019 (unresolved external symbol)
//  — см. THEORY-01 §3: LNK = иди в Build.cs.
//
//  ПОЧЕМУ Private, а не Public: в заголовке у нас только
//  forward declaration (class UInputMappingContext;), сам тип
//  используется исключительно в .cpp. Значит — Private.
// ============================================================

using UnrealBuildTool;

public class MegaBonkLearn : ModuleRules
{
	public MegaBonkLearn(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "EnhancedInput" });
	}
}
