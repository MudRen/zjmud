// Room: /d/gaibang/wgandao1.c 
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
		"southwest" : __DIR__"wgandao2", 
		"northeast" : __DIR__"undertre", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
