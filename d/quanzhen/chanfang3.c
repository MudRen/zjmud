// chanfang3.c ����
// By Lgg,1998.10

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
������ȫ������������ԡ��������ĵط�����Ϊ����Ƚ��ľ���
�ܶ���������ﾲ�����񣬲����ѧ���С�
LONG
	);
	set("exits", ([
		"east" : __DIR__"xiaohuayuan2",
		"west" : __DIR__"chanfang2",
	]));
	setup();
}

void init()
{
	add_action("do_jingxiu", "jingxiu");
}

int do_jingxiu(string arg)
{
	object me;
	int cost;

	me = this_player();
	if (me->is_busy())
		return notify_fail("����æ������ͷ��������˵��\n");

	if (me->is_fighting())
		return notify_fail("��ߴ��һ�߾��ޣ�������ġ�\n");

	if (me->query("jing") < me->query("max_jing") * 7 / 10)
		return notify_fail("�����ڵľ��������޷����ޡ�\n");

	if (me->query_skill("taoism", 1) < 250)
		return notify_fail("��Ե�ѧ�ķ����̫ǳ�����޻�ò���ʲô������\n");

	if (! arg || ! sscanf(arg, "%d", cost))
		return notify_fail("��Ҫ������Ǳ�ܽ��о��ޣ�\n");

	if (cost >= me->query("potential") - me->query("learned_points"))
		return notify_fail("������û����ô���Ǳ�ܣ�\n");

	if (cost < 100)
		return notify_fail("���Ҳ̫���˰ɣ�����Ҫ��һ�ٵ�Ǳ�ܲ�������������\n");

	message_vision("$N����һ���ط�������������Ŀڤ�񣬿�"
		       "ʼר���о���ѧ�ķ���\n", me);

	me->set_temp("pending/jingxiu", 1);
	me->set_temp("potential_cost", cost);
	me->set_short_desc("�����ڵ���ڤ���ޡ�");
	me->start_busy((:call_other, __FILE__, "jingxiu" :),
		       (:call_other, __FILE__, "halt_jingxiu" :));
	return 1;
}

int jingxiu(object me)
{
	int cost;

	cost = me->query_temp("potential_cost");
	if (cost > 0)
	{
		cost = random(cost) + 1;
		if (cost > 3) cost = 3;
	} else
		cost = 0;

	me->improve_skill("taoism", me->query_int() / 5 +
			  random(me->query_skill("taoism", 1) * cost));
	me->add("learned_points", cost);
	if (me->add_temp("potential_cost", -cost) > 0)
		return 1;

	me->set_temp("pending/jingxiu", 0);
	me->set_short_desc(0);
	message_vision("$N������ϣ���¶΢Ц��վ��������\n", me);
	return 0;
}

int halt_jingxiu(object me)
{
	tell_object(me, "�������۾���վ��������\n");
	tell_room(environment(me), me->name() + "������������˫�ۣ�վ��������\n", me);
	me->set_temp("pending/jingxiu", 0);
	me->delete_temp("potential_cost");
	me->set_short_desc(0);
	return 1;
}
