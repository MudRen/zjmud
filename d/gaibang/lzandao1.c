// Room: /d/gaibang/lzandao1.c 
// Date: jeeny 2001.5	 
#include <room.h> 
inherit ROOM; 
	
void create() 
{ 
	set("short", "暗道"); 
	set("long", @LONG 
这是丐帮极其秘密的地下通道，乃用丐帮几辈人之心血掘成。  
LONG 
	); 
	set("exits", ([ 
		"northwest" : __DIR__"lzandao2", 
		"southeast" : __DIR__"undertre", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
