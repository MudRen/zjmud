// Room: /d/xingxiu/wuchang2.c

inherit ROOM;

void create()
{
	set("short", "ɽ��ƽ��");
	set("long", @LONG
ɽ��ƽ�أ����������̵�С�ݣ���Χ���˼���������ɽ����һ
����Ȫ���ݵ������ż��������Ϲֵ����������͵����ľ�ˣ�����
�����޵����������á������߽�������һ����������
LONG );

	set("resource/water", 1);
	set("objects", ([
		__DIR__"obj/yangrou.c" : 3,
		"/clone/npc/mu-ren" : 4
	]));
	set("exits", ([
		"east" : __DIR__"xxroad6",
		"west" : __DIR__"wuchang3",
	]));
	set("outdoors", "xingxiu");
	set("for_family", "������");
	setup();
}
