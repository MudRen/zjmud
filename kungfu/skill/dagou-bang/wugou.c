// wugou.c �����޹�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"�޹�"; }
string *pfm_type() { return ({ "staff", }); }

int query_cd() { return 4; }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int ap, dp, i, skill;

	if (userp(me) && ! me->query("can_perform/dagou-bang/wugou"))
		return notify_fail("�㲻��ʹ�á������޹�����\n");

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}
	if (! target || ! me->is_fighting(target))
		return notify_fail("�������޹���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");
		
	if (skill=(int)me->query_skill("dagou-bang", 1) < 150)
		return notify_fail("��Ĵ򹷰���������죬����ʹ�á������޹�����\n");
				
	if ((int)me->query_skill("force") < 220)
		return notify_fail("����ڹ���Ϊ�����ߣ��������á������޹�����\n");
			
	if ((int)me->query("neili") < 500)
		return notify_fail("��������������������ʹ�á������޹�����\n");

	if (me->query_skill_mapped("staff") != "dagou-bang")
		return notify_fail("��û�м����򹷰���������ʹ�á������޹�����\n");

      if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

      message_vision(HIW"\n"HIW"$N"HIW"���е�" +weapon->name()+HIW "��������һ·���򹷰�����ʹ�ñ仯�򷽣�������ȥ������ز�ã����������������裡\n",me);
      message_vision(HIG"�����Ǵ򹷰����ľ��С������޹���,��˵������ף�һ��ʹ������������������˷�ȫ�ǰ�Ӱ��\n",me);
      message_vision(HIG"��ʱ�����м�ʮ����ȮҲ��һ�������ˣ���ν�������޹������Ǵ��⡣"NOR"\n",me);

      me->add_temp("apply/damage", skill/4);
	write("��Ĺ�����˲������� "+skill/4+" �㡣\n");

	for (i = 0; i < 6; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

      me->add_temp("apply/damage", skill/4);	
	me->add("neili", -500);
	me->start_busy(1+random(2));

/*
	switch (random(3))
	{
	case 0:
		msg = HIC "$N" HIC "���е�" + weapon->name() +
		      HIC "�����²������������籩������һ�㹥��$n" HIC "��"NOR"\n";
		break;

	case 1:
		msg = HIC "$N" HIC "������Ц������" + weapon->name() +
		      HIC "�������������˻˻���죬$n"
		      HIC "ֻ������ǰһ��������˷�����" + weapon->name() + "��\n";
		break;

	default:
		msg = HIC "$N" HIC "����" + weapon->name() +
		      HIC "���̶�����;��һ�����������ġ�Խ��Խ�࣬��������$n"
		      HIC "ȫȻ�������ڡ�"NOR"\n";
		break;
	}

	ap = me->query_skill("staff") + me->query("int") * 10;
	dp = target->query_skill("parry") + target->query("dex") * 10;
	if (ap / 2 + random(ap) > dp)
	{
		damage = me->query_skill("force") + ap;
		damage = damage / 2 + random(damage / 2);

		me->add("neili", -300);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
					   HIR "ֻ��$p" HIR "��æ���ң��мܲ�������������$P"
					   HIR "��������ʹ���̣�������У�"NOR"\n");
		me->start_busy(2);
	} else 
	{
		msg += HIC "����$p" HIC "�����ۿ죬�������ܣ���Ȼ��ס$P"
		       HIC "���е����У�"NOR"\n";
		me->add("neili", -100);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);
*/

	return 1;
}

