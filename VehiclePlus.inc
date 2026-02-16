
/*
    Created by devbluen
    Repo: https://github.com/devbluen/VehiclePlus
*/

#if defined VehiclePlus_included
	#endinput
#endif
#define VehiclePlus_included

            // Definers
#define         MAX_VEHICLE_PLATE       (18)

            // Forwards
forward OnVehicleConnect(vehicleid);
forward OnVehicleDisconnect(vehicleid);
forward OnVehicleColorUpdate(vehicleid, color1, color2);
forward OnVehiclePlateUpdate(vehicleid, const newplate[]);
            //
forward OnVehicleBonnetUpdate(vehicleid, bool:status);  // Capô
forward OnVehicleBootUpdate(vehicleid, bool:status);  // Porta Malas
forward OnVehicleEngineUpdate(vehicleid, bool:status);
forward OnVehicleDoorsUpdate(vehicleid, bool:status);
forward OnVehicleLightsUpdate(vehicleid, bool:status);
forward OnVehicleAlarmUpdate(vehicleid, bool:status);

static enum E_VEHICLE_PLUS {
    E_VEHICLE_PLATE[MAX_VEHICLE_PLATE + 1],
    E_VEHICLE_COLOR_1,
    E_VEHICLE_COLOR_2,
    E_VEHICLE_RESPAWN_DELAY,
    bool:E_VEHICLE_SIREN,
    Float:E_VEHICLE_SPAWNPOINT[4],

    // Params
    bool:E_VEHICLE_ENGINE,
    bool:E_VEHICLE_LIGHTS,
    bool:E_VEHICLE_ALARM,
    bool:E_VEHICLE_DOORS,
    bool:E_VEHICLE_BONNET,  // Capô [PT-BR]
    bool:E_VEHICLE_BOOT     // Porta Malas [PT-BR]
};

static 
    e_VehiclePlus[MAX_VEHICLES][E_VEHICLE_PLUS]
;

static const 
    VehTopSpeed[212] = {
        157, 147, 186, 110, 133, 164, 110, 148, 100, 158, 129, 221, 168, 110, 105, 192, 154, 270,
        115, 149, 145, 154, 140, 99, 135, 270, 173, 165, 157, 201, 190, 130, 94, 110, 167, 0, 149,
        158, 142, 168, 136, 145, 139, 126, 110, 164, 270, 270, 111, 0, 0, 193, 270, 60, 135, 157,
        106, 95, 157, 136, 270, 160, 111, 142, 145, 145, 147, 140, 144, 270, 157, 110, 190, 190,
        149, 173, 270, 186, 117, 140, 184, 73, 156, 122, 190, 99, 64, 270, 270, 139, 157, 149, 140,
        270, 214, 176, 162, 270, 108, 123, 140, 145, 216, 216, 173, 140, 179, 166, 108, 79, 101, 270,
        270, 270, 120, 142, 157, 157, 164, 270, 270, 160, 176, 151, 130, 160, 158, 149, 176, 149, 60,
        70, 110, 167, 168, 158, 173, 0, 0, 270, 149, 203, 164, 151, 150, 147, 149, 142, 270, 153, 145,
        157, 121, 270, 144, 158, 113, 113, 156, 178, 169, 154, 178, 270, 145, 165, 160, 173, 146, 0, 0,
        93, 60, 110, 60, 158, 158, 270, 130, 158, 153, 151, 136, 85, 0, 153, 142, 165, 108, 162, 0, 0,
        270, 270, 130, 190, 175, 175, 175, 158, 151, 110, 169, 171, 148, 152, 0, 0, 0, 108, 0, 0
    }
;



/*

                    ooooooooo.   ooooo     ooo oooooooooo.  ooooo        ooooo   .oooooo.   
                    `888   `Y88. `888'     `8' `888'   `Y8b `888'        `888'  d8P'  `Y8b  
                    888   .d88'  888       8   888     888  888          888  888          
                    888ooo88P'   888       8   888oooo888'  888          888  888          
                    888          888       8   888    `88b  888          888  888          
                    888          `88.    .8'   888    .88P  888       o  888  `88b    ooo  
                    o888o           `YbodP'    o888bood8P'  o888ooooood8 o888o  `Y8bood8P'  

*/

public OnVehicleStreamIn(vehicleid, forplayerid) {
    SetVehicleFixParams(vehicleid, forplayerid);

    #if defined HOOK_OnVehicleStreamIn
       return HOOK_OnVehicleStreamIn(vehicleid, forplayerid);
    #else 
        return true;
    #endif
}



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock alsCreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, bool:addsiren = false) {
    new vehicleid = CreateVehicle(vehicletype, x, y, z, rotation, color1, color2, respawn_delay, addsiren);
    CreateVehicle_ConfigData(vehicleid, x, y, z, rotation, color1, color2, respawn_delay, addsiren);
    return vehicleid;
}

stock alsAddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2) {
    new vehicleid = AddStaticVehicle(modelid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2);
    CreateVehicle_ConfigData(vehicleid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2);
    return vehicleid;
}

stock alsAddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay, bool:addsiren = false) {
    new vehicleid = AddStaticVehicleEx(modelid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2, respawn_delay, addsiren);
    CreateVehicle_ConfigData(vehicleid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2, respawn_delay, addsiren);
    return vehicleid;
}

stock alsDestroyVehicle(vehicleid) {

    CallLocalFunction("OnVehicleDisconnect", "i", vehicleid);

    static const e_Clear[E_VEHICLE_PLUS];
    e_VehiclePlus[vehicleid] = e_Clear;
    return DestroyVehicle(vehicleid);
}

stock alsChangeVehicleColor(vehicleid, color1, color2) {

    color1 = color1 == -1 ? e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_1] : color1;
    color2 = color2 == -1 ? e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_2] : color2;

    e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_1] = color1;
    e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_2] = color2;

    CallLocalFunction("OnVehicleColorUpdate", "iii", vehicleid, color1, color2);
    return ChangeVehicleColor(vehicleid, color1, color2);
}

stock alsSetVehicleNumberPlate(vehicleid, const numberplate[]) {
    format(e_VehiclePlus[vehicleid][E_VEHICLE_PLATE], MAX_VEHICLE_PLATE, numberplate);

    CallLocalFunction("OnVehiclePlateUpdate", "is", vehicleid, numberplate);
    return SetVehicleNumberPlate(vehicleid, numberplate);
}



/*

                    oooooooooooo oooooooooooo       .o.       ooooooooooooo ooooo     ooo ooooooooo.   oooooooooooo  .oooooo..o 
                    `888'     `8 `888'     `8      .888.      8'   888   `8 `888'     `8' `888   `Y88. `888'     `8 d8P'    `Y8 
                    888          888             .8"888.          888       888       8   888   .d88'  888         Y88bo.      
                    888oooo8     888oooo8       .8' `888.         888       888       8   888ooo88P'   888oooo8     `"Y8888o.  
                    888    "     888    "      .88ooo8888.        888       888       8   888`88b.     888    "         `"Y88b 
                    888          888       o  .8'     `888.       888       `88.    .8'   888  `88b.   888       o oo     .d8P 
                    o888o        o888ooooood8 o88o     o8888o     o888o        `YbodP'    o888o  o888o o888ooooood8 8""88888P'  

*/

stock GetVehiclePlate(vehicleid) {
    new string[MAX_VEHICLE_PLATE + 1];
    strcat(string, e_VehiclePlus[vehicleid][E_VEHICLE_PLATE]);
    return string;
}

stock SetVehicleColor(vehicleid, color1, color2) {
    alsChangeVehicleColor(vehicleid, color1, color2);
}

stock alsGetVehicleColor(vehicleid, &color1, &color2 = 0) {

    color1 = e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_1];
    color2 = e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_2];
}

stock SetVehicleMotor(vehicleid, bool:status) {SetVehicleEngine(vehicleid, status);}
stock SetVehicleEngine(vehicleid, bool:status) {
    if(e_VehiclePlus[vehicleid][E_VEHICLE_ENGINE] == status)
        return;

    e_VehiclePlus[vehicleid][E_VEHICLE_ENGINE] = status;
    CallLocalFunction("OnVehicleEngineUpdate", "ii", vehicleid, status);
    SetVehicleFixParams(vehicleid);  
}

stock SetVehiclePorta(vehicleid, bool:status) {SetVehicleDoorLock(vehicleid, status);}
stock SetVehicleDoorLock(vehicleid, bool:status) {
    if(e_VehiclePlus[vehicleid][E_VEHICLE_DOORS] == status)
        return;

    e_VehiclePlus[vehicleid][E_VEHICLE_DOORS] = status;
    CallLocalFunction("OnVehicleDoorsUpdate", "ii", vehicleid, status);
    SetVehicleFixParams(vehicleid);
}

stock SetVehicleLuz(vehicleid, bool:status) {SetVehicleLights(vehicleid, status);}
stock SetVehicleLights(vehicleid, bool:status) {
    if(e_VehiclePlus[vehicleid][E_VEHICLE_LIGHTS] == status)
        return;

    e_VehiclePlus[vehicleid][E_VEHICLE_LIGHTS] = status;
    CallLocalFunction("OnVehicleLightsUpdate", "ii", vehicleid, status);
    SetVehicleFixParams(vehicleid);    
}

stock SetVehicleAlarme(vehicleid, bool:status) {SetVehicleAlarm(vehicleid, status);}
stock SetVehicleAlarm(vehicleid, bool:status) {
    if(e_VehiclePlus[vehicleid][E_VEHICLE_ALARM] == status)
        return;

    e_VehiclePlus[vehicleid][E_VEHICLE_ALARM] = status;
    CallLocalFunction("OnVehicleAlarmUpdate", "ii", vehicleid, status);
    SetVehicleFixParams(vehicleid);       
}

stock SetVehicleCapo(vehicleid, bool:status) {SetVehicleBonnet(vehicleid, status);}
stock SetVehicleBonnet(vehicleid, bool:status) {
    if(e_VehiclePlus[vehicleid][E_VEHICLE_BONNET] == status)
        return;

    e_VehiclePlus[vehicleid][E_VEHICLE_BONNET] = status;
    CallLocalFunction("OnVehicleBonnetUpdate", "ii", vehicleid, status);
    SetVehicleFixParams(vehicleid);     
}

stock SetVehiclePortaMalas(vehicleid, bool:status) {SetVehicleBoot(vehicleid, status);}
stock SetVehicleBoot(vehicleid, bool:status) {
    if(e_VehiclePlus[vehicleid][E_VEHICLE_BOOT] == status)
        return;

    e_VehiclePlus[vehicleid][E_VEHICLE_BOOT] = status;
    CallLocalFunction("OnVehicleBootUpdate", "ii", vehicleid, status);
    SetVehicleFixParams(vehicleid);     
}

stock bool:GetVehicleStatusEngine(vehicleid) return (e_VehiclePlus[vehicleid][E_VEHICLE_ENGINE]);
stock bool:GetVehicleStatusMotor(vehicleid) return GetVehicleStatusEngine(vehicleid);

stock bool:GetVehicleStatusDoor(vehicleid) return (e_VehiclePlus[vehicleid][E_VEHICLE_DOORS]);
stock bool:GetVehicleStatusPorta(vehicleid) return GetVehicleStatusDoor(vehicleid);

stock bool:GetVehicleStatusLight(vehicleid) return (e_VehiclePlus[vehicleid][E_VEHICLE_LIGHTS]);
stock bool:GetVehicleStatusLuz(vehicleid) return GetVehicleStatusLight(vehicleid);

stock bool:GetVehicleStatusAlarm(vehicleid) return (e_VehiclePlus[vehicleid][E_VEHICLE_ALARM]);
stock bool:GetVehicleStatusAlarme(vehicleid) return GetVehicleStatusAlarm(vehicleid);

stock bool:GetVehicleStatusBonnet(vehicleid) return (e_VehiclePlus[vehicleid][E_VEHICLE_BONNET]);
stock bool:GetVehicleStatusCapo(vehicleid) return GetVehicleStatusBonnet(vehicleid);

stock bool:GetVehicleStatusBoot(vehicleid) return (e_VehiclePlus[vehicleid][E_VEHICLE_BONNET]);
stock bool:GetVehicleStatusPortaMalas(vehicleid) return GetVehicleStatusBoot(vehicleid);

static stock SetVehicleFixParams(vehicleid, playerid = INVALID_PLAYER_ID) {

    if(playerid == INVALID_PLAYER_ID) SetVehicleParamsEx(vehicleid, 
                                                            e_VehiclePlus[vehicleid][E_VEHICLE_ENGINE], 
                                                            e_VehiclePlus[vehicleid][E_VEHICLE_LIGHTS], 
                                                            e_VehiclePlus[vehicleid][E_VEHICLE_ALARM], 
                                                            e_VehiclePlus[vehicleid][E_VEHICLE_DOORS], 
                                                            e_VehiclePlus[vehicleid][E_VEHICLE_BONNET], 
                                                            e_VehiclePlus[vehicleid][E_VEHICLE_BOOT], 
                                                            false);
    else SetVehicleParamsForPlayer(vehicleid, playerid, false, e_VehiclePlus[vehicleid][E_VEHICLE_DOORS]);
}

static stock CreateVehicle_ConfigData(vehicleid, Float:x, Float:y, Float:z, Float:a, color1, color2, respawn_delay = 0, bool:addsiren = false) {

    color1 = color1 == -1 ? random(999) : color1;
    color2 = color2 == -1 ? random(999) : color2;

    e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_1] = color1;
    e_VehiclePlus[vehicleid][E_VEHICLE_COLOR_2] = color2;
    e_VehiclePlus[vehicleid][E_VEHICLE_RESPAWN_DELAY] = respawn_delay;
    e_VehiclePlus[vehicleid][E_VEHICLE_SIREN] = addsiren;
    
    e_VehiclePlus[vehicleid][E_VEHICLE_SPAWNPOINT][0] = x;
    e_VehiclePlus[vehicleid][E_VEHICLE_SPAWNPOINT][1] = y;
    e_VehiclePlus[vehicleid][E_VEHICLE_SPAWNPOINT][2] = z;
    e_VehiclePlus[vehicleid][E_VEHICLE_SPAWNPOINT][3] = a;

    CallLocalFunction("OnVehicleConnect", "i", vehicleid);   
}

stock IsVehicleFlyingVehicle(modelid) {

    switch(modelid) {
        case 592, 577, 511, 512, 593, 520, 553, 476, 519, 460, 513, 548, 425, 417, 487, 488, 497, 563, 447, 469: return true;
    }
    return false;
}

stock IsVehicleBoat(modelid) {

    switch(modelid) {
        case 472, 473, 493, 484, 430, 453, 452, 446, 454, 595: return true;
    }
    return false;
}

stock IsVehicleBike(modelid) {
    
    switch(modelid) {
        case 481, 509, 510: return true;
    }
    return false;
}

stock IsVehicleMotorcycle(modelid) {

    switch(modelid) {
        case 461, 462, 448, 522, 581, 521, 523, 463, 586, 468, 471: return true;
    }
    return false;
}

stock IsVehicleTruck(modelid) {

    switch(modelid) {
        case 403, 406, 407, 408, 414, 416, 427, 433, 443, 455, 456, 498, 508, 514, 515, 524, 573, 578, 428: return true;
    }
    return false;
}

stock IsVehicleBus(modelid) {

    switch(modelid) {
        case 431, 437: return true;
    }
    return false;
}

stock IsVehicleHelicopter(modelid) {

    switch(modelid) {
        case 425, 469, 487, 488, 497, 548, 563: return true;
    }
    return false;
}

stock IsVehicleTrain(modelid) {

    switch(modelid) {
        case 538, 537, 449, 570: return true;
    }
    return false;
}

stock bool:IsVehicleLand(modelid)
    return !IsVehicleBoat(modelid) && !IsVehicleFlyingVehicle(modelid) && !IsVehicleBike(modelid);

stock bool:IsVehicleCar(modelid) 
    return !IsVehicleBoat(modelid) && !IsVehicleFlyingVehicle(modelid) && !IsVehicleBike(modelid) && !IsVehicleMotorcycle(modelid);

stock GetVehicleTopSpeed(vehicleid)
    return GetVehicleTopSpeedModel(GetVehicleModel(vehicleid));   


stock GetVehicleTopSpeedModel(model) {
    if(model) 
        return VehTopSpeed[(model - 400)];

    return 0;
}



/*

                    ooo        ooooo       .o.         .oooooo.   ooooooooo.     .oooooo.    .oooooo..o 
                    `88.       .888'      .888.       d8P'  `Y8b  `888   `Y88.  d8P'  `Y8b  d8P'    `Y8 
                    888b     d'888      .8"888.     888           888   .d88' 888      888 Y88bo.      
                    8 Y88. .P  888     .8' `888.    888           888ooo88P'  888      888  `"Y8888o.  
                    8  `888'   888    .88ooo8888.   888           888`88b.    888      888      `"Y88b 
                    8    Y     888   .8'     `888.  `88b    ooo   888  `88b.  `88b    d88' oo     .d8P 
                    o8o        o888o o88o     o8888o  `Y8bood8P'  o888o  o888o  `Y8bood8P'  8""88888P'  

*/

#if defined _ALS_CreateVehicle
    #undef CreateVehicle
#else
    #define _ALS_CreateVehicle
#endif
 
#define CreateVehicle alsCreateVehicle

#if defined _ALS_AddStaticVehicle
    #undef AddStaticVehicle
#else
    #define _ALS_AddStaticVehicle
#endif
 
#define AddStaticVehicle alsAddStaticVehicle

#if defined _ALS_AddStaticVehicleEx
    #undef AddStaticVehicleEx
#else
    #define _ALS_AddStaticVehicleEx
#endif
 
#define AddStaticVehicleEx alsAddStaticVehicleEx

#if defined _ALS_ChangeVehicleColor
    #undef ChangeVehicleColor
#else
    #define _ALS_ChangeVehicleColor
#endif
 
#define ChangeVehicleColor alsChangeVehicleColor

#if defined _ALS_SetVehicleNumberPlate
    #undef SetVehicleNumberPlate
#else
    #define _ALS_SetVehicleNumberPlate
#endif
 
#define SetVehicleNumberPlate alsSetVehicleNumberPlate

#if defined _ALS_DestroyVehicle
    #undef DestroyVehicle
#else
    #define _ALS_DestroyVehicle
#endif
 
#define DestroyVehicle alsDestroyVehicle

#if defined _ALS_GetVehicleColor
    #undef GetVehicleColor
#else
    #define _ALS_GetVehicleColor
#endif
 
#define GetVehicleColor alsGetVehicleColor

#if defined _ALS_OnVehicleStreamIn
    #undef OnVehicleStreamIn
#else
    #define _ALS_OnVehicleStreamIn
#endif
#define OnVehicleStreamIn HOOK_OnVehicleStreamIn
#if defined HOOK_OnVehicleStreamIn
    forward HOOK_OnVehicleStreamIn(vehicleid, forplayerid); 
#endif 
