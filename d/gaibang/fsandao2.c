// Room: /d/gaibang/fsandao2.c 
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
		"northeast" : __DIR__"fsandao1", 
		"southwest" : __DIR__"underfs", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
