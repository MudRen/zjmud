// Room: /d/gaibang/fsandao1.c 
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
		"northeast" : __DIR__"undertre", 
		"southwest" : __DIR__"fsandao2", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
