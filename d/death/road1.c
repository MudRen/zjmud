// Room: /d/death/road1.c

inherit ROOM;

void create()
{
	set("short", "���Ŵ��");
	set("long", @LONG
������һ����ɭɭ��·��, ŨŨ���������������, ������
Զ������ɢȥ�Ƶ�. ���Ͽ�ȥ����ǿ���Էֱ��һ����¥��ģ��,
������Լ���Կ�����յ����, ��Ũ�����Եø���Ĺ���. ·������
����һ��ľ��Ľ���, �Ŷ��ǰ뿪��, ���㿴�����������ʲ��.

LONG );
	set("exits", ([ /* sizeof() == 4 */
		"north" : "/d/death/road2",
		"south" : "/d/death/gateway",
		"west" : "/d/death/inn1",
		"east" : "/d/death/inn2",
	]));

	set("no_fight", 1);
	set("no_sleep_room", 1);

	setup();
}

