// ximen.c
inherit ROOM;
void create()
{
	set("short","����");
	set("long",
		"���Ǹ�ɽׯ�����š������ε����ŷ������£����Ϲ���\n"
		"һ������(pai)�����������Ӳݴ�����\n"
	);

	set("exits",([
		"west" : __DIR__"cao1",
		"east" : __DIR__"changlang",
	]));

	set("item_desc",([
		"pai" : "���������ж��߳�û�����С�\n" ,
	]));

	set("objects",([
		__DIR__"npc/menwei" : 1,
	]));

	set("outdoors", "baituo");
	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (! objectp(guarder = present("men wei", this_object())))
		return 1;

	if (dir == "east")
		return guarder->permit_pass(me, dir);

	if (dir == "west"
	   && (int)me->query("combat_exp") < 600
	   && guarder )
		return notify_fail("��������һ������ľ���̫�ͣ��ᱻ"
				   "����ҧ���ģ����ǲ�Ҫ�Ҵ��ĺá�\n");

	return 1;
}
