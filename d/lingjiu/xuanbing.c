//ROOM xuanbing.c

inherit ROOM;

int exercise_improve();
	
void create()
{
	set("short","������");
	set("long", @LONG
���������ڹ��ĵط��� ����������һ��ǧ������(ice)������ð��˿
˿������ ������˺������ˣ��㲻�ɵô���һ��������
LONG );
	set("exits", ([
		"east" : __DIR__"changl13",
	]));

	set("item_desc", ([
	    "��������" : "����һ�������ɽ֮�۵�ǧ���������溮�ޱȡ�\n",
	]));

	set("exercise_improve", (: exercise_improve :));

	setup();
}

int exercise_improve()
{
	object me;

	me = this_player();
	if (me->query_skill("bahuang-gong", 1) >= 10)
	{
		if (random(5) == 0)
			tell_object(me, "�����ð˻�����Ω�Ҷ��𹦵��������������й���\n");
		return me->query_skill("force") / 10;
	}

	tell_object(me, "�㶳������ֱ�����������ϢҲ��һ����Ļ��ҡ�\n");
	return -20;
}
