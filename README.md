sandbox-sdk
===========

A software development kit used to create plugins and dependencies for sandbox, inspired by bakkesmod.

Documentation
-------------

#### Hooking


| HookType | Function
| -------- | --------
| PE       | ```ProcessEvent(class UObject*, class UFunction*, void*, void*)```
| PI       | ```ProcessInternal(class UObject*, FFrame&, void*)```
| CF       | ```CallFunction(class UObject*, FFrame&, void*, class UFunction*)```


```c++
#include "path/to/unclass.h"

// hooking function signature
void function(UObject* caller, UFunction* function, void* params) {}
```


```c++
#include "path/to/hooking.h"

void Plugin::load()
{
    // hook a pre function
    Hooking::hook_function("Function Engine.Interaction.Tick", Hooking::HookType::PE, &function);
    // hook a post function
    Hooking::hook_function_post("Function Engine.Interaction.Tick", Hooking::HookType::PE, &function);
}

void Plugin::unload()
{
    // unhook pre and post function
    Hooking::unhook_function("Function Engine.Interaction.Tick", Hooking::HookType::PE, &function);
}
```

#### Unreal Structs

```c++
#include "path/to/unstruct.h"

// ScriptStruct Core.Object.LinearColor
struct LinearColor
{
	float R;
	float G;
	float B;
	float A;
};

// create a new struct
UnStruct linear_color = UnStruct("LinearColor");
// get a field value
float red = linear_color.get<float>("R");
// set a field value
linear_color.get<float>("G") = 1.0f;
```

#### Unreal Objects

```c++
#include "path/to/unstruct.h"

// Class Engine.Actor
class Actor : public UObject
{
public:
    TArray<class ActorComponent*> Components; // 0x0070
	struct Vector Location;                   // 0x0090
	float DrawScale;                          // 0x00A8
	TArray<struct TimerData> Timers;          // 0x00E8
};

// Function TAGame.Car_TA.OnJumpPressed
void function(UObject* caller, UFunction* function, void* params)
{
    UObject* car = caller;
    
    if (car)
    {
        // *you can get and set object field values*
        
        // get a object field
        float draw_scale = car->get_field<float>("DrawScale");
        // set a object field
        draw_scale = 0.5f;
        
        // get a object field struct
        UnStruct location = car->get_struct_field("Vector", "Location");
        // set a object field struct
        location.get<float>("X") = 20.f;
        
        // get a object field array
        TArray<UObject*> components = car->get_field<TArray<UObject*>>("Components");
        // set a object field array data
        components.at(0) = car;
        
        // get a object field array struct
        UnArrayStruct timers = car->get_field<UnArrayStruct>("Timers");
        // get a object field array struct data
        UnStruct timer = timers.at("TimerData", 0);
        
    }
}
```

#### Unreal Functions

```c++
#include "path/to/unfunc.h"

bool IsBumperHit(class Car_TA* OtherCar, struct Vector HitLocation, struct Vector HitNormal);

// Function TAGame.Car_TA.IsBumperHit
void function(UObject* caller, UFunction* function, void* params)
{
    // get the function params
    UnFuncParams func_params = UnFuncParams(function, params);
    // get a field in the param
    func_params.get<UObject*>("OtherCar");
    // get a struct field in the param
    UnStruct hit_location = func_params.get_struct("Vector", "HitLocation");
    // set a param value
    func_params.get_struct("Vector", "HitNormal").get<float>("X") = 0.0f;
    
    if (caller)
    {
        // calling a function
        // void SetCarScale(float NewScale);
        float scale = 0.5f;
        caller->call_function("TAGame.Car_TA.SetCarScale", UnParams({ &scale }));
        
        // calling a function and getting a return value
        // int32_t GetLoadoutTeamIndex();
        UnFunc func = caller->call_function("TAGame.Car_TA.GetLoadoutTeamIndex", UnParams({}));
        int32_t ret = func.get_ret<int>();
    }
}
```

#### Example Plugin

```c++
#include "path/to/unstruct.h"
#include "path/to/unfunc.h"
#include "path/to/hooking.h"

// function hook to remove the timestamp on a chat message
void disable_timestamp(UObject* caller, UFunction* function, void* params)
{
	UnFuncParams func_params = UnFuncParams(function, params);

	UnStruct chat_message = func_params.get_struct("ChatMessage", "Message");

	FString chat = FString();

	chat_message.get<FString>("TimeStamp") = chat;
}

// on plugin load
void DisableTimestamp::load()
{
	Hooking::hook_function("Function TAGame.HUDBase_TA.EventChatMessage", Hooking::HookType::CF, &disable_timestamp);
}

// on plugin unload
void DisableTimestamp::unload()
{
	Hooking::unhook_function("Function TAGame.HUDBase_TA.EventChatMessage", Hooking::HookType::CF, &disable_timestamp);
}

// register plugin
SANDBOX_PLUGIN(DisableTimestamp)
```