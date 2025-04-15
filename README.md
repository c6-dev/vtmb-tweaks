# vtmb-tweaks
Various small engine-level tweaks for Vampire the Masquerade Bloodlines. All features can be turned on and off via supplied .ini file.  
* bNoTracers - disables the bullet tracer effect for both NPCs and the player.
* bNoCorpseDespawn - prevents NPC corpses from despawning until a level transition occurs (a loading screen).
* bStackableWeapons - allows weapons to stack in the inventory. "is_stackable" must be set to 1 in weapon definition files in vdata/items.
* bNPCsDropAllWeapons - makes NPCs drop all weapons on death instead of only the last one used.
* bNonSolidRagdolls - sets CRagdollProp ragdolls as non-solid (debris collision group) to fix some cutscene bugs.
* bFixDoorsAtHighFPS - fixes the player getting stuck inside doors when playing at high framerate. Credits to funkkiy for the [original fix](https://github.com/funkkiy/BloodlinesPatch).
* bNoDoorAutoClose - Makes doors stay open instead of automatically closing after a few seconds.
  
Loader.exe is required (included with all versions of Unofficial Patch and major mods).  

To install, place vtmb-tweaks.vtm and vtmb-tweaks.ini into Bin/loader.

Built using Visual Studio 2022 and v141_xp toolset.
