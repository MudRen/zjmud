// feilong.c ��ɽ�����������������ɽ���

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	int damage;
	string msg;
	string tname;
	object weapon;
	int ap, fp, dp, pp;

	if (userp(me) && ! me->query("can_perform/huashan-sword/sanxian"))
		return notify_fail("�㲻��ʹ�ö����������ɽ���\n");

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�������������ɽ���ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("���ý���ôʹ�á������������ɽ�����\n");

	if ((int)me->query_skill("huashan-sword", 1) < 135)
		return notify_fail("�㻪ɽ����������죬ʹ�����������������ɽ�����\n");

	if ((int)me->query("neili") < 300)
		return notify_fail("�����������������޷����������������ɽ���ʹ�꣡\n");

	if (me->query_skill_mapped("sword") != "huashan-sword")
		return notify_fail("��û�м�����ɽ�������޷�ʹ�á������������ɽ�����\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	tname = target->name();
	me->add("neili", -300);

	ap = me->query_skill("sword");
	fp = target->query_skill("force") + target->query_skill("martial-cognize", 1);
	dp = target->query_skill("dodge") + target->query_skill("martial-cognize", 1);
	pp = target->query_skill("parry") + target->query_skill("martial-cognize", 1);

	msg = HIM "$N" HIM "������ȫ���˵��˽��ϣ�����һ������ͷֱ����"NOR"\n";
	if (ap / 2 + random(ap) < dp)
		msg += CYN "$n" CYN "б��������"NOR"\n";
	else
	if (ap / 2 + random(ap) < fp)
		msg += CYN "$n" CYN "Ĭ�������������ܿ�$N" CYN "��һ�����漴������"NOR"\n";
	else
	{
		damage = ap / 2 + random(ap / 2);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
					   HIR "$n" HIR "��æ���ˣ���Ȼ��ܲ�������$N"
					   HIR "��һ����ÿ�����Ѫ���������ˡ�"NOR"\n");
	}

	if (objectp(target))
	{
		msg += HIM "\n$N" HIM "Ȧת" + weapon->name() + HIM "������������"NOR"\n";
		if (ap / 2 + random(ap) < dp)
			msg += CYN "$n" CYN "����ӽ���Խ����"NOR"\n";
		else
		if (ap / 2 + random(ap) < pp)
			msg += CYN "$n" CYN "���ָ񵲣���$N" CYN "��һ���ܿ�������Ծ����"NOR"\n";
		else
		{
			damage = ap + random(ap / 2);
			msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
						   HIR "�������Ƶ���켰��$n" HIR "�������ü���"
						   "���мܣ�ֻ��$N" HIR "����������$n"
						   HIR "������ʱ��Ѫ���죡"NOR"\n");
		}
	}

	if (objectp(target))
	{
		msg += HIM "\n$N" HIM "�������ã�����$p" HIM "���ġ�"NOR"\n";
		if (ap / 2 + random(ap) < pp)
			msg += CYN "$n" CYN "���ڿ��У��������У�ֻ�ܻӳ�һ�У�������$N"
			       CYN "���ϣ���һ������ƮȻ��ȥ��"NOR"\n";
		else
		{
			damage = ap + random(ap / 2);
			msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 66,
						   HIR "$n" HIR "���ڿ��У��������ü����У�ֻ��$N"
						   HIR "�˽��ӹ���$n" HIR "�����Һ�����Ѫ���·ɽ���"NOR"\n");
		}
	}

	me->start_busy(3);
	if (objectp(target))
		message_combatd(msg, me, target);
	else
	{
		msg = replace_string(msg, "$n", tname);
		message_vision(msg, me);
	}

	return 1;
}
