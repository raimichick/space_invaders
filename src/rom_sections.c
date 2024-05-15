#include <stdint.h>
#include <stdio.h>

// Code sections are taken from https://computerarcheology.com/Arcade/SpaceInvaders/Code.html

int print_rom_section_desc(uint16_t pc)
{
    // STARTUP AND INTERRUPTS
    int ret = pc;
    switch (pc)
    {
        // clang-format off
    case 0x0000:  { printf("Reset\n"); break; }
    case 0x0008:  { printf("ScanLine96\n"); break; }
    case 0x0010:  { printf("ScanLine224\n"); break; }
    case 0x002d:  { printf("HandleBumpingCredit\n"); break; }
    case 0x005d:  { printf("NoGameCreditsExist\n"); break; }
    case 0x0067:  { printf("CreditNeedsRegistering\n"); break; }
    case 0x006F:  { printf("MainGameplayTimingLoop\n"); break; }
    case 0x008c:  { printf("ScanLine96Continues\n"); break; }

    // THE ALIENS
    case 0x00b1:  { printf("InitRack\n"); break; }
    case 0x0100:  { printf("DrawAlien\n"); break; }
    case 0x0141:  { printf("CursorNextAlien\n"); break; }
    case 0x017a:  { printf("GetAlienCoords\n"); break; }
    case 0x01a1:  { printf("MoveRefAlien\n"); break; }
    case 0x01c0:  { printf("InitAliens\n"); break; }
    case 0x01CD:  { printf("ReturnTwo\n"); break; }

    // MISC
    case 0x01cf:  { printf("DrawBottomLine\n"); break; }
    case 0x01d9:  { printf("AddDelta\n"); break; }
    case 0x01e4:  { printf("CopyRamMirror\n"); break; }

    // COPY/RESTORE SHIELDS
    case 0x01ef:  { printf("DrawShieldPl1\n"); break; }
    case 0x01f5:  { printf("DrawShieldPl2\n"); break; }
    case 0x0209:  { printf("RememberShields1\n"); break; }
    case 0x020e:  { printf("RememberShields2\n"); break; }
    case 0x0213:  { printf("RestoreShields2\n"); break; }
    case 0x021a:  { printf("RestoreShields1\n"); break; }
    case 0x021e:  { printf("CopyShields\n"); break; }

    // GAME OBJECTS
    case 0x0248:  { printf("RunGameObjs\n"); break; }
    case 0x028E:  { printf("GameObj0\n"); break; }
    case 0x0296:  { printf("Handle blowing up player\n"); break; }
    case 0x02AE:  { printf("Blow up finished\n"); break; }
    case 0x033B:  { printf("Player not blowing up ... handle inputs\n"); break; }
    case 0x0363:  { printf("Player is in control\n"); break; }
    case 0x036F:  { printf("Draw player sprite\n"); break; }
    case 0x0381:  { printf("MovePlayerRight\n"); break; }
    case 0x038E:  { printf("MovePlayerLeft\n"); break; }
    case 0x039B:  { printf("DrawPlayerDie\n"); break; }
    case 0x03BB:  { printf("GameObj1\n"); break; }
    case 0x03D7:  { printf("Shot blowing up because it left the playfield, hit a shield, or hit another bullet\n"); break; }
    case 0x03DF:  { printf("Draw explosion first pass through timer loop\n"); break; }
    case 0x03FA:  { printf("InitPlyShot\n"); break; }
    case 0x040A:  { printf("MovePlyShot\n"); break; }
    case 0x0426:  { printf("Collision with alien detected\n"); break; }
    case 0x042A:  { printf("Other shot-status options\n"); break; }
    case 0x0430:  { printf("ReadPlyShot\n"); break; }
    case 0x0436:  { printf("EndOfBlowup\n"); break; }
    case 0x0462:  { printf("Setup saucer direction for next trip\n"); break; }
    case 0x0476:  { printf("GameObj2\n"); break; }
    case 0x04AB:  { printf("ResetShot\n"); break; }
    case 0x04B6:  { printf("GameObj3\n"); break; }
    case 0x050E:  { printf("Game task 4 when splash screen alien is shooting extra \"C\" with a squiggly shot\n"); break; }
    case 0x050F:  { printf("GameObject 4 comes here if processing a squiggly shot\n"); break; }
    case 0x053E:  { printf("Shot explosion is over. Remove the shot.\n"); break; }
    case 0x0550:  { printf("ToShotStruct\n"); break; }
    case 0x055B:  { printf("FromShotStruct\n"); break; }
    case 0x0563:  { printf("HandleAlienShot\n"); break; }
    case 0x057C:  { printf("Make sure it isn't too soon to fire another shot\n"); break; }
    case 0x05C1:  { printf("Move the alien shot\n"); break; }
    case 0x061B:  { printf("Start a shot right over the player\n"); break; }
    case 0x062F:  { printf("FindInColumn\n"); break; }
    case 0x0644:  { printf("ShotBlowingUp\n"); break; }
    case 0x0682:  { printf("GameObj4\n"); break; }
    case 0x0765:  { printf("WaitForStart\n"); break; }

    // START NEW GAME
    case 0x0798:  { printf("NewGame\n"); break; }
    case 0x079B:  { printf("2 player start sequence enters here with a=1 and B=98 (-2)\n"); break; }
    case 0x081F:  { printf("GAME LOOP\n"); break; }
    case 0x0857:  { printf("Test for 1 or 2 player start button press\n"); break; }
    case 0x086D:  { printf("2 PLAYER START\n"); break; }
    case 0x0886:  { printf("GetAlRefPtr\n"); break; }
    case 0x088D:  { printf("PromptPlayer\n"); break; }
    case 0x08D1:  { printf("GetShipsPerCred\n"); break; }
    case 0x08D8:  { printf("SpeedShots\n"); break; }
    case 0x08F3:  { printf("PrintMessage\n"); break; }
    case 0x08FF:  { printf("DrawChar\n"); break; }
    case 0x0913:  { printf("TimeToSaucer\n"); break; }
    case 0x092E:  { printf("Get number of ships for acive player\n"); break; }
    case 0x0935:  { printf("Award extra ship if score has reached ceiling\n"); break; }
    case 0x097C:  { printf("AlienScoreValue\n"); break; }
    case 0x0988:  { printf("AdjustScore\n"); break; }
    case 0x09AD:  { printf("Print4Digits\n"); break; }
    case 0x09B2:  { printf("DrawHexByte\n"); break; }
    case 0x09CA:  { printf("Get score descriptor for active player\n"); break; }
    case 0x09D6:  { printf("ClearPlayField\n"); break; }
    case 0x0A59:  { printf("Check to see if player is hit\n"); break; }
    case 0x0A5F:  { printf("ScoreForAlien\n"); break; }
    case 0x0A80:  { printf("Animate\n"); break; }
    case 0x0A93:  { printf("PrintMessageDel\n"); break; }
    case 0x0AAB:  { printf("SplashSquiggly\n"); break; }
    case 0x0AB1:  { printf("OneSecDelay\n"); break; }
    case 0x0AB6:  { printf("TwoSecDelay\n"); break; }
    case 0x0ABB:  { printf("SplashDemo\n"); break; }
    case 0x0ABF:  { printf("ISRSplTasks\n"); break; }
    case 0x0ACF:  { printf(" Message to center of screen. Only used in one place for \"SPACE  INVADERS\"\n"); break; }

    case 0x0AD7:  { printf("WaitOnDelay\n"); break; }
    case 0x0AE2:  { printf("IniSplashAni\n"); break; }
    case 0x0AEA:  { printf("After initialization ... splash screens\n"); break; }
    case 0x0B1E:  { printf("Animate small alien replacing upside-down Y with correct Y\n"); break; }
    case 0x0B4A:  { printf("Play demo\n"); break; }
    case 0x0B89:  { printf("Credit information\n"); break; }
    case 0x0BF7:  { printf("MessageCorp\n"); break; }

    // DIAGNOSTICS ROUTINE
    case 0x0C00:  { printf("RmvdDiagBlock1\n"); break; }
    case 0x0D00:  { printf("RmvdDiagBlock2\n"); break; }
    case 0x0E00:  { printf("RmvdDiagBlock3\n"); break; }
    case 0x0F00:  { printf("RmvdDiagBlock4\n"); break; }

    // OTHER
    case 0x1400:  { printf("DrawShiftedSprite\n"); break; }
    case 0x1424:  { printf("EraseSimpleSprite\n"); break; }
    case 0x1439:  { printf("DrawSimpSprite\n"); break; }
    case 0x1452:  { printf("EraseShifted\n"); break; }
    case 0x1474:  { printf("CnvtPixNumber\n"); break; }
    case 0x147C:  { printf("RememberShields\n"); break; }
    case 0x1491:  { printf("DrawSprCollision\n"); break; }
    case 0x14CB:  { printf("ClearSmallSprite\n"); break; }
    case 0x14D8:  { printf("PlayerShotHit\n"); break; }
    case 0x1504:  { printf("CodeBug1\n"); break; }
    case 0x1530:  { printf("Player shot leaving playfield, hitting shield, or hitting an alien shot\n"); break; }
    case 0x1538:  { printf("AExplodeTime\n"); break; }
    case 0x1554:  { printf("Cnt16s\n"); break; }
    case 0x1562:  { printf("FindRow\n"); break; }
    case 0x156F:  { printf("FindColumn\n"); break; }
    case 0x1581:  { printf("GetAlienStatPtr\n"); break; }
    case 0x1590:  { printf("WrapRef\n"); break; }
    case 0x1597:  { printf("RackBump\n"); break; }
    case 0x15D3:  { printf("DrawSprite\n"); break; }
    case 0x15F3:  { printf("CountAliens\n"); break; }
    case 0x1611:  { printf("GetPlayerDataPtr\n"); break; }
    case 0x1618:  { printf("PlrFireOrDemo\n"); break; }
    case 0x1652:  { printf("Handle demo (constant fire, parse demo commands)\n"); break; }
    case 0x170E:  { printf("AShotReloadRate\n"); break; }
    case 0x172C:  { printf("ShotSound\n"); break; }
    case 0x1740:  { printf("TimeFleetSound\n"); break; }
    case 0x1775:  { printf("FleetDelayExShip\n"); break; }
    case 0x17B4:  { printf("SndOffExtPly\n"); break; }
    case 0x17C0:  { printf("ReadInputs\n"); break; }
    case 0x17CD:  { printf("CheckHandleTilt\n"); break; }
    case 0x1804:  { printf("CtrlSaucerSound\n"); break; }
    case 0x1815:  { printf("DrawAdvTable\n"); break; }
    case 0x1856:  { printf("ReadPriStruct\n"); break; }
    case 0x1868:  { printf("SplashSprite\n"); break; }
    case 0x189E:  { printf(";Animate alien shot to extra \"C\" in splash\n"); break; }

    case 0x18D4:  { printf("INIT\n"); break; }
    case 0x18E7:  { printf("Get player-alive flag for OTHER player\n"); break; }
    case 0x18FA:  { printf("SoundBits3On\n"); break; }
    case 0x1904:  { printf("InitAliensP2\n"); break; }
    case 0x190A:  { printf("PlyrShotAndBump\n"); break; }
    case 0x1910:  { printf("CurPlyAlive\n"); break; }
    case 0x191A:  { printf("DrawScoreHead\n"); break; }
    case 0x1931:  { printf("DrawScore\n"); break; }
    case 0x1947:  { printf("DrawNumCredits\n"); break; }
    case 0x1950:  { printf("PrintHiScore\n"); break; }
    case 0x1956:  { printf("DrawStatus\n"); break; }
    case 0x199A:  { printf("CheckHiddenMes\n"); break; }
    case 0x19BE:  { printf("MessageTaito\n"); break; }
    case 0x19D1:  { printf("EnableGameTasks\n"); break; }
    case 0x19D7:  { printf("DsableGameTasks\n"); break; }
    case 0x19DC:  { printf("SoundBits3Off\n"); break; }
    case 0x19E6:  { printf("DrawNumShips\n"); break; }
    case 0x1A06:  { printf("CompYToBeam\n"); break; }
    case 0x1A32:  { printf("BlockCopy\n"); break; }
    case 0x1A3B:  { printf("ReadDesc\n"); break; }
    case 0x1A47:  { printf("ConvToScr\n"); break; }
    case 0x1A5C:  { printf("ClearScreen\n"); break; }
    case 0x1A69:  { printf("RestoreShields\n"); break; }
    case 0x1A7F:  { printf("RemoveShip\n"); break; }

    // DATA
    case 0x1AA1:  { printf("ShotReloadRate\n"); break; }
    case 0x1AA6:  { printf("MessageGOver\n"); break; }
    case 0x1ABA:  { printf("MessageB1or2\n"); break; }
    case 0x1ACF:  { printf("Message1Only\n"); break; }
    case 0x1AE4:  { printf("MessageScore\n"); break; }
    default: { ret = -1; break; };
    }
    return ret;
}
