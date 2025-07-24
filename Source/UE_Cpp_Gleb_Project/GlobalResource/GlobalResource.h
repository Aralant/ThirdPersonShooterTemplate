#pragma once

UENUM(BlueprintType)
enum class EInventoryType : uint8
{
	None,
	Head,
	Leg,
	Hand,
	Torso
};

UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	None,
	SwapInventory,
	TradeInventory
};

UENUM(BlueprintType)
enum class ESlot : uint8
{
	LeftHand,
	RightHand,
	Torso,
	Leg,
	Head
};

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	None,
	Primary,     
	Secondary,  
	Melee 
};