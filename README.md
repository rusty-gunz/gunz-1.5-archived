# GunZ1.5
A 1.5 Based GunZ Source/Client/Server with added features such as x64 support, x64 3ds max plugins, d3d9ex, etc.

GameModes currently in source:

All base 1.5 gamemodes (function challengequest as well but needs work)
Spymode

Gungame

Infection

SkillMap

BlitzKrieg* (blitzkrieg is an incomplete gamemode. the match runs and you can kill the radar to end the game. however, the interface is a mess and unfinished).

Demolition* (incomplete, missing animations, logic too client sided. preserved for anyone that wants to complete it in the future).

The 64Bit 3ds max plugins do not allow models to load on the 32bit gunz runnable builds. This requires more code modification to work for 32bit client.

To Build:

This doesn't use cmake as the refined base does for anyone coming off that. To build you'll need to use gunz.sln, matchserver.sln, matchagent.sln, and locator.sln, use encrypt_brz_release_publish and use win32 or x64. x64 is still experimental but seems to work fine.


Credits To:
Secrets of The past
S1lent
JP
Gunblade
Nick

All of these guys were a very big help in not only fixing issues in the source, but also getting me started on my programming.
