// Room: /d/gaibang/underhz.c 
// Date: jeeny 2001.5	     
#include <room.h> 
inherit ROOM; 
      
void create() 
{ 
	set("short", "��������"); 
	set("long", @LONG 
���Ǻ��������ŵ��µ�С���������������õģ������˸������
����ؤ������ռ�����ͭ�����ȡ�������ͨ��ؤ�������ͨ���� 
LONG 
	); 
	set("exits", ([ 
		"out"       : "/d/hangzhou/xilingqiao", 
		"northwest" : __DIR__"hzandao2", 
	])); 
	set("no_clean_up", 0); 
	setup(); 
} 
