// Room: /d/gaibang/undercd.c 
// Date: jeeny 2001.5	     
#include <room.h> 
inherit ROOM; 
      
void create() 
{ 
	set("short", "�������"); 
	set("long", @LONG 
���ǳɶ���������µ�С���������������õģ������˸������
����ؤ������ռ�����ͭ�����ȡ�������ͨ��ؤ�������ͨ���� 
LONG 
	); 
	set("exits", ([ 
		"out"       : "/d/city3/wuhouci", 
		"northeast" : __DIR__"cdandao2", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
