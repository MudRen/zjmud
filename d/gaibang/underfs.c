// Room: /d/gaibang/underfs.c 
// Date: jeeny 2001.5	     
#include <room.h> 
inherit ROOM; 
      
void create() 
{ 
	set("short", "��������"); 
	set("long", @LONG 
���Ƿ�ɽ��������µ�С���������������õģ������˸������
����ؤ������ռ�����ͭ�����ȡ�������ͨ��ؤ�������ͨ���� 
LONG 
	); 
	set("exits", ([ 
		"out"       : "/d/foshan/beidimiao", 
		"northeast" : __DIR__"fsandao2", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
