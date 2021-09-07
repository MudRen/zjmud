// jinsha.c

#include <ansi.h>
inherit COMBINED_ITEM;
string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}

void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name(HIG "������¶" NOR, ({"magic water", "yvlu", "lu"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("base_unit", "��");
		set("long", HIG "���Ǹ�������֥�ϵ�һ�ξ�Ө��͸����¶����˵����\n"
				"��ɽ��ǧ��������֥Ϊĸ�����ϵ���ȡ���վ��»���\n"
				"�������ޱ�����Ĺ�Ч��\n");
		set("value", 100000);
		set("base_value", 100000);
		set("no_get", 1);
		set("no_give", 1);
		set("no_drop", 1);
		set("no_sell", 1);
		set("no_steal", 1);
		set("no_beg", 1);
		set("base_weight", 1);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	string force;

	message_vision(HIG "$N" HIG "С������Ľ���¶�������У�\n��ʱ����"
		       "��̨һ���������������ƮƮ���ɣ�\nһʱ�侹�в���"
		       "�����ĸо���"NOR"\n",
		       me);
	if (me->improve_neili(120 + random(150)))
		me->set("neili", me->query("max_neili"));

	force = me->query_skill_mapped("force");
	if (me->can_improve_skill("force"))
		me->improve_skill("force", 40000);
	if (stringp(force) && me->can_improve_skill(force))
		me->improve_skill(force, 40000);

	me->start_busy(3);
	add_amount(-1);
	return 1;
}
