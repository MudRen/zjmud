// Room: /d/wanjiegu/wlshan.c

inherit ROOM;

void create()
{
	set("short", "����ɽ");
	set("long", @LONG
�����������ɽ����ɽ����ľ���������������߶����㶼�޷�
�ҵ�һ���ܹ���ɽ��·������ɽ����һ�����ѵ�С·��
LONG
	);
	set("outdoors", "wanjiegu");
	set("exits", ([ /* sizeof() == 2 */
		"northwest" : __DIR__"wlroad1",
		"southeast" : __DIR__"riverside4",
	]));

	setup();
}
