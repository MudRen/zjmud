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
		set("long", HIG "���Ǹ�������֥�ϵ�һ�ξ�Ө��͸����¶����˵����"
				"��ɽ��ǧ��������֥Ϊĸ�����ϵ���ȡ���վ��»����������ޱ�����Ĺ�Ч(��������������ڹ��ȼ�180֮ǰ����������)��\n");
		set("yuanbao", 30);
		set("value", 100000);
		set("base_value", 100000);
		set("base_weight", 1);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	string force;

	message_vision(HIG "$N" HIG "С������Ľ���¶�������У���ʱ����"
		       "��̨һ���������������ƮƮ���ɣ�һʱ�侹�в��ڳ����ĸо���"NOR"\n", me);
	if (me->improve_neili(120 + random(150)))
		me->set("neili", me->query("max_neili"));

	force = me->query_skill_mapped("force");
	if (me->can_improve_skill("force")&&me->query_skill("force",1)<181)
		me->improve_skill("force", 40000);
	if (stringp(force) && me->can_improve_skill(force)&&me->query_skill(force,1)<181)
		me->improve_skill(force, 40000);

	me->start_busy(3);
	add_amount(-1);
	return 1;
}
