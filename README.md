﻿<h1>SlashTheTrash</h1>
Unreal Engine 5.3 project with an implementation of <b>replicated combo system</b> with <b>Gameplay Ability System (GAS)</b> 
<h2>Character and abilities</h2>
Base Character has default movement and <b>3 types of abilities</b>:
<ul>
<li>Combo attacks (normal and hard)</li>
<li>Skill ability</li>
<li>Ultimate ability</li>
</ul>
<b>Combo attacks</b> deal damage to a target ability system component with a gameplay effect, restoring energy for Ultimate ability. <b>Skill ability</b> applies a gameplay effect to a target. Has a cooldown. <b>Ultimate ability</b> works like skill ability but has a cost. Each ability is easy to override in blueprints for game designers.
<h2>Data</h2>
Character's abilities, default stats as a struct, and animations are stored in <b>DataAssets</b>. Default stats applies with a gameplay effect with SetByCaller. Abilities are given in the initializing ability system component function on the server (PossessedBy) and clients (OnRep_PlayerState). Animation blueprint uses DataAssets for setting a movement blendspace, idle, death and damage animations.
<h2>User Interface</h2>
Connection between UI and Character is provided by <b>WidgetControllers</b> as an Observer. WidgetController is an UObject that has params such as AbilitySystemComponent, AttributeSet, PlayerState, PlayerController, and delegates. UserWidgets assigns to the delegates, and WidgetController broadcasts these delegates on param's changes.
