// pi.c ����ٵ�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"�ٵ�"; }

int perform(object me, object target)
{
	object weapon, weapon2;
	int damage, i, n;
	string msg, str;
	int ap, dp;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}
	if (! target || ! me->is_fighting(target))
		return notify_fail("������ٵء�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    weapon->query("skill_type") != "blade")
		return notify_fail("���á��������ء����б����е���\n");

	if (me->query_skill("hujia-daofa", 1) < 200)
		return notify_fail("��ĺ��ҵ���������죬����ʹ�á�����ٵء���\n");
				
	if (me->query_skill("force") < 250)
		return notify_fail("����ڹ���Ϊ�����ߡ�\n");
			
	if (me->query("neili") < 800)
		return notify_fail("����������̫��������ʹ�á��������ء���\n");

	if (userp(me) && ! me->query("can_perform/hujia-daofa/pi"))
		return notify_fail("�㻹����ʹ�á�����ٵء���һ������\n");
			
	msg = HIC "$N" HIC "һ����Ц���й�ֱ����˫�ֽ���" + weapon->name() +
	      HIC "����������һ������ȫ����$n" HIC "Ѹ����ȥ��"NOR"\n";

	if (target->query_temp("lengyue-shengong_freeze"))
	{
		msg += HIW + weapon->name() +
		HIW "�������ˣ�����˺�ѿ�����ƬƬѩ��Ʈ�䣬��δ�����ȼ���$n" HIW
		"üë�������˱�����˪��"NOR"\n";
	}

	ap = me->query_skill("blade") + me->query_skill("force");
	dp = target->query_skill("force");
	if (ap / 3 + random(ap / 3) > dp)
	{
		damage = ap + random(ap);
		damage += me->query("jiali");

		me->add("neili", -(damage / 2));

		if (! objectp(weapon2 = target->query_temp("weapon")))
		{       
			msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
						       HIR "ֻ��$n" HIR "һ���ҽУ��ؿڸ�"
						       "����һ���޴�Ŀ��ӣ���Ѫ��ӿ�����"NOR"\n");

			if (target->query_temp("lengyue-shengong_freeze"))
				msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 33,
							   HIB "\n$n" HIB "����ҡ�μ䣬�о���"
							   + weapon->name() + HIB + 
							   "��һ��̹ǵĺ����������ڣ��������"
							   "һ����Ѫ��"NOR"\n");
		} else
		{
			if (weapon2->is_item_make() || weapon2->query("damage") > 180 ||
			    weapon2->query("skill_type") == "hammer")
				msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
							   HIG "$p" HIG "���" + weapon2->name() + HIG "��ͼ�мܣ�"
							   HIG "�����⵶�����Ϭ����͸��" + weapon2->name() +
							   HIG "ֱ���$p" HIG "������Ѫ������������Ҫ��ת������"NOR"\n");
			else
			{
				msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
							   HIR "$n" HIR "��״�����æ����" + 
							   weapon2->name() + HIR + "�ֵ�����$N" HIR
							   "�������˫��һ���£�" + weapon2->name() +
							   HIR "�������Ƭ��"NOR"\n");
				n = 2 + random(3);
				for (i = 0; i < n; i++)
				{
					msg += (random(2) ? HIB : HIC) + "��Ƭ��ɢ�ɽ���������$n�����壡"NOR"\n";
	
					target->receive_damage("qi", damage / 7, me);
						target->receive_wound("qi",damage / 15 + random(damage / 15), me);
				}
	
				msg += "\n" + HIY + weapon->name() + HIY "����δ������������$n" + HIY + 
					"���ؿڣ�$n����ش�����Ѫ���������"NOR"\n";

				weapon2->set_name("���ѵ�" + weapon2->query("name"));
				weapon2->move(environment(target));
				weapon2->set("value", 0);
				weapon2->set("weapon_prop", 0);
			}

			target->reset_action();
			target->receive_damage("qi", damage / 2, me);
					       target->receive_wound("qi",
					       damage / 4 + random(damage / 4), me);

			if (target->query_temp("lengyue-shengong_freeze"))
				msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 25,
							   HIB "\n$n" HIB "����ҡ�μ䣬�о���"
							   + weapon->name() + HIB + 
							   "��һ��̹ǵĺ����������ڣ��������"
							   "һ����Ѫ��"NOR"\n");
		}
		me->start_busy(3);
		target->start_busy(1 + random(2));
	} else 
	{
		msg += HIY "$n" HIY "���Ʋ�������ˣ����ձܹ�$N"
		       HIY "����ǿ���ٵأ����������У������ѿ���һ������ӣ�"NOR"\n";
		me->add("neili", -100);
		me->start_busy(3);
	}
	
	message_sort(msg, me, target);

	return 1;
}
