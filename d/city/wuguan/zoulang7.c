//zoulang7.c
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����һ�����ȣ��ȶ�����Ž��������ķ羰��ÿ��������ɫ�����Ӽ����
Ҳ�������ߵľ��룬���ɫ�������ߣ��ۻ�ɫ�ĵ�ש�����������棬Ѿ�ߡ�ū
����������ȥ����æ���Լ������飬������һ�㵡�����������˻��Ⱦ��ܵ���
��԰�ˣ��������е��ӵ���Ϣ�ң���������Ů���ӵ���Ϣ�ҡ�
LONG
	);
	set("no_fight",1);
	set("exits", ([
		"west" : __DIR__"zoulang6",
		"east" : __DIR__"huilang",
		"north" : __DIR__"xxshi1",
		"south" : __DIR__"xxshi2",
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	if ((me->query("gender") =="����") && dir =="south" )
		return notify_fail("�ٺ٣���͵��Ů���ӵ��Է���\n");
	if ((me->query("gender") == "Ů��") && dir == "north")
		return notify_fail("Ů���ӻ��ǲ�Ҫ����ȥ�ĺã�����Ͳ������ż��ˡ�\n");

	return ::valid_leave(me, dir);
}
