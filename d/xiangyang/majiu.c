// Room: /d/xiangyang/majiu.c ���
#include <room.h>
inherit TRANS_ROOM;
void create()
{
	set("short","���");
	set("long",@LONG
��������������Ψһһ�ҳ����С���ɻ�Ǯ����������
���ط�ȥ���ܽ�Լ����������������Ϊ������----����������
֯�����Ĵ��Ѽ����ǲ��ϣ���������Ӧ������ṩ�Ƴ�����
�͸��ַ��ǲ��ϡ�
    ������������µ���ľ���϶���һ����ľ�ơ�
LONG);
	set("outdoors", "xiangyang");
	set("no_fight", 1);
	set("objects", ([
		"/clone/horse/zaohongma": 1,
		"/clone/horse/huangbiaoma": 1,
		"/clone/horse/ziliuma": 1,
		"/clone/npc/mafu": 1,

	]));

	set("exits",([ /* sizeof() == 1 */
		"south"  : __DIR__"northroad2",
	]));

	setup();
	replace_program(TRANS_ROOM);
}
