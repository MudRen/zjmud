// xiaodao2.c
// shilling 97.2

inherit ROOM;

void create()
{
	set("short", "�ּ�С��");
	set("long", @LONG
����һ���������ּ�С�����Ӷ���һֱͨ�����ߣ�һ����ȥ��������·
�ľ�ͷ�����԰ٻ����ޡ����������������ϱߺ�������ζɢ��������������
����������
LONG );
	set("exits", ([ /* sizeof() == 4 */
		"south" : __DIR__"shantang",
		"east" : __DIR__"xiaodao1",
		"west" : __DIR__"xiuxis",
		"north" : __DIR__"bingqif",
	]));
	set("outdoors", "xiaoyao");
	setup();
}

