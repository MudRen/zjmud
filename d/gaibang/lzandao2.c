// Room: /d/gaibang/lzandao2.c 
// Date: jeeny 2001.5	 
#include <room.h> 
inherit ROOM; 
	
void create() 
{ 
	set("short", "����"); 
	set("long", @LONG 
����ؤ�Ｋ�����ܵĵ���ͨ��������ؤ�Ｘ����֮��Ѫ��ɡ�  
LONG 
	); 
	set("exits", ([ 
		"northwest" : __DIR__"underlz", 
		"southeast" : __DIR__"lzandao1", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
