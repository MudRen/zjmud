// Room: /d/gaibang/lzandao1.c 
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
		"northwest" : __DIR__"lzandao2", 
		"southeast" : __DIR__"undertre", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
