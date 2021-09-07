// liandu.c ��Һ��ҩ

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "��Һ"ZJBR"��ҩ"; }

int perform(object me, object target)
{
	mapping p;
	string msg;
	object ob;
	int amount;
	int exp;
	int lvl;
	int sk;
 
	if (! target)
		return notify_fail("��Ҫȡ�����ߵĶ�Һ��ҩ��\n");

	if (! target->is_snake())
		return notify_fail("�����Щ���ǲ����ߣ���Ϲ��ʲô��\n");

	if (living(target))
		return notify_fail("�����߻��������أ�����������\n");

	if ((int)me->query_skill("shedu-qiqiao", 1) < 80)
		return notify_fail("����߶����ɻ��������, �������ƶ�ҩ !\n");

	if ((int)me->query_skill("hamagong", 1) < 80)
		return notify_fail("��ĸ�󡹦����Ϊ����, �������ƶ�ҩ !\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�����ڵ�����������\n");

	me->add("neili", -50);
	me->start_busy(random(3));

	msg = HIG "\n$N���˫ָ����ס" +
	      target->name() + "����ͣ��������ȳ���Һ��ҩ��"NOR"\n";

	p = target->query("snake_poison");
	if (! mapp(p))
		return notify_fail("��������Ū����ʲô��Һ���ˡ�"NOR"\n");

	lvl = (int) me->query_skill("poison", 1) / 2 +
	      (int) me->query_skill("shedu-qiqiao", 1);

	amount = p["level"] * p["remain"];
	if (amount > lvl)
		amount = lvl;
	
	p["remain"] = (p["level"] * p["remain"] - amount) /
		       p["level"];
	target->apply_condition("poison-supply", 1);

	if (! amount)
	{
		msg += WHT "$N���˰��죬���ɶҲû�м����������ǰ�æ���ˡ�"NOR"\n";
		message_vision(msg, me);
		return 1;
	}

	if (amount < lvl)
	{
		msg += WHT "$N����һ�㶾Һ������"NOR"\n";
		message_vision(msg, me);
		tell_object(me, "��ϧ��㶾Һ����һ�Ŷ�ҩ��������\n");
		return 1;
	}

	msg += HIM "$N��" + target->name() + "�Ķ�ҺϤ����������������"
	       "�����»�����һ�ž�Ө��͸��ҩ�衣"NOR"\n";
	message_vision(msg, me);
	tell_object(me, "��������һ���߶�ҩ�衣\n");

	// improve skill
	exp = lvl / 5;
	me->improve_skill("poison", 2 + random(exp));
	if (me->can_improve_skill("shedu-qiqiao"))
		me->improve_skill("shedu-qiqiao", 2 + random(exp));

	if (me->can_improve_skill("hamagong"))
		me->improve_skill("hamagong", 2 + random(exp / 6), 1);

	// create the object
	ob = new("/clone/misc/shedu");
	ob->set("poison", ([
		"level" : lvl,
		"id"    : me->query("id"),
		"name"  : "�߶�",
		"duration" : 10,
	]));
	ob->move(me);

	return 1;
}
