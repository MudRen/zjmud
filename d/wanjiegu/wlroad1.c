// Room: /d/wanjiegu/wlroad1.c

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
		"west"      : __DIR__"wlroad2",
		"southeast" : __DIR__"wlshan",
	]));

	setup();
}
