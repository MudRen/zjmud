// xiaodao1.c
inherit ROOM;

void create()
{
	set("short", "�ּ�С��");
	set("long", @LONG
����һ���������ּ�С�����Ӷ���һֱͨ�����ߣ�һ����ȥ��������·
�ľ�ͷ�����԰ٻ����ޡ����������������ϱ���һ��С������������ң�ɵ�
���������������Ļ���������Ĵ򶷽к�����
LONG
	);
	set("exits", ([
		"east" : __DIR__"qingcaop",
		"west" : __DIR__"xiaodao2",
		"north" : __DIR__"wuchang1",
		"south" : __DIR__"wuchang2",
	]));

	set("outdoors", "xiaoyao");
	setup();
}

