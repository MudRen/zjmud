// Room: /d/gaibang/hzandao2.c 
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
		"southeast" : __DIR__"underhz", 
		"northwest" : __DIR__"hzandao1", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
