// Room: /d/gaibang/undergw.c 
// Date: jeeny 2001.5	     
#include <room.h> 
inherit ROOM; 
      
void create() 
{ 
	set("short", "С������"); 
	set("long", @LONG 
���ǹ���С���ݵ��µ�С���������������õģ������˸������
����ؤ������ռ�����ͭ�����ȡ�������ͨ��ؤ�������ͨ���� 
LONG 
	); 
	set("exits", ([ 
		"out"       : "/d/guanwai/tuwu", 
		"southwest" : __DIR__"gwandao2", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
