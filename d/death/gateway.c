// Room: /d/death/gateway.c

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
	set("short", "ۺ������");
	set("long", @LONG
����������һ����ɫ��¥֮ǰ����¥�Ͽ����������֣�ۺ���ǡ���
�ϲ�Զ����һ���ţ����Ϲ�Ӱ����������ȴ��������������������߽�
��¥ֻ��һƬ������ģ�ֻ��������ɫ�Ļ���������ֵ���˸����
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		"north" : "/d/death/road1",
		"south" : "/d/death/gate",
	]));
	set("objects", ([
		__DIR__"npc/bgargoyle": 1
	]) );

	set("no_fight", 1);
	set("no_sleep_room", 1);

	setup();
}
