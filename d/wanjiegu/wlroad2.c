// Room: /d/wanjiegu/wlroad2.c

inherit ROOM;

void create()
{
	set("short", "С·");
	set("long", @LONG
���ﳤ�����Ӳݣ��������ǹ�ľ����ľ������գ�żȻ��һЩ
С����ͻȻ�������зɿ���ܿ����ش�ƫƧ��ʮ���ľ���
LONG
	);
	set("outdoors", "wanjiegu");
	set("exits", ([ /* sizeof() == 2 */
		"southwest" : __DIR__"wlhoushan",
		"east"      : __DIR__"wlroad1",
	]));

	setup();
}
