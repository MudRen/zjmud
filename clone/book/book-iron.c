// book-iron.c

#include <armor.h>

inherit HANDS;

void create()
{
	set_name("������", ({ "iron hand", "hand", "shu", "book" }));
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("long",
			"�׽����ƪ\n"
			"����һ�������ƣ����氼��͹͹���������β����ĳ��档\n");
		set("value", 500);
		set("material", "steel");
		set("armor_prop/armor", 5);
		set("armor_prop/hand", 5);
		set("armor_prop/strike", 5);
		set("armor_prop/unarmed_damage", 20);
		set("skill", ([
			"name":	"parry",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	10,	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	29	// the maximum level you can learn
		]) );
	}
	setup();
}

void init()
{
	if( this_player() == environment() )
		add_action("do_study", "study");
}

int do_study(string arg)
{
	object me = this_player();

	if (! arg || ! id(arg))
		return notify_fail("��Ҫѧʲô��\n");

	if (! me->can_improve_skill("parry"))
	{
		write("���ʵս���鲻�㣬�޷������ж������Ƶ��书��\n");
		return 1;
	}

	if (me->is_fighting() &&
	    (int)me->query_skill("parry", 1) >= 30 &&
	    (int)me->query_skill("parry", 1) <= 100)
	{
		me->receive_damage("jing", 20);
		me->improve_skill("parry", 20 + random(20));
		message_vision("$Nһ��ս����һ�߳�ռ���æ"
			       "æ���ó���������ϸ�о���\n", me);
		return 1;
	}

	return 0;
}
