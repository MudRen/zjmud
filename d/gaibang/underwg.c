// Room: /d/gaibang/underwg.c 
// Date: jeeny 2001.	     
#include <room.h> 
inherit ROOM; 
      
void create() 
{ 
	set("short", "土地庙下"); 
	set("long", @LONG 
这是武功镇土地庙下的小洞。里面破破烂烂的，丢满了各种杂物，
还有丐帮弟子收集的破铜烂铁等。从这里通往丐帮的秘密通道。 
LONG 
	); 
	set("exits", ([ 
		"out"       : "/d/quanzhen/xiaomiao", 
		"northeast" : __DIR__"wgandao2", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
