//Room: majiu1.c ���
#include <room.h>
inherit TRANS_ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
���Ǳ����ǵ���ǣ����깩Ӧ���ʲ��ϡ������Թ����ӽ��£�ɶ����
��أ��͵�Ҳ�ػ��ź��ˣ�����ǻ����ǣ����Ǻ����տ���������ι��
���㣬��ϴˢ�ø�Ǭ������һֱ�ź򵽿�����·����������µ���ľ����
����һ����ľ�ơ�
    ����жѷ������Ѳ��ϣ�������һ����ۡ�
LONG);
	set("outdoors", "beijing");
	set("no_fight", 1);
	set("objects", ([
		"/clone/horse/zaohongma": 1,
		"/clone/horse/huangbiaoma": 1,
		"/clone/horse/ziliuma": 1,
		"/clone/npc/mafu": 1,
	       
	]));
	set("exits",([ /* sizeof() == 1 */
		"east"      : __DIR__"niaoshi",
	]));

	setup();
	replace_program(TRANS_ROOM);
}
