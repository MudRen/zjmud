// Room: /d/wanjiegu/wlhoushan.c

inherit ROOM;

void create()
{
	set("short", "��ɽ");
	set("long", @LONG
����������ɽ�ĺ�ɽ�����Ĵ����˿��������޷��ҵ���ɽ��·
������ǰ��һƬ����������ȥ�ľ���Ȼ��ԶԶ�Ŀ���ȥ������ɽ��
ʮ�ֹ⻬������һ�澵�ӡ�
LONG
	);
	set("outdoors", "wanjiegu");
	set("exits", ([ /* sizeof() == 2 */
		"northeast" : __DIR__"wlroad2",
	]));

	setup();
}
