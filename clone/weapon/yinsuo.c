#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
	set_name(HIW "����" NOR + HIY "����" NOR,({ "yinsuo jinling", "suo", "ling",
						    "yinsuo", "jinling" }) );
	set_weight(1300);
	if (clonep())
		destruct(this_object());
	else {
		set("long", HIW "һ����ɫ�ĳ��������������Ž����Ĺ�"
			    "�󣬿���ȥ���Ǽ��͡�������һ��ϵ������"
			    "���塣"NOR"\n");
		set("unit", "��");
		set("value", 800000);
		set("no_sell", 1);
		set("material", "steel");
		set("wield_msg", HIW "$N" HIW "����Ĵӻ���ȡ��һ��"
				 "��ɫ�ĳ����������С�"NOR"\n"); 
		set("unwield_msg", HIW "$N����������" NOR + HIY "��"
				 "��" NOR + HIW "�ջ����䣬����ֽ���"
				 "�ų���â��"NOR"\n");
		set("stable", 50);
	}
	init_whip(150);
	setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int n;

	if (me->query_skill_mapped("whip") != "yinsuo-jinling" ||
	    me->query_skill("yinsuo-jinling", 1) < 100)
		return damage_bonus / 2;

	switch (random(12))
	{
	case 0:
		if (! victim->is_busy())
		victim->start_busy(me->query_skill("whip") / 10 + 2);
		return HIY "$N" HIY "һ�����ȣ����е�" NOR + HIW "����"
		       NOR + HIY "����ó������Ӱ��ֱ��$n" HIY "��ȥ��"
		       HIR "\n$n" HIR "��һ���ɣ�ֻ��ȫ��һ�飬�ѱ�$N"
		       HIR "���е���ҪѨ��"NOR"\n";

	case 1:
		n = me->query_skill("whip");
		victim->receive_damage("qi", n * 3 / 4, me);
		victim->receive_wound("qi", n * 3 / 4, me);
		return  HIY "$N" HIY "һ����Х������" NOR + HIW "����"
			NOR + HIY "������������ͨ�죬����ǵ�Ϯ��$n"
			HIY "��"NOR"\n";
	}
	return damage_bonus;
}

