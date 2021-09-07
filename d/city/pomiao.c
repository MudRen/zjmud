// Room: /city/pomiao.c	
#include <room.h> 
inherit ROOM; 
	
void create() 
{ 
	set("short", "������"); 
	set("long", @LONG 
����һ���������õ������������ưܲ�����������������һ�ԣ����ϵ� 
��Ҳ�����˻ҳ���һ����֪���Ѿ��ܾ�û������������ˡ����з��Ÿ����㰸�� 
�������ҵ����ż�����ʣ�����ļ���ͷ��Ҳ��������Ϊ���ε�ԭ��ɣ���˵ؤ 
�ｭ�Ϸֶ�ͱ����ڴ˴��� 
LONG 
	); 
	set("valid_startroom", 1); 
	set("exits", ([ 
		"west"  : "/d/gaibang/shoushe", 
		"east"  : "/d/gaibang/sheyuan", 
		"south" : __DIR__"ml4",
		"enter" : __DIR__"gbandao",		      
	])); 
	set("objects", ([ 
		CLASS_D("gaibang") + "/lu" : 1, 
		CLASS_D("gaibang") + "/peng" : 1,
		CLASS_D("gaibang") + "/xi" : 1, 
	])); 
	create_door("enter", "С��", "out", DOOR_CLOSED); 
	setup(); 
} 

int valid_leave(object me, string dir) 
{ 
	object ob; 
	mapping myfam; 
       
	myfam = me->query("family"); 
       
	if ((! mapp(myfam) || myfam["family_name"] != "ؤ��") && 
	    (dir == "west" || dir == "east") && 
	    objectp(ob = present("lu youjiao", environment(me))) && 
	    living(ob)) 
	{ 
		return notify_fail("³�н���ס��˵���˴���" 
				   "������أ���ֹ����\n"); 
	} 
       
	return ::valid_leave(me, dir); 
} 

