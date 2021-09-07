// Room: /d/taishan/.c
inherit ROOM;

int do_study(string arg);

void create()
{
	set("short", "ʯ����");
	set("long", @LONG
������һ���ʯƺ��ʯ�����׭�ġ���վ�������������綷��
��ȴû�м��ؿ�ʯ�ߵ����ֺͿ�ʯ����������˴˴��������ɽ��
ɽ·Խ��Խ�������ˡ�
LONG );
	set("exits", ([
		"northup" : __DIR__"huima",
		"westdown" : __DIR__"doumo",
	]));
	set("objects",([
		__DIR__"npc/seng-ren" : 1,
	]));
	set("outdoors", "taishan");
	setup();
}

void init()
{
	add_action("do_study", "study");
	add_action("do_study", "du");
}


int do_study(string arg)
{
	object me;

	me = this_player();

	if (! arg || (arg != "stone"))
		return notify_fail("��Ҫ�о�ʲô��\n");

	if ((int)me->query_skill("literate", 1) < 1)
		return notify_fail("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");

	me->receive_damage("jing", 30);

	message_vision("$N��ר���ж�ʯƺ�ϵġ���վ�����\n", me);

	if ((int)me->query_skill("buddhism", 1) < 100)
	{
		me->improve_skill("buddhism", 1 + random(me->query("int")));
		write("�����ʯƺ�ϵġ���վ�����ĥ��һ��"
		      "�����ƺ��������ķ������ĵá�\n");
		return 1;
	}

	write("�����ʯƺ����һ�ض�������������˵�ķ���̫��"
	      "ǳ�ԣ�������˵�Ѻ��������ˡ�\n");

	return 1;
}


