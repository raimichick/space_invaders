#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Code sections are taken from https://computerarcheology.com/Arcade/SpaceInvaders/Code.html

void print_rom_section_desc(uint16_t pc, char *message)
{
    // STARTUP AND INTERRUPTS
    switch (pc)
    {
        // clang-format off
    case 0x0000:  { strcpy(message, "Reset"); break; }
    case 0x0008:  { strcpy(message, "ScanLine96"); break; }
    case 0x0010:  { strcpy(message, "ScanLine224"); break; }
    case 0x002d:  { strcpy(message, "HandleBumpingCredit"); break; }
    case 0x005d:  { strcpy(message, "NoGameCreditsExist"); break; }
    case 0x0067:  { strcpy(message, "CreditNeedsRegistering"); break; }
    case 0x006F:  { strcpy(message, "MainGameplayTimingLoop"); break; }
    case 0x008c:  { strcpy(message, "ScanLine96Continues"); break; }

        // THE ALIENS
    case 0x00b1:  { strcpy(message, "InitRack"); break; }
    case 0x0100:  { strcpy(message, "DrawAlien"); break; }
    case 0x0141:  { strcpy(message, "CursorNextAlien"); break; }
    case 0x017a:  { strcpy(message, "GetAlienCoords"); break; }
    case 0x01a1:  { strcpy(message, "MoveRefAlien"); break; }
    case 0x01c0:  { strcpy(message, "InitAliens"); break; }
    case 0x01CD:  { strcpy(message, "ReturnTwo"); break; }

        // MISC
    case 0x01cf:  { strcpy(message, "DrawBottomLine"); break; }
    case 0x01d9:  { strcpy(message, "AddDelta"); break; }
    case 0x01e4:  { strcpy(message, "CopyRamMirror"); break; }

        // COPY/RESTORE SHIELDS
    case 0x01ef:  { strcpy(message, "DrawShieldPl1"); break; }
    case 0x01f5:  { strcpy(message, "DrawShieldPl2"); break; }
    case 0x0209:  { strcpy(message, "RememberShields1"); break; }
    case 0x020e:  { strcpy(message, "RememberShields2"); break; }
    case 0x0213:  { strcpy(message, "RestoreShields2"); break; }
    case 0x021a:  { strcpy(message, "RestoreShields1"); break; }
    case 0x021e:  { strcpy(message, "CopyShields"); break; }

        // GAME OBJECTS
    case 0x0248:  { strcpy(message, "RunGameObjs"); break; }
    case 0x028E:  { strcpy(message, "GameObj0"); break; }
    case 0x0296:  { strcpy(message, "Handle blowing up player"); break; }
    case 0x02AE:  { strcpy(message, "Blow up finished"); break; }
    case 0x033B:  { strcpy(message, "Player not blowing up ... handle inputs"); break; }
    case 0x0363:  { strcpy(message, "Player is in control"); break; }
    case 0x036F:  { strcpy(message, "Draw player sprite"); break; }
    case 0x0381:  { strcpy(message, "MovePlayerRight"); break; }
    case 0x038E:  { strcpy(message, "MovePlayerLeft"); break; }
    case 0x039B:  { strcpy(message, "DrawPlayerDie"); break; }
    case 0x03BB:  { strcpy(message, "GameObj1"); break; }
    case 0x03D7:  { strcpy(message, "Shot blowing up because it left the playfield, hit a shield, or hit another bullet"); break; }
    case 0x03DF:  { strcpy(message, "Draw explosion first pass through timer loop"); break; }
    case 0x03FA:  { strcpy(message, "InitPlyShot"); break; }
    case 0x040A:  { strcpy(message, "MovePlyShot"); break; }
    case 0x0426:  { strcpy(message, "Collision with alien detected"); break; }
    case 0x042A:  { strcpy(message, "Other shot-status options"); break; }
    case 0x0430:  { strcpy(message, "ReadPlyShot"); break; }
    case 0x0436:  { strcpy(message, "EndOfBlowup"); break; }
    case 0x0462:  { strcpy(message, "Setup saucer direction for next trip"); break; }
    case 0x0476:  { strcpy(message, "GameObj2"); break; }
    case 0x04AB:  { strcpy(message, "ResetShot"); break; }
    case 0x04B6:  { strcpy(message, "GameObj3"); break; }
    case 0x050E:  { strcpy(message, "Game task 4 when splash screen alien is shooting extra \"C\" with a squiggly shot"); break; }
    case 0x050F:  { strcpy(message, "GameObject 4 comes here if processing a squiggly shot"); break; }
    case 0x053E:  { strcpy(message, "Shot explosion is over. Remove the shot."); break; }
    case 0x0550:  { strcpy(message, "ToShotStruct"); break; }
    case 0x055B:  { strcpy(message, "FromShotStruct"); break; }
    case 0x0563:  { strcpy(message, "HandleAlienShot"); break; }
    case 0x057C:  { strcpy(message, "Make sure it isn't too soon to fire another shot"); break; }
    case 0x05C1:  { strcpy(message, "Move the alien shot"); break; }
    case 0x061B:  { strcpy(message, "Start a shot right over the player"); break; }
    case 0x062F:  { strcpy(message, "FindInColumn"); break; }
    case 0x0644:  { strcpy(message, "ShotBlowingUp"); break; }
    case 0x0682:  { strcpy(message, "GameObj4"); break; }
    case 0x0765:  { strcpy(message, "WaitForStart"); break; }

        // START NEW GAME
    case 0x0798:  { strcpy(message, "NewGame"); break; }
    case 0x079B:  { strcpy(message, "2 player start sequence enters here with a=1 and B=98 (-2)"); break; }
    case 0x081F:  { strcpy(message, "GAME LOOP"); break; }
    case 0x0857:  { strcpy(message, "Test for 1 or 2 player start button press"); break; }
    case 0x086D:  { strcpy(message, "2 PLAYER START"); break; }
    case 0x0886:  { strcpy(message, "GetAlRefPtr"); break; }
    case 0x088D:  { strcpy(message, "PromptPlayer"); break; }
    case 0x08D1:  { strcpy(message, "GetShipsPerCred"); break; }
    case 0x08D8:  { strcpy(message, "SpeedShots"); break; }
    case 0x08F3:  { strcpy(message, "PrintMessage"); break; }
    case 0x08FF:  { strcpy(message, "DrawChar"); break; }
    case 0x0913:  { strcpy(message, "TimeToSaucer"); break; }
    case 0x092E:  { strcpy(message, "Get number of ships for acive player"); break; }
    case 0x0935:  { strcpy(message, "Award extra ship if score has reached ceiling"); break; }
    case 0x097C:  { strcpy(message, "AlienScoreValue"); break; }
    case 0x0988:  { strcpy(message, "AdjustScore"); break; }
    case 0x09AD:  { strcpy(message, "Print4Digits"); break; }
    case 0x09B2:  { strcpy(message, "DrawHexByte"); break; }
    case 0x09CA:  { strcpy(message, "Get score descriptor for active player"); break; }
    case 0x09D6:  { strcpy(message, "ClearPlayField"); break; }
    case 0x0A59:  { strcpy(message, "Check to see if player is hit"); break; }
    case 0x0A5F:  { strcpy(message, "ScoreForAlien"); break; }
    case 0x0A80:  { strcpy(message, "Animate"); break; }
    case 0x0A93:  { strcpy(message, "PrintMessageDel"); break; }
    case 0x0AAB:  { strcpy(message, "SplashSquiggly"); break; }
    case 0x0AB1:  { strcpy(message, "OneSecDelay"); break; }
    case 0x0AB6:  { strcpy(message, "TwoSecDelay"); break; }
    case 0x0ABB:  { strcpy(message, "SplashDemo"); break; }
    case 0x0ABF:  { strcpy(message, "ISRSplTasks"); break; }
    case 0x0ACF:  { strcpy(message, " Message to center of screen. Only used in one place for \"SPACE  INVADERS\""); break; }

    case 0x0AD7:  { strcpy(message, "WaitOnDelay"); break; }
    case 0x0AE2:  { strcpy(message, "IniSplashAni"); break; }
    case 0x0AEA:  { strcpy(message, "After initialization ... splash screens"); break; }
    case 0x0B1E:  { strcpy(message, "Animate small alien replacing upside-down Y with correct Y"); break; }
    case 0x0B4A:  { strcpy(message, "Play demo"); break; }
    case 0x0B89:  { strcpy(message, "Credit information"); break; }
    case 0x0BF7:  { strcpy(message, "MessageCorp"); break; }

        // DIAGNOSTICS ROUTINE
    case 0x0C00:  { strcpy(message, "RmvdDiagBlock1"); break; }
    case 0x0D00:  { strcpy(message, "RmvdDiagBlock2"); break; }
    case 0x0E00:  { strcpy(message, "RmvdDiagBlock3"); break; }
    case 0x0F00:  { strcpy(message, "RmvdDiagBlock4"); break; }

        // OTHER
    case 0x1400:  { strcpy(message, "DrawShiftedSprite"); break; }
    case 0x1424:  { strcpy(message, "EraseSimpleSprite"); break; }
    case 0x1439:  { strcpy(message, "DrawSimpSprite"); break; }
    case 0x1452:  { strcpy(message, "EraseShifted"); break; }
    case 0x1474:  { strcpy(message, "CnvtPixNumber"); break; }
    case 0x147C:  { strcpy(message, "RememberShields"); break; }
    case 0x1491:  { strcpy(message, "DrawSprCollision"); break; }
    case 0x14CB:  { strcpy(message, "ClearSmallSprite"); break; }
    case 0x14D8:  { strcpy(message, "PlayerShotHit"); break; }
    case 0x1504:  { strcpy(message, "CodeBug1"); break; }
    case 0x1530:  { strcpy(message, "Player shot leaving playfield, hitting shield, or hitting an alien shot"); break; }
    case 0x1538:  { strcpy(message, "AExplodeTime"); break; }
    case 0x1554:  { strcpy(message, "Cnt16s"); break; }
    case 0x1562:  { strcpy(message, "FindRow"); break; }
    case 0x156F:  { strcpy(message, "FindColumn"); break; }
    case 0x1581:  { strcpy(message, "GetAlienStatPtr"); break; }
    case 0x1590:  { strcpy(message, "WrapRef"); break; }
    case 0x1597:  { strcpy(message, "RackBump"); break; }
    case 0x15D3:  { strcpy(message, "DrawSprite"); break; }
    case 0x15F3:  { strcpy(message, "CountAliens"); break; }
    case 0x1611:  { strcpy(message, "GetPlayerDataPtr"); break; }
    case 0x1618:  { strcpy(message, "PlrFireOrDemo"); break; }
    case 0x1652:  { strcpy(message, "Handle demo (constant fire, parse demo commands)"); break; }
    case 0x170E:  { strcpy(message, "AShotReloadRate"); break; }
    case 0x172C:  { strcpy(message, "ShotSound"); break; }
    case 0x1740:  { strcpy(message, "TimeFleetSound"); break; }
    case 0x1775:  { strcpy(message, "FleetDelayExShip"); break; }
    case 0x17B4:  { strcpy(message, "SndOffExtPly"); break; }
    case 0x17C0:  { strcpy(message, "ReadInputs"); break; }
    case 0x17CD:  { strcpy(message, "CheckHandleTilt"); break; }
    case 0x1804:  { strcpy(message, "CtrlSaucerSound"); break; }
    case 0x1815:  { strcpy(message, "DrawAdvTable"); break; }
    case 0x1856:  { strcpy(message, "ReadPriStruct"); break; }
    case 0x1868:  { strcpy(message, "SplashSprite"); break; }
    case 0x189E:  { strcpy(message, ";Animate alien shot to extra \"C\" in splash"); break; }

    case 0x18D4:  { strcpy(message, "INIT"); break; }
    case 0x18E7:  { strcpy(message, "Get player-alive flag for OTHER player"); break; }
    case 0x18FA:  { strcpy(message, "SoundBits3On"); break; }
    case 0x1904:  { strcpy(message, "InitAliensP2"); break; }
    case 0x190A:  { strcpy(message, "PlyrShotAndBump"); break; }
    case 0x1910:  { strcpy(message, "CurPlyAlive"); break; }
    case 0x191A:  { strcpy(message, "DrawScoreHead"); break; }
    case 0x1931:  { strcpy(message, "DrawScore"); break; }
    case 0x1947:  { strcpy(message, "DrawNumCredits"); break; }
    case 0x1950:  { strcpy(message, "PrintHiScore"); break; }
    case 0x1956:  { strcpy(message, "DrawStatus"); break; }
    case 0x199A:  { strcpy(message, "CheckHiddenMes"); break; }
    case 0x19BE:  { strcpy(message, "MessageTaito"); break; }
    case 0x19D1:  { strcpy(message, "EnableGameTasks"); break; }
    case 0x19D7:  { strcpy(message, "DsableGameTasks"); break; }
    case 0x19DC:  { strcpy(message, "SoundBits3Off"); break; }
    case 0x19E6:  { strcpy(message, "DrawNumShips"); break; }
    case 0x1A06:  { strcpy(message, "CompYToBeam"); break; }
    case 0x1A32:  { strcpy(message, "BlockCopy"); break; }
    case 0x1A3B:  { strcpy(message, "ReadDesc"); break; }
    case 0x1A47:  { strcpy(message, "ConvToScr"); break; }
    case 0x1A5C:  { strcpy(message, "ClearScreen"); break; }
    case 0x1A69:  { strcpy(message, "RestoreShields"); break; }
    case 0x1A7F:  { strcpy(message, "RemoveShip"); break; }

        // DATA
    case 0x1AA1:  { strcpy(message, "ShotReloadRate"); break; }
    case 0x1AA6:  { strcpy(message, "MessageGOver"); break; }
    case 0x1ABA:  { strcpy(message, "MessageB1or2"); break; }
    case 0x1ACF:  { strcpy(message, "Message1Only"); break; }
    case 0x1AE4:  { strcpy(message, "MessageScore"); break; }
    case 0x0082:  { strcpy(message, "Restore registers and out"); break; }
    default: { strcpy(message, ""); }
    }
}
