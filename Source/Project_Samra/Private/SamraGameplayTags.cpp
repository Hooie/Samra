// Fill out your copyright notice in the Description page of Project Settings.


#include "SamraGameplayTags.h"

namespace SamraGameplayTags
{
	/**Input Tags**/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Sprint, "InputTag.Sprint");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Grab, "InputTag.Grab");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipStick, "InputTag.EquipStick");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnequipStick, "InputTag.UnequipStick");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack_Stick, "InputTag.Attack.Stick");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Roll, "InputTag.Roll");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SwitchTarget, "InputTag.SwitchTarget");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ControllerSwitchTarget_Left, "InputTag.ControllerSwitchTarget.Left");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ControllerSwitchTarget_Right, "InputTag.ControllerSwitchTarget.Right");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_Draw, "InputTag.Skill.Buff");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_1, "InputTag.Skill.1");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Skill_2, "InputTag.Skill.2");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_PickUp_Potions, "InputTag.PickUp.Potions");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ESC, "InputTag.ESC");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_DrinkPotion, "InputTag.DrinkPotion");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "InputTag.MustBeHeld");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld_Block, "InputTag.MustBeHeld.Block");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_TargetLock, "InputTag.Toggleable.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_Lamp, "InputTag.Toggleable.Lamp");


	/**Player Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Stick, "Player.Ability.Equip.Stick");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Stick, "Player.Ability.Unequip.Stick");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Stick, "Player.Ability.Attack.Stick");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Roll, "Player.Ability.Roll");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Block, "Player.Ability.Block");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_TargetLock, "Player.Ability.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill_Draw, "Player.Ability.Skill.Draw");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill_1, "Player.Ability.Skill.1");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Skill_2, "Player.Ability.Skill.2");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_CriticalHitReact, "Player.Ability.CriticalHitReact");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_PickUp_Potions, "Player.Ability.PickUp.Potions");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_PickUp_Items, "Player.Ability.PickUp.Items");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_DrinkPotion, "Player.Ability.DrinkPotion");

	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_Skill_1, "Player.Cooldown.Skill.1");
	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_Skill_2, "Player.Cooldown.Skill.2");
	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_Skill_Buff, "Player.Cooldown.Skill.Buff");
	UE_DEFINE_GAMEPLAY_TAG(Player_Cooldown_DrinkPotion, "Player.Cooldown.DrinkPotion");

	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Stick, "Player.Weapon.Stick");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Lamp, "Player.Weapon.Lamp");

	UE_DEFINE_GAMEPLAY_TAG(Player_Card_Best, "Player.Card.Best");
	UE_DEFINE_GAMEPLAY_TAG(Player_Card_Mid, "Player.Card.Mid");
	UE_DEFINE_GAMEPLAY_TAG(Player_Card_Worst, "Player.Card.Worst");
	UE_DEFINE_GAMEPLAY_TAG(Player_Card_Stamp, "Player.Card.Stamp");

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Rolling, "Player.Status.Rolling");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Blocking, "Player.Status.Blocking");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Jumping, "Player.Status.Jumping");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_TargetLock, "Player.Status.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Alive, "Player.Status.Alive");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Attacking, "Player.Status.Attacking");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_HavingPotiong, "Player.Status.HavingPotion");

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Stick, "Player.Event.Equip.Stick");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Stick, "Player.Event.Unequip.Stick");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SuccessfulBlock, "Player.Event.SuccessfulBlock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Left, "Player.Event.SwitchTarget.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Right, "Player.Event.SwitchTarget.Right");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_CriticalHitReact, "Player.Event.CriticalHitReact");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_AOE, "Player.Event.AOE");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_ConsumePotions, "Player.Event.ConsumePotions");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_PickUpItems, "Player.Event.PickUpItems");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_ActivateBuff, "Player.Event.ActivateBuff");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_DrinkPotion, "Player.Event.DrinkPotion");

	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Normal, "Player.SetByCaller.AttackType.Normal");

	
	/**Enemy Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_FrontDash, "Enemy.Ability.FrontDash");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_BackDash, "Enemy.Ability.BackDash");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_BackAttack, "Enemy.Ability.BackAttack");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_UnderAttack, "Enemy.Status.UnderAttack");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Unblockable, "Enemy.Status.Unblockable");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Stunned, "Enemy.Status.Stunned");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_OnCombat, "Enemy.Status.OnCombat");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_Breath, "Enemy.Event.Breath");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_Screaming, "Enemy.Event.Screaming");

	/**Shared Tags**/
	UE_DEFINE_GAMEPLAY_TAG(Shared_Abiity_HitReact, "Shared.Abiity.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Abiity_Death, "Shared.Abiity.Death");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_SpawnProjectile, "Shared.Event.SpawnProjectile");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Stunned, "Shared.Event.Stunned");

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dead, "Shared.Status.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");

	/**Game Data Tags**/
	UE_DEFINE_GAMEPLAY_TAG(GameData_Level_StartMap, "GameData.Level.LoadGameMap");
	UE_DEFINE_GAMEPLAY_TAG(GameData_Level_MainMenuMap, "GameData.Level.MainMenuMap");

	UE_DEFINE_GAMEPLAY_TAG(GameData_SaveGame_Slot_1, "GameData.SaveGame.Slot.1");
	UE_DEFINE_GAMEPLAY_TAG(GameData_SaveGame_Slot_2, "GameData.SaveGame.Slot.2");
	UE_DEFINE_GAMEPLAY_TAG(GameData_SaveGame_Slot_3, "GameData.SaveGame.Slot.3");
	UE_DEFINE_GAMEPLAY_TAG(GameData_SaveGame_Slot_4, "GameData.SaveGame.Slot.4");

}