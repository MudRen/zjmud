// Room: /d/gaibang/underlz.c 
// Date: jeeny 2001.5	     
#include <room.h> 
inherit ROOM; 
      
void create() 
{ 
	set("short", "������"); 
	set("long", @LONG 
�����������д����µ�С���������������õģ������˸������
����ؤ������ռ�����ͭ�����ȡ�������ͨ��ؤ�������ͨ���� 
LONG 
	); 
	set("exits", ([ 
		"out"       : "/d/lingzhou/dawu", 
		"southeast" : __DIR__"lzandao2", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
