// liangong3.c С������

inherit ROOM;

void create()
{
	set("short", "С������");
	set("long", @LONG
������һ��СС��ʯ�ң��ط���խ��ȴ���˼���ľ�ˣ���֪����
�������ڲ��»�����Ϊ���ʲôԭ�򡣵�����Щ���ң��������Ǿ���
��ɨ��
LONG
	);

	set("exits", ([
		"north" : __DIR__"liangong2",
	]));
	set("objects", ([
		"/clone/npc/mu-ren" : 3,
	]));
	set("for_family", "��Ĺ��");
	setup();
}
