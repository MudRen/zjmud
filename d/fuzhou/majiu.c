// Room: /d/suzhou/majiu.c
// Date: May,31 1998 Java

#include <room.h>
inherit TRANS_ROOM;

void create()
{
	set("short","����");
	set("long",@LONG
�����ų�������ǣ����깩Ӧ���ʲ��ϡ�������紾�ӣ�
�����ǻ����ǣ�����Ǻ����տ���������ι�����㣬��ϴˢ��
��Ǭ������һֱ�ź򵽿�����·�����������µ���ľ���϶���
һ����ľ��(paizi)��
    �����жѷ������Ѳ��ϣ�������һ����ۡ�
LONG);
	set("outdoors", "fuzhou");
	set("no_fight", 1);
	set("objects", ([
		"/clone/horse/zaohongma": 1,
		"/clone/horse/huangbiaoma": 1,
		"/clone/horse/ziliuma": 1,
		"/clone/npc/mafu": 1,
 
	]));
	set("exits",([ /* sizeof() == 1 */
		"south" : __DIR__"rongcheng",
	]));
	setup();
	replace_program(TRANS_ROOM);
}