//Room: majiu.c ���
#include <room.h>
inherit TRANS_ROOM;
void create()
{
	set("short", "���");
	set("long", @LONG
���Ǳ���С�����ǣ����깩Ӧ���ʲ��ϡ�����ش��Ὦ���������
���ÿͣ�������Զ�����������ֵܿ���������ǻ����ǣ����Ǻ����տ���
������ι�����㣬�����������ˬˬ��һֱ�ź򵽿�����·����Ǿ�ľ��
�϶���һ����ľ�ơ�
    ����жѷ������Ѳ��ϣ�������һ����ۡ�
LONG);
	set("outdoors", "xingxiu");
	set("no_fight", 1);
	set("objects", ([
		"/clone/horse/zaohongma": 1,
		"/clone/horse/huangbiaoma": 1,
		"/clone/horse/ziliuma": 1,
		"/clone/npc/mafu": 1,

	]));

	set("exits",([ /* sizeof() == 1 */
		"south"      : __DIR__"beijiang",
	]));
	setup();
	replace_program(TRANS_ROOM);
}
