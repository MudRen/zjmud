// Room: /d/xingxiu/xxroad6.c

inherit ROOM;

void create()
{
	set("short", "ɽ��ƽ��");
	set("long", @LONG
ɽ��ƽ�أ����������̵�С�ݣ���Χ���˼���������ɽ����һ
����Ȫ���ݵ������ż��������Ϲֵ����������͵����ľ�ˣ�����
���޵����������á����߹�ȥ����һ��ƽ�أ�Ҳ��������ȥ����
LONG );

	set("resource/water", 1);
	set("objects", ([
		__DIR__"obj/yangrou.c" : 3,
		"/clone/npc/mu-ren" : 4
	]));
	set("exits", ([
		"south" : __DIR__"xxroad5",
		"west" : __DIR__"wuchang2",
	]));
	set("outdoors", "xingxiu");
	set("for_family", "������");
	setup();
}
