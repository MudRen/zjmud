// Room: /d/gaibang/underwg.c 
// Date: jeeny 2001.	     
#include <room.h> 
inherit ROOM; 
      
void create() 
{ 
	set("short", "��������"); 
	set("long", @LONG 
�����书���������µ�С���������������õģ������˸������
����ؤ������ռ�����ͭ�����ȡ�������ͨ��ؤ�������ͨ���� 
LONG 
	); 
	set("exits", ([ 
		"out"       : "/d/quanzhen/xiaomiao", 
		"northeast" : __DIR__"wgandao2", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
