//      Designed by secret (����)
inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
����һ�������۵���·�����������Զ�������߲���
���ٵ�һ��Ƭ����ˮ�⴦������������ʥ����
LONG );
	set("outdoors", "xueshan");
	set("exits", ([
		"south" : __DIR__"tulu2",
		"north" : __DIR__"shenghu",
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	if (! playerp(me))
		return ::valid_leave(me, dir);

	if (random(3))
	{
		write("��ͻȻ������ǰ�ľ�����Щ���ҡ�\n");
		return -1;
	}
	return ::valid_leave(me, dir);
}
