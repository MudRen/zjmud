// Room: /d/gaibang/hzandao1.c 
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
		"southeast" : __DIR__"hzandao2", 
		"northwest" : __DIR__"undertre", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
