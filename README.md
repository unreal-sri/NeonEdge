# **Hack-and-Slash Combat System (Unreal Engine C++)**  

**A modular, high-intensity combat system inspired by *Devil May Cry* and classic hack-and-slash games, built entirely in C++ for Unreal Engine.**  

[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)  
[![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5+-%23313131.svg)](https://www.unrealengine.com)  

---

## **🔥 Features**  
✔ **Combo-Based Combat** – Light/Heavy attacks, aerial launches, and juggle mechanics.  
✔ **Dynamic Camera System** – Smooth shifts on attacks, hit reactions, and rage-mode post-processing.  
✔ **Modular Design** – Easily extendable for new weapons, enemies, and abilities.  
✔ **Distance-Matched Locomotion** – Fluid start/stop animations with root motion blending.  
✔ **WIP Boss Fight** – Multi-phase enemy with adaptive AI (coming soon!).  

---

## **🚀 Getting Started**  
### **Prerequisites**  
- Unreal Engine 5.0+  
- Basic C++ knowledge  

### **Setup**  
1. Clone this repository into your UE5 project’s `Source` folder.  
2. Link the modules in your `.Build.cs` file.  
3. Derive from the base classes (e.g., `UCustomCombatComponent`).  

---

## **🎮 How It Works**  
### **Core Systems**  
- **Combat Flow:** Chain attacks into air combos using `UAnimMontage` and `UStateMachine`.  
- **Camera Logic:** `UCameraModifier` for dynamic framing during combat.  
- **Rage Mode:** Post-process materials and attack buffs via `UGameplayEffect`.  

### **Code Examples**  
```cpp  
// Trigger a launch attack  
void APlayerCharacter::PerformLaunchAttack()  
{  
    if (CombatComponent->CanLaunchEnemy())  
    {  
        PlayAnimMontage(LaunchMontage);  
        CombatComponent->ApplyHitReaction(EHitReactionType::KnockUp);  
    }  
}  
```  

---

## **📂 Project Structure**  
```  
/Source  
├── ActorComponents        # Core combat logic for both player and Enemies  
├── Characters             # Base classes for all kinds of enemies and a base class for player aswell  
├── Interfaces             # All the required interfaces to establish link between different classes
├── Controllers            # all the Enemy AI stuff is taken care of in a base Controller class that is responsible for setting all the variables of the blackboard component in the behaviour tree
├── AnimNotifies           # everything that has to happene in between a montage I have made few simpler AnimNotfies in the Blueprint but most of them are here in this folder 
└── Weapons                # Weapons are seperate actors so that I can easily create different typpes of weapons with similar functionality all deriving from same base class
  
```  

---

## **📜 License**  
MIT License – Use freely, but credit appreciated!  

---

## **💡 Contributing**  
Open to PRs for:  
- New weapon types (whips, dual blades).  
- Enhanced camera effects.  
- Boss fight mechanics!  

**Let’s make combat feel legendary!** ⚔️  

--- 

*(Note: This repo contains only C++ code—no UE project files or assets.)*  

---

### **Why This Stands Out**  
- **Clean, documented C++** for easy integration.  
- **Performance-first** (no tick-heavy logic).  
- Built for **community reuse**—adapt it to your game!  

**Star ⭐ if you find it useful!**  

--- 

Need help? DM me on [LinkedIn](https://linkedin.com/in/srijan-giri-584688296).
 
