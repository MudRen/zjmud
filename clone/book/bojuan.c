// bojuan.c

inherit ITEM;

void create()
{
	set_name("����", ({ "bo juan", "bo", "juan" }));
	set_weight(50);
	set("no_sell", 1);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
			"����һ��������д�� ��\n"
			"ׯ�ӡ���ң�Ρ����ƣ��֮����ڤ���ߣ����Ҳ�������ɣ������ǧ�������\n");
		set("value", 500);
		set("material", "silk");
		set("skill", ([
			"name":	"beiming-shengong",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	10,	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	19,	// the maximum level you can learn
			"min_skill":    10,
		]) );
	}
}

void init()
{
	if( this_player() == environment() )
	{
		add_action("do_study", "study");
		add_action("do_study", "du");
	}
}

int do_study(string arg)
{
	object me = this_player();

	if (! id(arg))
		return notify_fail("��Ҫ��ʲô��\n");

	if (me->is_busy())
		return notify_fail("��������æ���ء�\n");
 
	if (me->is_fighter())
		return notify_fail("ս�����޷��Ķ���֪��\n");

	if (me->query("jing") < 20)
		return notify_fail("�����ھ������㣬��Ϣһ���ٶ��ɡ�\n");

	if ((int)me->query_skill("beiming-shengong", 1) >= 20 &&
	    (int)me->query_skill("beiming-shengong", 1) <= 50 )
	{
		me->receive_damage("jing", 20 + random(20));
		me->improve_skill("beiming-shengong", 1 + random(me->query("int")));
		message_vision("$N����ר���ж���ڤ���ķ���\n", me);
		return 1;
	}
	return 0;
}
