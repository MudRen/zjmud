//ROM yuanzi

inherit ROOM;

void create()
{
	set("short", "����");
	set("long",
	     "������������µġ�����ɽׯ���Ĵ��š��������ϵ����̷��ۼ\n"
	 "���أ���֪�����Ŷ����ܹ��ɽ�����Ѫ�����Գ�ׯ���ĸ������Թ���\n"
	 "ǰ���Ҹ�����һֻ����ׯ�ϵ�ʯʨ�ӡ�\n"
	);
	set("outdoors", "baituo");
	set("exits", ([
		"north" : __DIR__"yuanzi",
		"southdown" : __DIR__"shijie",
	]));
	set("objects",([
		__DIR__"npc/menwei" : 2,
	]));
	set("valid_startroom",1);
	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (objectp(guarder = present("men wei", this_object())) &&
		dir == "north")
	{
		return guarder->permit_pass(me, dir);
	}

	return 1;
}
