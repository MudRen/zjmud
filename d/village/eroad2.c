// Room: /d/village/eroad2.c

inherit ROOM;

void create()
{
	set("short", "��ʯ·");
	set("long", @LONG
����һ��������С���ӣ�ϡϡ����ķֲ��ż�ʮ�������෿��������
���˼Ҳ��࣬���Ҵ�����ܼ���������һ�����������ʯ·�������Ǽ�
��ʵ����լ��
LONG );
	set("exits", ([ /* sizeof() == 3 */
	    "east"  : __DIR__"eroad1",
	    "west"  : __DIR__"eroad3",
	    "north" : __DIR__"ehouse2",
	]));

	set("outdoors", "village");

	setup();
}

