// Room: /d/gaibang/gwandao2.c 
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
		"northeast" : __DIR__"undergw", 
		"southwest" : __DIR__"gwandao1", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
