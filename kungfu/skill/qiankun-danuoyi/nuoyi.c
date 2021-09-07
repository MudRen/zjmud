// nuoyi.c ��Ų��

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "��Ų��"; }

int perform(object me, object target)
{
	object weapon;
	object *obs;
	object der;
	string msg;
	int ap, dp;
	int damage;
	int level;
	int i;

	me->clean_up_enemy();
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����Ų�ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((level = (int)me->query_skill("qiankun-danuoyi", 1)) < 50)
		return notify_fail("���Ǭ����Ų�ƻ�û���������ڶ��㣬�޷�ʩչ��Ų�ơ�\n");

	if (me->query("neili") < 400)
		return notify_fail("�����������������޷�ʹ�á���Ų�ơ���\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	if (target->is_busy())
		return notify_fail("�Է�æ���أ��㲻�طѾ��ˡ�\n");

	msg = HIM "$N" HIM "������Ȼ��һ�䣬ġ�������������Ĵ�������������ǣ����$n"
	      HIM "����ʽ��"NOR"\n";

	ap = level + me->query_skill("force");
	dp = target->query_skill("force") +
	     target->query_skill("dodge", 1);
	if (level >= 300)
	{
		// layer 7 force
		ap += level;
	}

	if (ultrap(target))
		dp += target->query_skill("matrial-cognize", 1);

	der = 0;
	me->start_busy(2);
	me->add("neili", -350);
	if (ap / 3 + random(ap / 3) > dp)
	{
		// Success to make the target attack hiself
		msg += HIR "���$p" HIR "һ�л��������ô����Լ���Ҫ���ϣ�����һ���ҽУ�ˤ����ȥ��"NOR"\n";
		damage = me->query("max_qi");
		target->receive_damage("qi", damage / 2, me);
		target->receive_wound("qi", damage / 2, me);
	} else
	if (ap / 3 + random(ap) < dp)
	{
		// The enemy has defense
		msg += CYN "Ȼ��$p" CYN "�ڹ���񣬲�û�б�$P"
		       CYN "������ľ�����������"NOR"\n";
	} else
	if (sizeof(obs = me->query_enemy() - ({ target })) == 0)
	{
		// No other enemy
		msg += HIC "���$p" HIC "����ʽĪ������ı�"
		       "�˷��򣬾�Ȼ���Ʋ�ס���Һ����û�б�"
		       "�ˣ�û����ɴ����"NOR"\n";
	} else
	{
		string name;
		// Sucess to make the target attack my enemy
		der = obs[random(sizeof(obs))];
		name = der->name();
		if (name == target->name()) name = "��һ��" + name;
		msg += HIG "���$p" HIG "��������ʽ��������"
		       "�ı��˷���ͻȻ����" + name + HIG "��������" + name + HIG "���һ�����мܲ�����"NOR"\n";
	}

	message_combatd(msg, me, target);

	if (der)
	{
		// Target attack my enemy
		for (i = 0; i < 2 + random(3); i++)
		{
			if (! der->is_busy()) der->start_busy(1);
			COMBAT_D->do_attack(target, der, target->query_temp("weapon"));
		}
	}

	return 1;
}
